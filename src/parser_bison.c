/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         nft_parse
#define yylex           nft_lex
#define yyerror         nft_error
#define yylval          nft_lval
#define yychar          nft_char
#define yydebug         nft_debug
#define yynerrs         nft_nerrs
#define yylloc          nft_lloc

/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 11 "parser_bison.y"


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



/* Line 268 of yacc.c  */
#line 170 "parser_bison.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     HANDLE = 294,
     RULESET = 295,
     INET = 296,
     NETDEV = 297,
     ADD = 298,
     UPDATE = 299,
     CREATE = 300,
     INSERT = 301,
     DELETE = 302,
     LIST = 303,
     FLUSH = 304,
     RENAME = 305,
     DESCRIBE = 306,
     EXPORT = 307,
     MONITOR = 308,
     ACCEPT = 309,
     DROP = 310,
     CONTINUE = 311,
     JUMP = 312,
     GOTO = 313,
     RETURN = 314,
     TO = 315,
     CONSTANT = 316,
     INTERVAL = 317,
     TIMEOUT = 318,
     GC_INTERVAL = 319,
     ELEMENTS = 320,
     POLICY = 321,
     MEMORY = 322,
     PERFORMANCE = 323,
     SIZE = 324,
     NUM = 325,
     STRING = 326,
     QUOTED_STRING = 327,
     LL_HDR = 328,
     NETWORK_HDR = 329,
     TRANSPORT_HDR = 330,
     BRIDGE = 331,
     ETHER = 332,
     SADDR = 333,
     DADDR = 334,
     TYPE = 335,
     VLAN = 336,
     ID = 337,
     CFI = 338,
     PCP = 339,
     ARP = 340,
     HTYPE = 341,
     PTYPE = 342,
     HLEN = 343,
     PLEN = 344,
     OPERATION = 345,
     IP = 346,
     HDRVERSION = 347,
     HDRLENGTH = 348,
     TOS = 349,
     LENGTH = 350,
     FRAG_OFF = 351,
     TTL = 352,
     PROTOCOL = 353,
     CHECKSUM = 354,
     ICMP = 355,
     CODE = 356,
     SEQUENCE = 357,
     GATEWAY = 358,
     MTU = 359,
     IP6 = 360,
     PRIORITY = 361,
     FLOWLABEL = 362,
     NEXTHDR = 363,
     HOPLIMIT = 364,
     ICMP6 = 365,
     PPTR = 366,
     MAXDELAY = 367,
     AH = 368,
     RESERVED = 369,
     SPI = 370,
     ESP = 371,
     COMP = 372,
     FLAGS = 373,
     CPI = 374,
     UDP = 375,
     SPORT = 376,
     DPORT = 377,
     UDPLITE = 378,
     CSUMCOV = 379,
     TCP = 380,
     ACKSEQ = 381,
     DOFF = 382,
     WINDOW = 383,
     URGPTR = 384,
     DCCP = 385,
     SCTP = 386,
     VTAG = 387,
     RT = 388,
     RT0 = 389,
     RT2 = 390,
     SEG_LEFT = 391,
     ADDR = 392,
     HBH = 393,
     FRAG = 394,
     RESERVED2 = 395,
     MORE_FRAGMENTS = 396,
     DST = 397,
     MH = 398,
     META = 399,
     NFPROTO = 400,
     L4PROTO = 401,
     MARK = 402,
     IIF = 403,
     IIFNAME = 404,
     IIFTYPE = 405,
     OIF = 406,
     OIFNAME = 407,
     OIFTYPE = 408,
     SKUID = 409,
     SKGID = 410,
     NFTRACE = 411,
     RTCLASSID = 412,
     IBRIPORT = 413,
     OBRIPORT = 414,
     PKTTYPE = 415,
     CPU = 416,
     IIFGROUP = 417,
     OIFGROUP = 418,
     CGROUP = 419,
     CT = 420,
     DIRECTION = 421,
     STATE = 422,
     STATUS = 423,
     EXPIRATION = 424,
     HELPER = 425,
     L3PROTOCOL = 426,
     PROTO_SRC = 427,
     PROTO_DST = 428,
     LABEL = 429,
     COUNTER = 430,
     PACKETS = 431,
     BYTES = 432,
     LOG = 433,
     PREFIX = 434,
     GROUP = 435,
     SNAPLEN = 436,
     QUEUE_THRESHOLD = 437,
     LEVEL = 438,
     LEVEL_EMERG = 439,
     LEVEL_ALERT = 440,
     LEVEL_CRIT = 441,
     LEVEL_ERR = 442,
     LEVEL_WARN = 443,
     LEVEL_NOTICE = 444,
     LEVEL_INFO = 445,
     LEVEL_DEBUG = 446,
     LIMIT = 447,
     RATE = 448,
     NANOSECOND = 449,
     MICROSECOND = 450,
     MILLISECOND = 451,
     SECOND = 452,
     MINUTE = 453,
     HOUR = 454,
     DAY = 455,
     WEEK = 456,
     _REJECT = 457,
     RESET = 458,
     WITH = 459,
     ICMPX = 460,
     SNAT = 461,
     DNAT = 462,
     MASQUERADE = 463,
     REDIRECT = 464,
     RANDOM = 465,
     FULLY_RANDOM = 466,
     PERSISTENT = 467,
     QUEUE = 468,
     QUEUENUM = 469,
     BYPASS = 470,
     FANOUT = 471,
     POSITION = 472,
     COMMENT = 473,
     XML = 474,
     JSON = 475
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
#define HANDLE 294
#define RULESET 295
#define INET 296
#define NETDEV 297
#define ADD 298
#define UPDATE 299
#define CREATE 300
#define INSERT 301
#define DELETE 302
#define LIST 303
#define FLUSH 304
#define RENAME 305
#define DESCRIBE 306
#define EXPORT 307
#define MONITOR 308
#define ACCEPT 309
#define DROP 310
#define CONTINUE 311
#define JUMP 312
#define GOTO 313
#define RETURN 314
#define TO 315
#define CONSTANT 316
#define INTERVAL 317
#define TIMEOUT 318
#define GC_INTERVAL 319
#define ELEMENTS 320
#define POLICY 321
#define MEMORY 322
#define PERFORMANCE 323
#define SIZE 324
#define NUM 325
#define STRING 326
#define QUOTED_STRING 327
#define LL_HDR 328
#define NETWORK_HDR 329
#define TRANSPORT_HDR 330
#define BRIDGE 331
#define ETHER 332
#define SADDR 333
#define DADDR 334
#define TYPE 335
#define VLAN 336
#define ID 337
#define CFI 338
#define PCP 339
#define ARP 340
#define HTYPE 341
#define PTYPE 342
#define HLEN 343
#define PLEN 344
#define OPERATION 345
#define IP 346
#define HDRVERSION 347
#define HDRLENGTH 348
#define TOS 349
#define LENGTH 350
#define FRAG_OFF 351
#define TTL 352
#define PROTOCOL 353
#define CHECKSUM 354
#define ICMP 355
#define CODE 356
#define SEQUENCE 357
#define GATEWAY 358
#define MTU 359
#define IP6 360
#define PRIORITY 361
#define FLOWLABEL 362
#define NEXTHDR 363
#define HOPLIMIT 364
#define ICMP6 365
#define PPTR 366
#define MAXDELAY 367
#define AH 368
#define RESERVED 369
#define SPI 370
#define ESP 371
#define COMP 372
#define FLAGS 373
#define CPI 374
#define UDP 375
#define SPORT 376
#define DPORT 377
#define UDPLITE 378
#define CSUMCOV 379
#define TCP 380
#define ACKSEQ 381
#define DOFF 382
#define WINDOW 383
#define URGPTR 384
#define DCCP 385
#define SCTP 386
#define VTAG 387
#define RT 388
#define RT0 389
#define RT2 390
#define SEG_LEFT 391
#define ADDR 392
#define HBH 393
#define FRAG 394
#define RESERVED2 395
#define MORE_FRAGMENTS 396
#define DST 397
#define MH 398
#define META 399
#define NFPROTO 400
#define L4PROTO 401
#define MARK 402
#define IIF 403
#define IIFNAME 404
#define IIFTYPE 405
#define OIF 406
#define OIFNAME 407
#define OIFTYPE 408
#define SKUID 409
#define SKGID 410
#define NFTRACE 411
#define RTCLASSID 412
#define IBRIPORT 413
#define OBRIPORT 414
#define PKTTYPE 415
#define CPU 416
#define IIFGROUP 417
#define OIFGROUP 418
#define CGROUP 419
#define CT 420
#define DIRECTION 421
#define STATE 422
#define STATUS 423
#define EXPIRATION 424
#define HELPER 425
#define L3PROTOCOL 426
#define PROTO_SRC 427
#define PROTO_DST 428
#define LABEL 429
#define COUNTER 430
#define PACKETS 431
#define BYTES 432
#define LOG 433
#define PREFIX 434
#define GROUP 435
#define SNAPLEN 436
#define QUEUE_THRESHOLD 437
#define LEVEL 438
#define LEVEL_EMERG 439
#define LEVEL_ALERT 440
#define LEVEL_CRIT 441
#define LEVEL_ERR 442
#define LEVEL_WARN 443
#define LEVEL_NOTICE 444
#define LEVEL_INFO 445
#define LEVEL_DEBUG 446
#define LIMIT 447
#define RATE 448
#define NANOSECOND 449
#define MICROSECOND 450
#define MILLISECOND 451
#define SECOND 452
#define MINUTE 453
#define HOUR 454
#define DAY 455
#define WEEK 456
#define _REJECT 457
#define RESET 458
#define WITH 459
#define ICMPX 460
#define SNAT 461
#define DNAT 462
#define MASQUERADE 463
#define REDIRECT 464
#define RANDOM 465
#define FULLY_RANDOM 466
#define PERSISTENT 467
#define QUEUE 468
#define QUEUENUM 469
#define BYPASS 470
#define FANOUT 471
#define POSITION 472
#define COMMENT 473
#define XML 474
#define JSON 475




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 122 "parser_bison.y"

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



/* Line 293 of yacc.c  */
#line 666 "parser_bison.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 691 "parser_bison.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2240

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  230
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  182
/* YYNRULES -- Number of rules.  */
#define YYNRULES  533
/* YYNRULES -- Number of states.  */
#define YYNSTATES  751

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   475

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   224,     2,     2,     2,
     225,   226,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   221,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   228,     2,   229,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   222,   227,   223,     2,     2,     2,     2,
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
     215,   216,   217,   218,   219,   220
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    14,    18,
      24,    27,    29,    31,    34,    37,    39,    42,    45,    48,
      51,    54,    57,    60,    63,    66,    69,    72,    79,    82,
      89,    93,    96,   103,   110,   114,   117,   124,   127,   134,
     138,   141,   144,   147,   150,   153,   157,   160,   163,   166,
     169,   172,   175,   178,   181,   184,   187,   191,   193,   197,
     198,   200,   201,   203,   205,   207,   209,   211,   212,   214,
     216,   218,   220,   221,   224,   225,   228,   231,   235,   244,
     253,   262,   263,   264,   267,   270,   274,   278,   282,   283,
     284,   287,   290,   295,   300,   305,   310,   315,   319,   323,
     325,   327,   329,   331,   332,   333,   336,   339,   346,   351,
     356,   360,   363,   366,   368,   370,   372,   374,   378,   380,
     382,   389,   397,   406,   416,   419,   421,   423,   425,   427,
     429,   431,   432,   434,   436,   438,   440,   442,   444,   446,
     449,   451,   454,   456,   459,   461,   462,   465,   466,   469,
     473,   474,   477,   478,   480,   483,   485,   488,   490,   492,
     494,   496,   498,   500,   502,   504,   506,   508,   510,   512,
     514,   516,   518,   522,   526,   529,   531,   535,   539,   545,
     547,   550,   552,   554,   557,   560,   563,   565,   568,   570,
     572,   575,   578,   581,   584,   587,   590,   592,   594,   596,
     598,   600,   602,   604,   606,   612,   614,   616,   618,   620,
     622,   625,   627,   628,   633,   638,   643,   647,   650,   652,
     654,   656,   660,   663,   666,   668,   671,   673,   676,   678,
     680,   683,   685,   689,   691,   695,   697,   699,   701,   703,
     706,   708,   710,   713,   716,   718,   720,   724,   726,   728,
     733,   735,   737,   739,   741,   744,   747,   749,   751,   753,
     755,   757,   759,   761,   765,   767,   771,   775,   777,   781,
     783,   787,   789,   793,   795,   797,   801,   805,   809,   813,
     817,   819,   821,   823,   825,   829,   831,   833,   835,   837,
     841,   843,   847,   851,   855,   859,   865,   867,   870,   872,
     874,   877,   880,   883,   885,   887,   889,   891,   893,   895,
     898,   901,   905,   907,   909,   911,   913,   915,   917,   919,
     921,   923,   926,   929,   931,   934,   936,   938,   940,   942,
     944,   946,   948,   950,   952,   954,   956,   958,   960,   962,
     964,   966,   968,   970,   972,   974,   976,   978,   980,   982,
     984,   986,   991,   995,   998,  1000,  1002,  1004,  1006,  1008,
    1010,  1012,  1014,  1016,  1018,  1020,  1022,  1024,  1029,  1031,
    1033,  1035,  1037,  1039,  1041,  1043,  1045,  1047,  1049,  1051,
    1053,  1055,  1057,  1059,  1061,  1068,  1070,  1072,  1074,  1077,
    1079,  1081,  1083,  1085,  1088,  1090,  1092,  1094,  1096,  1098,
    1101,  1103,  1105,  1107,  1109,  1111,  1113,  1116,  1118,  1120,
    1122,  1124,  1126,  1128,  1130,  1132,  1134,  1136,  1138,  1140,
    1143,  1145,  1147,  1149,  1151,  1153,  1155,  1157,  1159,  1162,
    1164,  1166,  1168,  1170,  1172,  1174,  1176,  1178,  1180,  1183,
    1185,  1187,  1189,  1191,  1193,  1195,  1197,  1199,  1201,  1204,
    1206,  1208,  1210,  1212,  1214,  1216,  1219,  1221,  1223,  1225,
    1228,  1230,  1232,  1234,  1236,  1239,  1241,  1243,  1245,  1247,
    1249,  1252,  1254,  1256,  1258,  1260,  1262,  1265,  1267,  1269,
    1271,  1273,  1275,  1277,  1279,  1281,  1283,  1285,  1287,  1290,
    1292,  1294,  1296,  1298,  1301,  1303,  1305,  1307,  1309,  1311,
    1313,  1315,  1317,  1319,  1321,  1323,  1325,  1328,  1330,  1332,
    1335,  1337,  1339,  1341,  1343,  1346,  1351,  1354,  1356,  1359,
    1361,  1363,  1365,  1367,  1369,  1371,  1374,  1376,  1378,  1381,
    1383,  1385,  1387,  1389
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     231,     0,    -1,    -1,   231,   235,    -1,     4,    -1,     6,
      -1,     4,    -1,    -1,    25,    72,   232,    -1,    26,   270,
     221,   352,   232,    -1,     1,   232,    -1,   234,    -1,   232,
      -1,   236,   232,    -1,   236,     0,    -1,   237,    -1,    43,
     237,    -1,    45,   238,    -1,    46,   239,    -1,    47,   240,
      -1,    48,   241,    -1,    49,   242,    -1,    50,   243,    -1,
      52,   244,    -1,    53,   245,    -1,    51,   250,    -1,    29,
     275,    -1,    29,   275,   251,   222,   253,   223,    -1,    31,
     277,    -1,    31,   277,   254,   222,   255,   223,    -1,    33,
     283,   286,    -1,   283,   286,    -1,    36,   279,   256,   222,
     257,   223,    -1,    38,   279,   260,   222,   261,   223,    -1,
      37,   279,   343,    -1,    29,   275,    -1,    29,   275,   251,
     222,   253,   223,    -1,    31,   277,    -1,    31,   277,   254,
     222,   255,   223,    -1,    33,   283,   286,    -1,    29,   275,
      -1,    31,   277,    -1,    33,   283,    -1,    36,   279,    -1,
      38,   279,    -1,    37,   279,   343,    -1,    29,   275,    -1,
      30,   276,    -1,    31,   277,    -1,    35,   276,    -1,    36,
     279,    -1,    40,   285,    -1,    29,   275,    -1,    31,   277,
      -1,    36,   279,    -1,    40,   285,    -1,    31,   277,   270,
      -1,   249,    -1,   246,   247,   248,    -1,    -1,    71,    -1,
      -1,    30,    -1,    32,    -1,    35,    -1,    34,    -1,    65,
      -1,    -1,   249,    -1,   219,    -1,   220,    -1,   329,    -1,
      -1,   118,    71,    -1,    -1,   253,   234,    -1,   253,   232,
      -1,   253,   252,   232,    -1,   253,    31,   278,   254,   222,
     255,   223,   232,    -1,   253,    36,   280,   256,   222,   257,
     223,   232,    -1,   253,    38,   280,   260,   222,   261,   223,
     232,    -1,    -1,    -1,   255,   234,    -1,   255,   232,    -1,
     255,   267,   232,    -1,   255,   268,   232,    -1,   255,   286,
     232,    -1,    -1,    -1,   257,   234,    -1,   257,   232,    -1,
     257,    80,   264,   232,    -1,   257,   118,   258,   232,    -1,
     257,    63,   272,   232,    -1,   257,    64,   272,   232,    -1,
     257,    65,   221,   343,    -1,   257,   262,   232,    -1,   258,
       7,   259,    -1,   259,    -1,    61,    -1,    62,    -1,    63,
      -1,    -1,    -1,   261,   234,    -1,   261,   232,    -1,   261,
      80,   264,     5,   264,   232,    -1,   261,   118,   258,   232,
      -1,   261,    65,   221,   343,    -1,   261,   262,   232,    -1,
      66,   263,    -1,    69,    70,    -1,    68,    -1,    67,    -1,
     265,    -1,   266,    -1,   265,     8,   266,    -1,    71,    -1,
     147,    -1,    80,    71,    27,    71,   106,    70,    -1,    80,
      71,    27,    71,   106,    22,    70,    -1,    80,    71,    27,
      71,    28,    71,   106,    70,    -1,    80,    71,    27,    71,
      28,    71,   106,    22,    70,    -1,    66,   269,    -1,    54,
      -1,    55,    -1,    71,    -1,    71,    -1,    72,    -1,    71,
      -1,    -1,   274,    -1,    91,    -1,   105,    -1,    41,    -1,
      85,    -1,    76,    -1,    42,    -1,   273,   270,    -1,   273,
      -1,   275,   270,    -1,   270,    -1,   275,   270,    -1,   270,
      -1,    -1,    39,    70,    -1,    -1,   217,    70,    -1,   277,
     281,   282,    -1,    -1,   218,   271,    -1,    -1,   274,    -1,
     287,   284,    -1,   288,    -1,   287,   288,    -1,   289,    -1,
     326,    -1,   294,    -1,   360,    -1,   298,    -1,   303,    -1,
     305,    -1,   308,    -1,   318,    -1,   363,    -1,   311,    -1,
     313,    -1,   324,    -1,   355,    -1,   290,    -1,   335,    24,
     291,    -1,   222,   292,   223,    -1,    23,   270,    -1,   293,
      -1,   292,     7,   293,    -1,   292,     7,   233,    -1,   233,
     346,     5,   355,   233,    -1,   295,    -1,   295,   296,    -1,
     175,    -1,   297,    -1,   296,   297,    -1,   176,    70,    -1,
     177,    70,    -1,   299,    -1,   299,   300,    -1,   178,    -1,
     301,    -1,   300,   301,    -1,   179,   271,    -1,   180,    70,
      -1,   181,    70,    -1,   182,    70,    -1,   183,   302,    -1,
     184,    -1,   185,    -1,   186,    -1,   187,    -1,   188,    -1,
     189,    -1,   190,    -1,   191,    -1,   192,   193,    70,    20,
     304,    -1,   197,    -1,   198,    -1,   199,    -1,   200,    -1,
     201,    -1,   306,   307,    -1,   202,    -1,    -1,   204,   100,
      80,    71,    -1,   204,   110,    80,    71,    -1,   204,   205,
      80,    71,    -1,   204,   125,   203,    -1,   309,   310,    -1,
     206,    -1,   207,    -1,   342,    -1,   342,     5,   342,    -1,
       5,   342,    -1,   310,   316,    -1,   312,    -1,   312,   316,
      -1,   208,    -1,   314,   315,    -1,   314,    -1,   209,    -1,
      60,   342,    -1,   316,    -1,    60,   342,   316,    -1,   317,
      -1,   316,     7,   317,    -1,   210,    -1,   211,    -1,   212,
      -1,   319,    -1,   319,   320,    -1,   213,    -1,   321,    -1,
     320,   321,    -1,   214,   342,    -1,   322,    -1,   323,    -1,
     322,     7,   323,    -1,   215,    -1,   216,    -1,    36,   325,
     346,   327,    -1,    43,    -1,    44,    -1,   353,    -1,   271,
      -1,   224,   270,    -1,    23,   270,    -1,    70,    -1,   327,
      -1,   328,    -1,   364,    -1,   397,    -1,   356,    -1,   361,
      -1,   225,   334,   226,    -1,   329,    -1,   330,    15,   329,
      -1,   330,    16,   329,    -1,   330,    -1,   331,    17,   330,
      -1,   331,    -1,   332,    18,   331,    -1,   332,    -1,   333,
     227,   332,    -1,   333,    -1,   334,    -1,   335,     8,   334,
      -1,   334,     7,   334,    -1,   336,     7,   334,    -1,   334,
      20,    70,    -1,   334,    22,   334,    -1,    21,    -1,   337,
      -1,   338,    -1,   339,    -1,   335,    38,   342,    -1,   335,
      -1,   340,    -1,   343,    -1,   341,    -1,   222,   344,   223,
      -1,   345,    -1,   344,     7,   345,    -1,   344,     7,   233,
      -1,   233,   343,   233,    -1,   233,   346,   233,    -1,   233,
     346,     5,   351,   233,    -1,   347,    -1,   347,   348,    -1,
     350,    -1,   349,    -1,   348,   349,    -1,    63,   272,    -1,
     218,   271,    -1,   335,    -1,   340,    -1,   335,    -1,   355,
      -1,   342,    -1,   336,    -1,   342,   342,    -1,   342,   336,
      -1,   342,   354,   342,    -1,     9,    -1,    10,    -1,    11,
      -1,    12,    -1,    13,    -1,    14,    -1,    54,    -1,    55,
      -1,    56,    -1,    57,   270,    -1,    58,   270,    -1,    59,
      -1,   144,   357,    -1,   359,    -1,   358,    -1,   359,    -1,
      95,    -1,   145,    -1,   146,    -1,    98,    -1,   106,    -1,
     147,    -1,   148,    -1,   149,    -1,   150,    -1,   151,    -1,
     152,    -1,   153,    -1,   154,    -1,   155,    -1,   156,    -1,
     157,    -1,   158,    -1,   159,    -1,   160,    -1,   161,    -1,
     162,    -1,   163,    -1,   164,    -1,   144,   357,    36,   342,
      -1,   359,    36,   342,    -1,   165,   362,    -1,   167,    -1,
     166,    -1,   168,    -1,   147,    -1,   169,    -1,   170,    -1,
     171,    -1,    78,    -1,    79,    -1,    98,    -1,   172,    -1,
     173,    -1,   174,    -1,   165,   362,    36,   342,    -1,   365,
      -1,   367,    -1,   369,    -1,   371,    -1,   373,    -1,   375,
      -1,   377,    -1,   379,    -1,   381,    -1,   383,    -1,   385,
      -1,   387,    -1,   389,    -1,   391,    -1,   393,    -1,   395,
      -1,    23,   366,     7,    70,     7,    70,    -1,    73,    -1,
      74,    -1,    75,    -1,    77,   368,    -1,    77,    -1,    78,
      -1,    79,    -1,    80,    -1,    81,   370,    -1,    81,    -1,
      82,    -1,    83,    -1,    84,    -1,    80,    -1,    85,   372,
      -1,    85,    -1,    86,    -1,    87,    -1,    88,    -1,    89,
      -1,    90,    -1,    91,   374,    -1,    91,    -1,    92,    -1,
      93,    -1,    94,    -1,    95,    -1,    82,    -1,    96,    -1,
      97,    -1,    98,    -1,    99,    -1,    78,    -1,    79,    -1,
     100,   376,    -1,   100,    -1,    80,    -1,   101,    -1,    99,
      -1,    82,    -1,   102,    -1,   103,    -1,   104,    -1,   105,
     378,    -1,   105,    -1,    92,    -1,   106,    -1,   107,    -1,
      95,    -1,   108,    -1,   109,    -1,    78,    -1,    79,    -1,
     110,   380,    -1,   110,    -1,    80,    -1,   101,    -1,    99,
      -1,   111,    -1,   104,    -1,    82,    -1,   102,    -1,   112,
      -1,   113,   382,    -1,   113,    -1,   108,    -1,    93,    -1,
     114,    -1,   115,    -1,   102,    -1,   116,   384,    -1,   116,
      -1,   115,    -1,   102,    -1,   117,   386,    -1,   117,    -1,
     108,    -1,   118,    -1,   119,    -1,   120,   388,    -1,   120,
      -1,   121,    -1,   122,    -1,    95,    -1,    99,    -1,   123,
     390,    -1,   123,    -1,   121,    -1,   122,    -1,   124,    -1,
      99,    -1,   125,   392,    -1,   125,    -1,   121,    -1,   122,
      -1,   102,    -1,   126,    -1,   127,    -1,   114,    -1,   118,
      -1,   128,    -1,    99,    -1,   129,    -1,   130,   394,    -1,
     130,    -1,   121,    -1,   122,    -1,    80,    -1,   131,   396,
      -1,   131,    -1,   121,    -1,   122,    -1,   132,    -1,    99,
      -1,   398,    -1,   400,    -1,   402,    -1,   404,    -1,   406,
      -1,   408,    -1,   410,    -1,   138,   399,    -1,   108,    -1,
      93,    -1,   133,   401,    -1,   108,    -1,    93,    -1,    80,
      -1,   136,    -1,   134,   403,    -1,   137,   228,    70,   229,
      -1,   135,   405,    -1,   137,    -1,   139,   407,    -1,   108,
      -1,   114,    -1,    96,    -1,   140,    -1,   141,    -1,    82,
      -1,   142,   409,    -1,   108,    -1,    93,    -1,   143,   411,
      -1,   108,    -1,    93,    -1,    80,    -1,   114,    -1,    99,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   557,   557,   558,   575,   576,   579,   580,   583,   591,
     604,   612,   613,   614,   615,   644,   645,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   657,   661,   668,   672,
     680,   684,   688,   695,   702,   708,   712,   719,   723,   733,
     739,   743,   747,   751,   755,   759,   765,   769,   773,   777,
     781,   785,   791,   795,   799,   803,   809,   816,   824,   833,
     834,   837,   838,   839,   840,   841,   842,   845,   846,   849,
     850,   853,   862,   868,   880,   881,   882,   883,   884,   895,
     905,   918,   924,   925,   926,   927,   928,   929,   937,   942,
     943,   944,   945,   950,   955,   960,   965,   970,   973,   977,
     980,   981,   982,   986,   992,   993,   994,   995,  1003,  1008,
    1013,  1016,  1020,  1026,  1027,  1030,  1039,  1049,  1061,  1062,
    1065,  1082,  1099,  1117,  1132,  1143,  1144,  1147,  1150,  1151,
    1154,  1168,  1169,  1172,  1173,  1174,  1175,  1176,  1177,  1180,
    1188,  1196,  1203,  1210,  1217,  1225,  1228,  1235,  1238,  1244,
    1253,  1256,  1263,  1267,  1274,  1287,  1293,  1300,  1301,  1302,
    1303,  1304,  1305,  1306,  1307,  1308,  1309,  1310,  1311,  1312,
    1315,  1319,  1325,  1331,  1336,  1345,  1350,  1355,  1358,  1364,
    1365,  1367,  1373,  1377,  1380,  1384,  1390,  1391,  1394,  1400,
    1404,  1407,  1412,  1417,  1422,  1427,  1434,  1435,  1436,  1437,
    1438,  1439,  1440,  1441,  1444,  1452,  1453,  1454,  1455,  1456,
    1459,  1462,  1469,  1473,  1483,  1493,  1502,  1508,  1511,  1516,
    1523,  1527,  1532,  1536,  1542,  1543,  1550,  1553,  1554,  1557,
    1560,  1564,  1568,  1575,  1576,  1582,  1583,  1584,  1587,  1588,
    1591,  1597,  1601,  1604,  1608,  1614,  1615,  1621,  1622,  1625,
    1634,  1635,  1638,  1644,  1651,  1665,  1674,  1685,  1686,  1687,
    1688,  1689,  1690,  1691,  1694,  1695,  1699,  1705,  1706,  1712,
    1713,  1719,  1720,  1726,  1729,  1730,  1749,  1755,  1763,  1769,
    1775,  1786,  1787,  1788,  1791,  1797,  1798,  1799,  1800,  1803,
    1810,  1815,  1820,  1823,  1827,  1831,  1837,  1838,  1841,  1847,
    1851,  1854,  1858,  1864,  1865,  1868,  1869,  1872,  1873,  1876,
    1880,  1884,  1890,  1891,  1892,  1893,  1894,  1895,  1898,  1902,
    1906,  1910,  1914,  1918,  1924,  1928,  1934,  1935,  1938,  1939,
    1940,  1941,  1942,  1945,  1946,  1947,  1948,  1949,  1950,  1951,
    1952,  1953,  1954,  1955,  1956,  1957,  1958,  1959,  1960,  1961,
    1962,  1965,  1969,  1975,  1981,  1982,  1983,  1984,  1985,  1986,
    1987,  1988,  1989,  1990,  1991,  1992,  1993,  1996,  2002,  2003,
    2004,  2005,  2006,  2007,  2008,  2009,  2010,  2011,  2012,  2013,
    2014,  2015,  2016,  2017,  2020,  2030,  2031,  2032,  2035,  2039,
    2047,  2048,  2049,  2052,  2056,  2064,  2065,  2066,  2067,  2070,
    2074,  2082,  2083,  2084,  2085,  2086,  2089,  2093,  2101,  2102,
    2103,  2104,  2105,  2106,  2107,  2108,  2109,  2110,  2111,  2114,
    2118,  2127,  2128,  2129,  2130,  2131,  2132,  2133,  2136,  2140,
    2148,  2149,  2150,  2151,  2152,  2153,  2154,  2155,  2157,  2161,
    2170,  2171,  2172,  2173,  2174,  2175,  2176,  2177,  2180,  2184,
    2193,  2194,  2195,  2196,  2197,  2200,  2204,  2213,  2214,  2217,
    2221,  2230,  2231,  2232,  2235,  2239,  2248,  2249,  2250,  2251,
    2254,  2258,  2267,  2268,  2269,  2270,  2273,  2277,  2286,  2287,
    2288,  2289,  2290,  2291,  2292,  2293,  2294,  2295,  2298,  2302,
    2311,  2312,  2313,  2316,  2320,  2329,  2330,  2331,  2332,  2335,
    2336,  2337,  2338,  2339,  2340,  2341,  2344,  2350,  2351,  2354,
    2360,  2361,  2362,  2363,  2366,  2372,  2378,  2384,  2387,  2393,
    2394,  2395,  2396,  2397,  2398,  2401,  2407,  2408,  2411,  2417,
    2418,  2419,  2420,  2421
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "\"sets\"", "\"set\"", "\"element\"", "\"map\"", "\"handle\"",
  "\"ruleset\"", "\"inet\"", "\"netdev\"", "\"add\"", "\"update\"",
  "\"create\"", "\"insert\"", "\"delete\"", "\"list\"", "\"flush\"",
  "\"rename\"", "\"describe\"", "\"export\"", "\"monitor\"", "\"accept\"",
  "\"drop\"", "\"continue\"", "\"jump\"", "\"goto\"", "\"return\"",
  "\"to\"", "\"constant\"", "\"interval\"", "\"timeout\"",
  "\"gc-interval\"", "\"elements\"", "\"policy\"", "\"memory\"",
  "\"performance\"", "\"size\"", "\"number\"", "\"string\"",
  "QUOTED_STRING", "\"ll\"", "\"nh\"", "\"th\"", "\"bridge\"", "\"ether\"",
  "\"saddr\"", "\"daddr\"", "\"type\"", "\"vlan\"", "\"id\"", "\"cfi\"",
  "\"pcp\"", "\"arp\"", "\"htype\"", "\"ptype\"", "\"hlen\"", "\"plen\"",
  "\"operation\"", "\"ip\"", "\"version\"", "\"hdrlength\"", "\"tos\"",
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
  "\"nanosecond\"", "\"microsecond\"", "\"millisecond\"", "\"second\"",
  "\"minute\"", "\"hour\"", "\"day\"", "\"week\"", "\"reject\"",
  "\"reset\"", "\"with\"", "\"icmpx\"", "\"snat\"", "\"dnat\"",
  "\"masquerade\"", "\"redirect\"", "\"random\"", "\"fully-random\"",
  "\"persistent\"", "\"queue\"", "\"num\"", "\"bypass\"", "\"fanout\"",
  "\"position\"", "\"comment\"", "\"xml\"", "\"json\"", "'='", "'{'",
  "'}'", "'$'", "'('", "')'", "'|'", "'['", "']'", "$accept", "input",
  "stmt_seperator", "opt_newline", "common_block", "line", "base_cmd",
  "add_cmd", "create_cmd", "insert_cmd", "delete_cmd", "list_cmd",
  "flush_cmd", "rename_cmd", "export_cmd", "monitor_cmd", "monitor_event",
  "monitor_object", "monitor_format", "export_format", "describe_cmd",
  "table_block_alloc", "table_options", "table_block", "chain_block_alloc",
  "chain_block", "set_block_alloc", "set_block", "set_flag_list",
  "set_flag", "map_block_alloc", "map_block", "set_mechanism",
  "set_policy_spec", "data_type", "type_identifier_list",
  "type_identifier", "hook_spec", "policy_spec", "chain_policy",
  "identifier", "string", "time_spec", "family_spec",
  "family_spec_explicit", "table_spec", "tables_spec", "chain_spec",
  "chain_identifier", "set_spec", "set_identifier", "handle_spec",
  "position_spec", "ruleid_spec", "comment_spec", "ruleset_spec", "rule",
  "stmt_list", "stmt", "verdict_stmt", "verdict_map_stmt",
  "verdict_map_expr", "verdict_map_list_expr",
  "verdict_map_list_member_expr", "counter_stmt", "counter_stmt_alloc",
  "counter_args", "counter_arg", "log_stmt", "log_stmt_alloc", "log_args",
  "log_arg", "level_type", "limit_stmt", "time_unit", "reject_stmt",
  "reject_stmt_alloc", "reject_opts", "nat_stmt", "nat_stmt_alloc",
  "nat_stmt_args", "masq_stmt", "masq_stmt_alloc", "redir_stmt",
  "redir_stmt_alloc", "redir_stmt_arg", "nf_nat_flags", "nf_nat_flag",
  "queue_stmt", "queue_stmt_alloc", "queue_stmt_args", "queue_stmt_arg",
  "queue_stmt_flags", "queue_stmt_flag", "set_stmt", "set_stmt_op",
  "match_stmt", "symbol_expr", "integer_expr", "primary_expr",
  "shift_expr", "and_expr", "exclusive_or_expr", "inclusive_or_expr",
  "basic_expr", "concat_expr", "list_expr", "prefix_expr", "range_expr",
  "wildcard_expr", "multiton_expr", "map_expr", "expr", "set_expr",
  "set_list_expr", "set_list_member_expr", "set_elem_expr",
  "set_elem_expr_alloc", "set_elem_options", "set_elem_option",
  "set_lhs_expr", "set_rhs_expr", "initializer_expr", "relational_expr",
  "relational_op", "verdict_expr", "meta_expr", "meta_key",
  "meta_key_qualified", "meta_key_unqualified", "meta_stmt", "ct_expr",
  "ct_key", "ct_stmt", "payload_expr", "payload_raw_expr",
  "payload_base_spec", "eth_hdr_expr", "eth_hdr_field", "vlan_hdr_expr",
  "vlan_hdr_field", "arp_hdr_expr", "arp_hdr_field", "ip_hdr_expr",
  "ip_hdr_field", "icmp_hdr_expr", "icmp_hdr_field", "ip6_hdr_expr",
  "ip6_hdr_field", "icmp6_hdr_expr", "icmp6_hdr_field", "auth_hdr_expr",
  "auth_hdr_field", "esp_hdr_expr", "esp_hdr_field", "comp_hdr_expr",
  "comp_hdr_field", "udp_hdr_expr", "udp_hdr_field", "udplite_hdr_expr",
  "udplite_hdr_field", "tcp_hdr_expr", "tcp_hdr_field", "dccp_hdr_expr",
  "dccp_hdr_field", "sctp_hdr_expr", "sctp_hdr_field", "exthdr_expr",
  "hbh_hdr_expr", "hbh_hdr_field", "rt_hdr_expr", "rt_hdr_field",
  "rt0_hdr_expr", "rt0_hdr_field", "rt2_hdr_expr", "rt2_hdr_field",
  "frag_hdr_expr", "frag_hdr_field", "dst_hdr_expr", "dst_hdr_field",
  "mh_hdr_expr", "mh_hdr_field", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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
     475,    61,   123,   125,    36,    40,    41,   124,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   230,   231,   231,   232,   232,   233,   233,   234,   234,
     234,   235,   235,   235,   235,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   238,   238,   238,   238,   239,
     240,   240,   240,   240,   240,   240,   241,   241,   241,   241,
     241,   241,   242,   242,   242,   242,   243,   244,   245,   246,
     246,   247,   247,   247,   247,   247,   247,   248,   248,   249,
     249,   250,   251,   252,   253,   253,   253,   253,   253,   253,
     253,   254,   255,   255,   255,   255,   255,   255,   256,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   258,   258,
     259,   259,   259,   260,   261,   261,   261,   261,   261,   261,
     261,   262,   262,   263,   263,   264,   265,   265,   266,   266,
     267,   267,   267,   267,   268,   269,   269,   270,   271,   271,
     272,   273,   273,   274,   274,   274,   274,   274,   274,   275,
     276,   277,   278,   279,   280,   281,   281,   282,   282,   283,
     284,   284,   285,   285,   286,   287,   287,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     289,   289,   290,   291,   291,   292,   292,   292,   293,   294,
     294,   295,   296,   296,   297,   297,   298,   298,   299,   300,
     300,   301,   301,   301,   301,   301,   302,   302,   302,   302,
     302,   302,   302,   302,   303,   304,   304,   304,   304,   304,
     305,   306,   307,   307,   307,   307,   307,   308,   309,   309,
     310,   310,   310,   310,   311,   311,   312,   313,   313,   314,
     315,   315,   315,   316,   316,   317,   317,   317,   318,   318,
     319,   320,   320,   321,   321,   322,   322,   323,   323,   324,
     325,   325,   326,   327,   327,   327,   328,   329,   329,   329,
     329,   329,   329,   329,   330,   330,   330,   331,   331,   332,
     332,   333,   333,   334,   335,   335,   336,   336,   337,   338,
     339,   340,   340,   340,   341,   342,   342,   342,   342,   343,
     344,   344,   344,   345,   345,   345,   346,   346,   347,   348,
     348,   349,   349,   350,   350,   351,   351,   352,   352,   353,
     353,   353,   354,   354,   354,   354,   354,   354,   355,   355,
     355,   355,   355,   355,   356,   356,   357,   357,   358,   358,
     358,   358,   358,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   360,   360,   361,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   363,   364,   364,
     364,   364,   364,   364,   364,   364,   364,   364,   364,   364,
     364,   364,   364,   364,   365,   366,   366,   366,   367,   367,
     368,   368,   368,   369,   369,   370,   370,   370,   370,   371,
     371,   372,   372,   372,   372,   372,   373,   373,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   374,   375,
     375,   376,   376,   376,   376,   376,   376,   376,   377,   377,
     378,   378,   378,   378,   378,   378,   378,   378,   379,   379,
     380,   380,   380,   380,   380,   380,   380,   380,   381,   381,
     382,   382,   382,   382,   382,   383,   383,   384,   384,   385,
     385,   386,   386,   386,   387,   387,   388,   388,   388,   388,
     389,   389,   390,   390,   390,   390,   391,   391,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   393,   393,
     394,   394,   394,   395,   395,   396,   396,   396,   396,   397,
     397,   397,   397,   397,   397,   397,   398,   399,   399,   400,
     401,   401,   401,   401,   402,   403,   404,   405,   406,   407,
     407,   407,   407,   407,   407,   408,   409,   409,   410,   411,
     411,   411,   411,   411
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       2,     1,     1,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     6,     2,     6,
       3,     2,     6,     6,     3,     2,     6,     2,     6,     3,
       2,     2,     2,     2,     2,     3,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     1,     3,     0,
       1,     0,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     1,     0,     2,     0,     2,     2,     3,     8,     8,
       8,     0,     0,     2,     2,     3,     3,     3,     0,     0,
       2,     2,     4,     4,     4,     4,     4,     3,     3,     1,
       1,     1,     1,     0,     0,     2,     2,     6,     4,     4,
       3,     2,     2,     1,     1,     1,     1,     3,     1,     1,
       6,     7,     8,     9,     2,     1,     1,     1,     1,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     2,     1,     0,     2,     0,     2,     3,
       0,     2,     0,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     2,     1,     3,     3,     5,     1,
       2,     1,     1,     2,     2,     2,     1,     2,     1,     1,
       2,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     1,     1,     1,     1,     1,
       2,     1,     0,     4,     4,     4,     3,     2,     1,     1,
       1,     3,     2,     2,     1,     2,     1,     2,     1,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     2,
       1,     1,     2,     2,     1,     1,     3,     1,     1,     4,
       1,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     3,
       1,     3,     3,     3,     3,     5,     1,     2,     1,     1,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     2,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     2,
       1,     1,     1,     1,     2,     4,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,   131,   131,
     131,   131,   131,   131,   135,   138,   131,     0,     0,     0,
       0,     0,     0,     0,     0,    59,   137,   136,   133,   134,
      12,    11,     3,     0,    15,     0,   132,     0,   145,     0,
      10,     0,   127,     0,    26,    28,     0,     0,    88,     0,
     103,    16,   131,   131,    17,   131,    18,   131,   131,   131,
     131,   131,   131,    19,   131,   131,   131,   131,   131,   152,
      20,   131,   131,   131,   152,    21,   131,    22,     0,   256,
     128,   129,   389,   394,   400,   407,   420,   429,   439,   449,
     456,   460,   465,   471,   477,   489,   494,     0,     0,     0,
       0,     0,     0,     0,     0,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,     0,     0,     0,    25,   253,   257,   258,
      71,   261,   325,   262,   259,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   260,   499,   500,   501,   502,   503,   504,   505,    69,
      70,    23,    57,    60,    24,    61,    14,    13,   139,   141,
       0,   147,   280,     0,   318,   319,   320,     0,     0,   323,
       0,     0,   181,   188,     0,   211,   218,   219,   226,   229,
     240,     7,    31,   150,   155,   157,   171,   159,   179,   161,
     186,   162,   163,   212,   164,     0,   167,   224,   168,   228,
     165,   238,   169,   158,   264,   267,   269,   271,   273,   274,
     285,   281,   282,   283,   286,   288,     0,   287,   252,   170,
     325,   160,   166,     8,     0,     0,     0,    30,   143,     0,
      34,     0,    35,    37,     0,    40,    41,    42,    43,     0,
      44,    46,   140,    47,    48,    49,    50,   153,    51,    52,
      53,    54,    55,     0,   385,   386,   387,   255,     0,   390,
     391,   392,   388,   398,   395,   396,   397,   393,   401,   402,
     403,   404,   405,   399,   417,   418,   412,   408,   409,   410,
     411,   413,   414,   415,   416,   406,   421,   424,   423,   422,
     425,   426,   427,   419,   436,   437,   430,   433,   431,   432,
     434,   435,   428,   440,   445,   442,   441,   446,   444,   443,
     447,   438,   451,   454,   450,   452,   453,   448,   458,   457,
     455,   461,   462,   463,   459,   468,   469,   466,   467,   464,
     475,   472,   473,   474,   470,   486,   480,   483,   484,   478,
     479,   481,   482,   485,   487,   476,   492,   490,   491,   488,
     498,   495,   496,   497,   493,   512,   511,   510,   513,   509,
       0,   514,   517,   516,   508,   507,   506,   524,   521,   519,
     520,   522,   523,   518,   527,   526,   525,   531,   530,   533,
     529,   532,   528,   328,   331,   332,   329,   330,   324,   326,
     327,   361,   362,   363,   357,   355,   354,   356,   358,   359,
     360,   364,   365,   366,   353,   254,     0,    62,    63,    65,
      64,    66,    67,   146,     0,   149,   250,   251,     0,   321,
     322,   324,   353,     0,     6,     0,     0,   290,     0,   154,
     156,     0,     0,   180,   182,     0,     0,     0,     0,     0,
     187,   189,     0,   210,     0,   217,   285,   220,   235,   236,
     237,   225,   233,     0,   227,   231,     0,   247,   248,   239,
     241,   244,   245,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   312,   313,   314,   315,   316,   317,   274,
     310,   309,     0,     0,   308,   307,     0,    74,    82,    89,
     104,     0,     0,    39,    45,    56,     0,     0,   263,    58,
      68,   148,   303,   304,     0,   296,   298,     0,     0,     0,
       7,     7,     7,   289,   151,   184,   185,   183,   191,   192,
     193,   194,   196,   197,   198,   199,   200,   201,   202,   203,
     195,   190,     0,     0,     0,     0,   222,   223,     0,     0,
     230,   243,   242,     0,   265,   266,   268,   270,   272,   278,
     279,   275,     0,     7,   172,   284,     0,     0,   311,   352,
       9,     0,     0,     0,     0,    74,    82,     0,     0,     0,
     249,     0,     0,   297,   299,   351,   367,     0,   293,     0,
     294,   292,   291,     0,     0,   216,     0,   221,   234,   232,
     246,   174,     0,     0,   175,   276,   277,     0,     0,     0,
       0,    27,    76,    75,     0,     0,     0,    29,    84,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,    91,    90,     0,     0,     0,     0,    33,   106,   105,
       0,     0,     0,     0,   515,   130,   301,   302,   300,   205,
     206,   207,   208,   209,   204,   274,   305,     7,   306,   213,
     214,   215,     0,     7,   173,   142,    81,   144,    88,   103,
      73,    77,   125,   126,   124,     0,    85,    86,    87,     0,
       0,     0,   114,   113,   111,   112,   118,   119,     0,   115,
     116,   100,   101,   102,     0,    99,    97,     0,     0,     0,
     110,    36,    38,   384,   295,     0,   177,   176,     0,     0,
       0,     0,    94,    95,    96,    92,     0,     0,    93,   109,
       0,   108,     7,    82,    89,   104,     0,   117,    98,     0,
     178,     0,     0,     0,     0,     0,   107,     0,     0,     0,
       0,     0,   120,    78,    79,    80,     0,   121,     0,   122,
     123
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   618,   435,   619,    32,    33,    34,    54,    56,
      63,    70,    75,    77,   161,   164,   165,   422,   509,   162,
     126,   235,   614,   571,   236,   572,   239,   573,   694,   695,
     241,   574,   633,   684,   688,   689,   690,   620,   621,   674,
     267,   127,   646,    35,    36,    37,   253,    38,   666,    48,
     668,   171,   425,    39,   439,   258,   622,   193,   194,   195,
     196,   564,   603,   604,   197,   198,   443,   444,   199,   200,
     450,   451,   540,   201,   654,   202,   203,   453,   204,   205,
     455,   206,   207,   208,   209,   464,   461,   462,   210,   211,
     469,   470,   471,   472,   212,   428,   213,   128,   129,   214,
     215,   216,   217,   218,   219,   456,   490,   221,   222,   223,
     224,   225,   226,   227,   436,   437,   521,   515,   583,   584,
     516,   657,   496,   228,   492,   229,   131,   398,   399,   132,
     231,   133,   414,   232,   134,   135,   268,   136,   272,   137,
     277,   138,   283,   139,   295,   140,   303,   141,   312,   142,
     321,   143,   327,   144,   330,   145,   334,   146,   339,   147,
     344,   148,   355,   149,   359,   150,   364,   151,   152,   376,
     153,   369,   154,   371,   155,   373,   156,   383,   157,   386,
     158,   392
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -602
static const yytype_int16 yypact[] =
{
    -602,  2135,  -602,    69,  -602,  -602,   -16,     8,   152,   152,
     152,   152,   152,   152,  -602,  -602,   265,   104,    35,   369,
     510,   282,    61,  1969,   101,    88,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,   334,  -602,     8,  -602,     8,    62,  1516,
    -602,    69,  -602,   -97,   -90,   -59,  1516,     8,  -602,   -47,
    -602,  -602,   152,   152,  -602,   152,  -602,   152,   152,   152,
     152,   152,   152,  -602,   152,   152,   152,   152,   152,   152,
    -602,   152,   152,   152,   152,  -602,   152,  -602,   156,  -602,
    -602,  -602,   -14,   269,   372,   284,   494,   358,   292,   202,
     -41,   172,   157,   147,   430,   -26,    74,    75,    41,    44,
      30,   168,    63,   146,   263,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,   -20,     8,  1969,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,   190,  -602,  -602,  -602,  -602,
     114,    -2,  -602,   301,  -602,  -602,  -602,     8,     8,  -602,
     263,   -20,  -602,  -602,    12,  -602,  -602,  -602,  -602,  -602,
    -602,   213,  -602,  1342,  -602,  -602,  -602,  -602,   188,  -602,
     435,  -602,  -602,    34,  -602,   363,  -602,   118,  -602,   -12,
    -602,   227,  -602,  -602,  -602,   413,   223,   226,    22,   144,
     243,  -602,  -602,  -602,  -602,  -602,  1196,  -602,  -602,  -602,
     217,  -602,  -602,  -602,  1662,    36,    40,  -602,  -602,    55,
    -602,    83,   -90,   -59,  1516,  -602,  -602,  -602,  -602,   -47,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,     8,  -602,  -602,  -602,  -602,   259,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
      47,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,    59,  -602,  -602,  -602,
    -602,  -602,   101,  -602,   253,  -602,  -602,  -602,  1760,  -602,
    -602,   261,   295,   272,  -602,  1662,     9,  -602,   360,  -602,
    -602,   277,   287,   188,  -602,   360,   297,   303,   305,   438,
     435,  -602,   -65,  -602,  1662,   118,   122,   328,  -602,  -602,
    -602,   364,  -602,  1662,  -602,   364,  1662,  -602,  -602,   227,
    -602,   378,  -602,  1969,  1969,  1969,  1969,  1969,   318,  1969,
    1969,    -3,  1662,  -602,  -602,  -602,  -602,  -602,  -602,   196,
     383,  -602,  1662,  1662,   383,  -602,    69,  -602,  -602,  -602,
    -602,   173,   175,  -602,  -602,  -602,   331,   375,  -602,  -602,
    -602,  -602,   441,  -602,    39,   -33,  -602,  1662,  1662,   464,
     213,   434,   213,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,   405,   407,   252,   411,  -602,   364,  1662,   118,
     118,  -602,  -602,   236,  -602,  -602,   413,   223,   226,  -602,
    -602,  -602,     8,   213,  -602,  -602,  1969,  1969,  -602,  -602,
    -602,   103,   688,    18,    51,  -602,  -602,   482,   270,     8,
    -602,   419,   360,   -33,  -602,  -602,  -602,   437,  -602,  1873,
    -602,  1662,  -602,   421,   429,  -602,   432,  -602,  -602,   364,
    -602,  -602,  1760,    10,  -602,  -602,  -602,     8,     8,     8,
     433,  -602,  -602,  -602,    69,   420,   459,  -602,  -602,  -602,
      69,    69,    69,   419,   419,   288,   410,   461,   -29,   409,
    -602,  -602,  -602,    69,   312,   -29,   409,  -602,  -602,  -602,
      69,   166,   863,   465,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,   441,   213,  -602,  -602,
    -602,  -602,   503,   213,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,   507,  -602,  -602,  -602,    69,
      69,   -47,  -602,  -602,  -602,  -602,  -602,  -602,    69,   530,
    -602,  -602,  -602,  -602,   308,  -602,  -602,   -47,   537,   308,
    -602,  -602,  -602,  -602,  -602,   545,  1760,  -602,   325,   327,
     332,   489,  -602,  -602,  -602,  -602,   -29,   409,  -602,  -602,
     -29,  -602,   213,  -602,  -602,  -602,    19,  -602,  -602,    69,
    -602,  1038,    25,    96,   490,    16,  -602,    69,    69,    69,
     456,   493,  -602,  -602,  -602,  -602,    45,  -602,   495,  -602,
    -602
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -602,  -602,    -1,  -450,     7,  -602,  -602,   551,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,   149,
    -602,   326,  -602,    -6,  -236,  -549,   -93,  -147,   -57,  -135,
     -86,  -141,  -551,  -602,  -601,  -602,  -130,  -602,  -602,  -602,
       2,  -392,  -142,   145,    68,   275,   522,    27,  -602,   174,
     -19,  -602,  -602,    53,  -602,   517,   -21,  -602,   399,  -602,
    -602,  -602,  -602,   -69,  -602,  -602,  -602,   162,  -602,  -602,
    -602,   158,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -196,    81,  -602,  -602,
    -602,   143,  -602,    78,  -602,  -602,  -602,   127,  -602,   -17,
     167,   169,   170,  -602,  -120,   -36,   412,  -602,  -602,  -602,
    -414,  -602,  -193,   -48,  -602,   121,  -413,  -602,  -602,    67,
    -602,  -602,  -602,  -602,  -602,  -561,  -602,   471,  -602,   -35,
    -602,  -602,   463,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,
    -602,  -602
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -132
static const yytype_int16 yytable[] =
{
      30,   240,    40,   220,   230,   416,   130,   502,    31,    43,
     220,   230,   457,   465,   513,   514,   522,   663,   192,     3,
     562,   513,     4,   640,     5,   237,     3,   642,   658,     4,
     581,     5,   167,   491,   698,   542,    45,   168,   741,   169,
     233,   495,   686,     6,     7,   543,   524,   734,   463,   238,
       6,     7,     3,   528,   356,     4,    41,     5,   401,   402,
     544,   328,   579,    46,   269,   270,   271,   748,    55,   400,
     588,   590,   591,     4,   329,     5,     6,     7,   403,    42,
     243,   623,   624,   625,   626,   246,   742,   627,   623,   624,
     625,   626,    76,   254,   627,   357,   358,     3,   628,   260,
       4,   170,     5,   263,     3,   628,   489,     4,   244,     5,
      80,    81,   247,   602,   489,   749,   634,   626,   687,   729,
     627,     6,     7,   374,   234,   735,   415,   404,     6,     7,
     480,   635,   -72,    52,   607,    53,   629,   257,   375,   608,
     545,   609,   257,   629,   722,   400,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   365,   384,   220,   230,   163,
     482,   634,   626,   -81,   478,   627,   479,     3,   366,   636,
       4,   385,     5,   360,   731,   191,   635,   513,   370,   429,
     430,   372,   640,   367,   423,   582,    49,    50,   513,   662,
     647,     6,     7,    14,    15,   361,   362,   607,   458,   459,
     460,   504,   608,   566,   609,   433,   363,   704,   220,   230,
     252,   368,   252,   706,   636,   424,   478,   434,   479,   563,
     417,   610,   418,   503,   419,   420,   387,    42,    26,   264,
     265,   266,   523,   664,   248,   249,   250,    27,   452,   388,
     475,   630,   256,    28,   476,   389,   340,   261,   738,   477,
     377,   480,   335,   493,   390,   421,   336,    29,   497,   547,
     391,   546,   498,   124,   378,   505,   506,   481,   341,   342,
     550,   343,   730,   551,   637,   507,   379,   499,   337,   338,
     331,   482,   380,    44,   610,   508,    47,    47,    47,   565,
     332,   333,   513,   662,     8,   322,     9,   517,    10,   568,
     569,    11,    12,    13,   323,   500,    14,    15,   381,   382,
     324,    71,     4,    72,     5,   717,   325,   326,    73,   739,
     159,   160,    74,   511,   585,   586,   611,   242,   458,   459,
     460,   518,   245,   548,   166,    47,    47,    47,     4,   251,
       5,    26,   519,    47,   426,   427,   259,   525,    47,   273,
      27,   274,   275,   276,   599,   597,    28,   526,   393,   560,
     561,   394,   284,   285,   441,   442,   286,   529,   454,   395,
      29,   549,   313,   530,   314,   531,   287,   288,   289,   290,
     291,   292,   293,   294,   172,   553,    78,   520,   559,   701,
     567,   315,   512,   316,   317,   575,   318,   576,    57,   512,
      58,   577,    59,   319,   320,    60,    61,    62,   396,   397,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   473,   474,
     708,    80,    81,    79,    80,    81,   304,   305,   434,   589,
      82,   466,   467,   468,    83,   578,   605,   606,    84,   480,
     306,   467,   468,   307,    85,   595,   554,   555,   278,   279,
     280,   281,   282,    86,   308,   309,   310,   311,    87,   655,
     691,   692,   693,    88,   672,   673,    89,   682,   683,    90,
      91,   679,   680,    92,   587,   593,    93,   594,    94,   643,
     645,   596,   659,    95,    96,   570,    97,    98,    99,   644,
     660,   100,   101,   661,   670,   102,   103,   104,   705,   681,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   345,
     675,   685,   346,   697,   711,   703,   220,   230,   716,    64,
      65,    66,   720,   520,   347,    67,    68,   723,   348,   724,
      69,   349,   350,   656,   725,   512,   351,   352,   353,   354,
     726,   740,   746,   747,   601,   750,   512,    51,   501,   641,
     612,   510,   631,   638,   296,   709,   297,   732,   613,   699,
     632,   639,   728,   710,   733,   191,   727,   124,   125,   255,
     669,   262,   440,   298,   707,   299,   300,   301,   302,   174,
     175,   176,   177,   178,   179,   527,   220,   230,   541,   665,
     667,   667,   552,   671,   445,   446,   447,   448,   449,   676,
     677,   678,   532,   533,   534,   535,   536,   537,   538,   539,
     598,   600,   696,   714,   649,   650,   651,   652,   653,   700,
     612,   580,   556,   592,   432,   557,   494,   558,   613,   719,
     648,   431,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     512,     0,     0,     0,     0,     0,     0,     0,   712,   713,
       0,     0,     0,     0,     0,     0,     0,   715,     0,     3,
       0,     0,     4,   718,     5,   220,   230,     0,   721,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   172,
       0,    78,     0,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,     0,     0,     0,   736,     0,
       0,   631,   638,     0,     0,     0,   743,   744,   745,   632,
     639,     0,   174,   175,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,   615,     0,     0,     0,    79,    80,
      81,     0,     0,     0,     0,    82,     0,     0,   616,    83,
       0,     0,     0,    84,     0,     0,     0,     0,     0,    85,
       0,     0,     0,     0,     0,     0,     0,     0,    86,     0,
       0,     0,     0,    87,     0,     0,     0,     0,    88,     0,
       0,    89,     0,     0,    90,    91,     0,     0,    92,     0,
       0,    93,     0,    94,     0,     0,     0,     0,    95,    96,
       0,    97,    98,    99,     0,     0,   100,   101,     0,     0,
     102,   103,   180,     0,     0,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   182,     3,     0,   183,     4,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     184,     0,     0,     0,   172,     0,    78,     0,     6,     7,
     185,     0,     0,     0,   186,   187,   188,   189,     0,   173,
       0,   190,     0,     0,     0,     0,     0,     0,     0,     0,
     191,   617,   124,   125,     0,     0,     0,   174,   175,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,   615,
       0,     0,     0,    79,    80,    81,     0,     0,     0,     0,
      82,     0,     0,   616,    83,     0,     0,     0,    84,     0,
       0,     0,     0,     0,    85,     0,     0,     0,     0,     0,
       0,     0,     0,    86,     0,     0,     0,     0,    87,     0,
       0,     0,     0,    88,     0,     0,    89,     0,     0,    90,
      91,     0,     0,    92,     0,     0,    93,     0,    94,     0,
       0,     0,     0,    95,    96,     0,    97,    98,    99,     0,
       0,   100,   101,     0,     0,   102,   103,   180,     0,     0,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,     3,
       0,   183,     4,     0,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   184,     0,     0,     0,   172,
       0,    78,     0,     6,     7,   185,     0,     0,     0,   186,
     187,   188,   189,     0,   173,     0,   190,     0,     0,     0,
       0,     0,     0,     0,     0,   191,   702,   124,   125,     0,
       0,     0,   174,   175,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,   615,     0,     0,     0,    79,    80,
      81,     0,     0,     0,     0,    82,     0,     0,   616,    83,
       0,     0,     0,    84,     0,     0,     0,     0,     0,    85,
       0,     0,     0,     0,     0,     0,     0,     0,    86,     0,
       0,     0,     0,    87,     0,     0,     0,     0,    88,     0,
       0,    89,     0,     0,    90,    91,     0,     0,    92,     0,
       0,    93,     0,    94,     0,     0,     0,     0,    95,    96,
       0,    97,    98,    99,     0,     0,   100,   101,     0,     0,
     102,   103,   180,     0,     0,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   181,     0,   483,   484,   485,   486,   487,
     488,     0,     0,   182,     0,     0,   183,   172,     0,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     184,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     185,     0,     0,     0,   186,   187,   188,   189,     0,     0,
       0,   190,     0,     0,     0,     0,     0,     0,     0,     0,
     191,   737,   124,   125,     0,     0,    79,    80,    81,     0,
       0,     0,     0,    82,     0,     0,     0,    83,     0,     0,
       0,    84,     0,     0,     0,     0,     0,    85,     0,     0,
       0,     0,     0,     0,     0,     0,    86,     0,     0,     0,
       0,    87,     0,     0,     0,     0,    88,     0,     0,    89,
       0,     0,    90,    91,     0,     0,    92,     0,     0,    93,
       0,    94,     0,     0,     0,     0,    95,    96,     0,    97,
      98,    99,     0,     0,   100,   101,     0,     0,   102,   103,
     104,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,     0,   172,     0,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   173,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   174,   175,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    79,    80,    81,     0,     0,     0,   191,    82,
     124,   125,     0,    83,     0,     0,     0,    84,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,     0,     0,    87,     0,     0,
       0,     0,    88,     0,     0,    89,     0,     0,    90,    91,
       0,     0,    92,     0,     0,    93,     0,    94,     0,     0,
       0,     0,    95,    96,     0,    97,    98,    99,     0,     0,
     100,   101,     0,     0,   102,   103,   180,     0,     0,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,     0,     0,
     183,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   184,     0,     0,   172,     0,    78,
       0,     0,     0,     0,   185,     0,     0,     0,   186,   187,
     188,   189,   173,     0,     0,   190,     0,     0,     0,     0,
     438,     0,     0,     0,   191,     0,   124,   125,     0,     0,
     174,   175,   176,   177,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    79,    80,    81,     0,
       0,     0,     0,    82,     0,     0,     0,    83,     0,     0,
       0,    84,     0,     0,     0,     0,     0,    85,     0,     0,
       0,     0,     0,     0,     0,     0,    86,     0,     0,     0,
       0,    87,     0,     0,     0,     0,    88,     0,     0,    89,
       0,     0,    90,    91,     0,     0,    92,     0,     0,    93,
       0,    94,     0,     0,     0,     0,    95,    96,     0,    97,
      98,    99,     0,     0,   100,   101,     0,     0,   102,   103,
     180,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   181,     0,   172,     0,    78,     0,     0,     0,     0,
       0,   182,     0,     0,   183,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   184,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   185,     0,
       0,     0,   186,   187,   188,   189,     0,     0,     0,   190,
       0,     0,    79,    80,    81,     0,     0,     0,   191,    82,
     124,   125,     0,    83,     0,     0,     0,    84,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,     0,     0,    87,     0,     0,
       0,     0,    88,     0,     0,    89,     0,     0,    90,    91,
       0,   172,    92,    78,     0,    93,     0,    94,     0,     0,
       0,     0,    95,    96,     0,    97,    98,    99,     0,     0,
     100,   101,     0,     0,   102,   103,   104,     0,     0,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,     0,     0,
      79,    80,    81,     0,     0,     0,     0,    82,     0,     0,
       0,    83,     0,     0,     0,    84,     0,     0,     0,     0,
       0,    85,     0,     0,     0,     0,     0,     0,     0,     0,
      86,     0,     0,     0,     0,    87,     0,     0,     0,     0,
      88,     0,     0,    89,     0,     0,    90,    91,     0,     0,
      92,     0,     0,    93,   191,    94,   124,   125,     0,     0,
      95,    96,     0,    97,    98,    99,    78,     0,   100,   101,
       0,     0,   102,   103,   104,     0,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,     0,   174,   175,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,    80,    81,     0,     0,     0,     0,
      82,     0,     0,     0,    83,     0,     0,     0,    84,     0,
       0,     0,     0,     0,    85,     0,     0,     0,     0,     0,
       0,     0,     0,    86,     0,     0,     0,     0,    87,     0,
       0,     0,     0,    88,   124,   125,    89,     0,     0,    90,
      91,     0,    78,    92,     0,     0,    93,     0,    94,     0,
       0,     0,     0,    95,    96,     0,    97,    98,    99,     0,
       0,   100,   101,     0,     0,   102,   103,   104,     0,     0,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    79,
      80,    81,     0,     0,     0,     0,    82,     0,     0,     0,
      83,     0,     0,     0,    84,     0,     0,     0,     0,     0,
      85,     0,     0,     0,     0,     0,     0,     0,     0,    86,
       0,     0,     0,     0,    87,     0,     0,     0,     0,    88,
       0,     0,    89,     0,     0,    90,    91,     0,     0,    92,
       0,     0,    93,     0,    94,     0,     0,   124,   125,    95,
      96,     0,    97,    98,    99,     0,     0,   100,   101,     0,
       0,   102,   103,   104,     0,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,     2,     3,     0,     0,     4,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     7,     0,     0,     8,     0,     9,     0,    10,     0,
       0,    11,    12,    13,     0,     0,    14,    15,    16,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
       0,     0,     0,   124,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -131,     0,     0,     0,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
      27,     0,     0,     0,     0,     0,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-602))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    49,     3,    39,    39,   125,    23,   243,     1,     7,
      46,    46,   205,   209,   428,   428,     7,     7,    39,     1,
      23,   435,     4,   574,     6,    46,     1,   576,   589,     4,
      63,     6,    33,   226,   635,   100,     9,    35,    22,    37,
      41,   234,    71,    25,    26,   110,   438,    28,    60,    47,
      25,    26,     1,   445,    80,     4,    72,     6,    78,    79,
     125,   102,    23,    10,    78,    79,    80,    22,    33,   104,
     520,   521,   522,     4,   115,     6,    25,    26,    98,    71,
      53,    63,    64,    65,    66,    58,    70,    69,    63,    64,
      65,    66,    31,    66,    69,   121,   122,     1,    80,    72,
       4,    39,     6,    76,     1,    80,   226,     4,    55,     6,
      71,    72,    59,   563,   234,    70,    65,    66,   147,   720,
      69,    25,    26,    93,   221,   106,   124,   147,    25,    26,
       8,    80,   222,    29,    31,    31,   118,    69,   108,    36,
     205,    38,    74,   118,   705,   180,   166,   167,   168,   169,
     170,   171,   172,   173,   174,    80,    93,   193,   193,    71,
      38,    65,    66,   222,    20,    69,    22,     1,    93,   118,
       4,   108,     6,    99,   723,   222,    80,   591,   137,   177,
     178,   137,   733,   108,    70,   218,    12,    13,   602,   602,
     582,    25,    26,    41,    42,   121,   122,    31,   210,   211,
     212,   249,    36,     7,    38,   193,   132,   657,   244,   244,
      65,   136,    67,   663,   118,   217,    20,     4,    22,   222,
      30,   118,    32,   244,    34,    35,    80,    71,    76,    73,
      74,    75,   223,   223,    60,    61,    62,    85,   204,    93,
      17,   223,    68,    91,    18,    99,    99,    73,   223,   227,
      82,     8,    95,    36,   108,    65,    99,   105,   222,   455,
     114,   454,   222,   224,    96,   263,     7,    24,   121,   122,
     463,   124,   722,   466,   223,   228,   108,   222,   121,   122,
     108,    38,   114,     8,   118,   226,    11,    12,    13,   482,
     118,   119,   706,   706,    29,    93,    31,    36,    33,   492,
     493,    36,    37,    38,   102,   222,    41,    42,   140,   141,
     108,    29,     4,    31,     6,     7,   114,   115,    36,   223,
     219,   220,    40,    70,   517,   518,   223,    52,   210,   211,
     212,    36,    57,     5,     0,    60,    61,    62,     4,    64,
       6,    76,    70,    68,    43,    44,    71,    70,    73,    80,
      85,    82,    83,    84,   550,   548,    91,    70,    95,   479,
     480,    98,    78,    79,   176,   177,    82,    70,     5,   106,
     105,     7,    80,    70,    82,    70,    92,    93,    94,    95,
      96,    97,    98,    99,    21,     7,    23,   435,    70,   223,
       7,    99,   428,   101,   102,   222,   104,   222,    29,   435,
      31,    70,    33,   111,   112,    36,    37,    38,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,    15,    16,
     666,    71,    72,    70,    71,    72,    78,    79,     4,     5,
      77,   214,   215,   216,    81,    70,   566,   567,    85,     8,
      92,   215,   216,    95,    91,   203,   473,   474,    86,    87,
      88,    89,    90,   100,   106,   107,   108,   109,   105,   589,
      61,    62,    63,   110,    54,    55,   113,    67,    68,   116,
     117,   623,   624,   120,    20,    80,   123,    80,   125,     7,
      71,    80,    71,   130,   131,   496,   133,   134,   135,   229,
      71,   138,   139,    71,    71,   142,   143,   144,     5,   221,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    99,
      71,    70,   102,   221,    27,    70,   572,   572,     8,    29,
      30,    31,     5,   591,   114,    35,    36,   222,   118,   222,
      40,   121,   122,   589,   222,   591,   126,   127,   128,   129,
      71,    71,   106,    70,   562,    70,   602,    16,   242,   575,
     571,   422,   573,   574,    80,   668,    82,   724,   571,   636,
     573,   574,   717,   669,   725,   222,   716,   224,   225,    67,
     609,    74,   193,    99,   663,   101,   102,   103,   104,    54,
      55,    56,    57,    58,    59,   443,   642,   642,   450,   607,
     608,   609,   469,   614,   179,   180,   181,   182,   183,   620,
     621,   622,   184,   185,   186,   187,   188,   189,   190,   191,
     549,   553,   633,   681,   197,   198,   199,   200,   201,   640,
     641,   514,   475,   522,   181,   476,   234,   477,   641,   697,
     583,   180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     706,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   679,   680,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   688,    -1,     1,
      -1,    -1,     4,   694,     6,   731,   731,    -1,   699,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,   729,    -1,
      -1,   732,   733,    -1,    -1,    -1,   737,   738,   739,   732,
     733,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    80,    81,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,
      -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,   110,    -1,
      -1,   113,    -1,    -1,   116,   117,    -1,    -1,   120,    -1,
      -1,   123,    -1,   125,    -1,    -1,    -1,    -1,   130,   131,
      -1,   133,   134,   135,    -1,    -1,   138,   139,    -1,    -1,
     142,   143,   144,    -1,    -1,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   175,     1,    -1,   178,     4,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     192,    -1,    -1,    -1,    21,    -1,    23,    -1,    25,    26,
     202,    -1,    -1,    -1,   206,   207,   208,   209,    -1,    36,
      -1,   213,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     222,   223,   224,   225,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    80,    81,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,   110,    -1,    -1,   113,    -1,    -1,   116,
     117,    -1,    -1,   120,    -1,    -1,   123,    -1,   125,    -1,
      -1,    -1,    -1,   130,   131,    -1,   133,   134,   135,    -1,
      -1,   138,   139,    -1,    -1,   142,   143,   144,    -1,    -1,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,     1,
      -1,   178,     4,    -1,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,    21,
      -1,    23,    -1,    25,    26,   202,    -1,    -1,    -1,   206,
     207,   208,   209,    -1,    36,    -1,   213,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   222,   223,   224,   225,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    80,    81,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,
      -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,   110,    -1,
      -1,   113,    -1,    -1,   116,   117,    -1,    -1,   120,    -1,
      -1,   123,    -1,   125,    -1,    -1,    -1,    -1,   130,   131,
      -1,   133,   134,   135,    -1,    -1,   138,   139,    -1,    -1,
     142,   143,   144,    -1,    -1,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,    -1,     9,    10,    11,    12,    13,
      14,    -1,    -1,   175,    -1,    -1,   178,    21,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     202,    -1,    -1,    -1,   206,   207,   208,   209,    -1,    -1,
      -1,   213,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     222,   223,   224,   225,    -1,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,    -1,    -1,   113,
      -1,    -1,   116,   117,    -1,    -1,   120,    -1,    -1,   123,
      -1,   125,    -1,    -1,    -1,    -1,   130,   131,    -1,   133,
     134,   135,    -1,    -1,   138,   139,    -1,    -1,   142,   143,
     144,    -1,    -1,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    -1,    -1,    -1,   222,    77,
     224,   225,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      -1,    -1,   110,    -1,    -1,   113,    -1,    -1,   116,   117,
      -1,    -1,   120,    -1,    -1,   123,    -1,   125,    -1,    -1,
      -1,    -1,   130,   131,    -1,   133,   134,   135,    -1,    -1,
     138,   139,    -1,    -1,   142,   143,   144,    -1,    -1,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,    -1,
     178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   192,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,   202,    -1,    -1,    -1,   206,   207,
     208,   209,    36,    -1,    -1,   213,    -1,    -1,    -1,    -1,
     218,    -1,    -1,    -1,   222,    -1,   224,   225,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,    -1,   110,    -1,    -1,   113,
      -1,    -1,   116,   117,    -1,    -1,   120,    -1,    -1,   123,
      -1,   125,    -1,    -1,    -1,    -1,   130,   131,    -1,   133,
     134,   135,    -1,    -1,   138,   139,    -1,    -1,   142,   143,
     144,    -1,    -1,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
      -1,   175,    -1,    -1,   178,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   202,    -1,
      -1,    -1,   206,   207,   208,   209,    -1,    -1,    -1,   213,
      -1,    -1,    70,    71,    72,    -1,    -1,    -1,   222,    77,
     224,   225,    -1,    81,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      -1,    -1,   110,    -1,    -1,   113,    -1,    -1,   116,   117,
      -1,    21,   120,    23,    -1,   123,    -1,   125,    -1,    -1,
      -1,    -1,   130,   131,    -1,   133,   134,   135,    -1,    -1,
     138,   139,    -1,    -1,   142,   143,   144,    -1,    -1,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,    -1,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
     110,    -1,    -1,   113,    -1,    -1,   116,   117,    -1,    -1,
     120,    -1,    -1,   123,   222,   125,   224,   225,    -1,    -1,
     130,   131,    -1,   133,   134,   135,    23,    -1,   138,   139,
      -1,    -1,   142,   143,   144,    -1,    -1,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    81,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,   110,   224,   225,   113,    -1,    -1,   116,
     117,    -1,    23,   120,    -1,    -1,   123,    -1,   125,    -1,
      -1,    -1,    -1,   130,   131,    -1,   133,   134,   135,    -1,
      -1,   138,   139,    -1,    -1,   142,   143,   144,    -1,    -1,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    70,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
      -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,   110,
      -1,    -1,   113,    -1,    -1,   116,   117,    -1,    -1,   120,
      -1,    -1,   123,    -1,   125,    -1,    -1,   224,   225,   130,
     131,    -1,   133,   134,   135,    -1,    -1,   138,   139,    -1,
      -1,   142,   143,   144,    -1,    -1,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,     0,     1,    -1,    -1,     4,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    -1,    -1,    29,    -1,    31,    -1,    33,    -1,
      -1,    36,    37,    38,    -1,    -1,    41,    42,    43,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    -1,   224,   225,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   231,     0,     1,     4,     6,    25,    26,    29,    31,
      33,    36,    37,    38,    41,    42,    43,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    76,    85,    91,   105,
     232,   234,   235,   236,   237,   273,   274,   275,   277,   283,
     232,    72,    71,   270,   275,   277,   283,   275,   279,   279,
     279,   237,    29,    31,   238,    33,   239,    29,    31,    33,
      36,    37,    38,   240,    29,    30,    31,    35,    36,    40,
     241,    29,    31,    36,    40,   242,    31,   243,    23,    70,
      71,    72,    77,    81,    85,    91,   100,   105,   110,   113,
     116,   117,   120,   123,   125,   130,   131,   133,   134,   135,
     138,   139,   142,   143,   144,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   224,   225,   250,   271,   327,   328,
     329,   356,   359,   361,   364,   365,   367,   369,   371,   373,
     375,   377,   379,   381,   383,   385,   387,   389,   391,   393,
     395,   397,   398,   400,   402,   404,   406,   408,   410,   219,
     220,   244,   249,    71,   245,   246,     0,   232,   270,   270,
      39,   281,    21,    36,    54,    55,    56,    57,    58,    59,
     144,   165,   175,   178,   192,   202,   206,   207,   208,   209,
     213,   222,   286,   287,   288,   289,   290,   294,   295,   298,
     299,   303,   305,   306,   308,   309,   311,   312,   313,   314,
     318,   319,   324,   326,   329,   330,   331,   332,   333,   334,
     335,   337,   338,   339,   340,   341,   342,   343,   353,   355,
     359,   360,   363,   232,   221,   251,   254,   286,   270,   256,
     343,   260,   275,   277,   283,   275,   277,   283,   279,   279,
     279,   275,   273,   276,   277,   276,   279,   274,   285,   275,
     277,   279,   285,   277,    73,    74,    75,   270,   366,    78,
      79,    80,   368,    80,    82,    83,    84,   370,    86,    87,
      88,    89,    90,   372,    78,    79,    82,    92,    93,    94,
      95,    96,    97,    98,    99,   374,    80,    82,    99,   101,
     102,   103,   104,   376,    78,    79,    92,    95,   106,   107,
     108,   109,   378,    80,    82,    99,   101,   102,   104,   111,
     112,   380,    93,   102,   108,   114,   115,   382,   102,   115,
     384,   108,   118,   119,   386,    95,    99,   121,   122,   388,
      99,   121,   122,   124,   390,    99,   102,   114,   118,   121,
     122,   126,   127,   128,   129,   392,    80,   121,   122,   394,
      99,   121,   122,   132,   396,    80,    93,   108,   136,   401,
     137,   403,   137,   405,    93,   108,   399,    82,    96,   108,
     114,   140,   141,   407,    93,   108,   409,    80,    93,    99,
     108,   114,   411,    95,    98,   106,   145,   146,   357,   358,
     359,    78,    79,    98,   147,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   362,   270,   334,    30,    32,    34,
      35,    65,   247,    70,   217,   282,    43,    44,   325,   270,
     270,   357,   362,   193,     4,   233,   344,   345,   218,   284,
     288,   176,   177,   296,   297,   179,   180,   181,   182,   183,
     300,   301,   204,   307,     5,   310,   335,   342,   210,   211,
     212,   316,   317,    60,   315,   316,   214,   215,   216,   320,
     321,   322,   323,    15,    16,    17,    18,   227,    20,    22,
       8,    24,    38,     9,    10,    11,    12,    13,    14,   334,
     336,   342,   354,    36,   336,   342,   352,   222,   222,   222,
     222,   251,   254,   286,   343,   270,     7,   228,   226,   248,
     249,    70,   335,   340,   346,   347,   350,    36,    36,    70,
     343,   346,     7,   223,   271,    70,    70,   297,   271,    70,
      70,    70,   184,   185,   186,   187,   188,   189,   190,   191,
     302,   301,   100,   110,   125,   205,   342,   316,     5,     7,
     342,   342,   321,     7,   329,   329,   330,   331,   332,    70,
     334,   334,    23,   222,   291,   342,     7,     7,   342,   342,
     232,   253,   255,   257,   261,   222,   222,    70,    70,    23,
     327,    63,   218,   348,   349,   342,   342,    20,   233,     5,
     233,   233,   345,    80,    80,   203,    80,   342,   317,   316,
     323,   270,   233,   292,   293,   334,   334,    31,    36,    38,
     118,   223,   232,   234,   252,    66,    80,   223,   232,   234,
     267,   268,   286,    63,    64,    65,    66,    69,    80,   118,
     223,   232,   234,   262,    65,    80,   118,   223,   232,   234,
     262,   253,   255,     7,   229,    71,   272,   271,   349,   197,
     198,   199,   200,   201,   304,   334,   335,   351,   355,    71,
      71,    71,   346,     7,   223,   270,   278,   270,   280,   280,
      71,   232,    54,    55,   269,    71,   232,   232,   232,   272,
     272,   221,    67,    68,   263,    70,    71,   147,   264,   265,
     266,    61,    62,    63,   258,   259,   232,   221,   264,   258,
     232,   223,   223,    70,   233,     5,   233,   293,   254,   256,
     260,    27,   232,   232,   343,   232,     8,     7,   232,   343,
       5,   232,   355,   222,   222,   222,    71,   266,   259,   264,
     233,   255,   257,   261,    28,   106,   232,   223,   223,   223,
      71,    22,    70,   232,   232,   232,   106,    70,    22,    70,
      70
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, scanner, state, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, scanner, state); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser_state *state)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    void *scanner;
    struct parser_state *state;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (state);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser_state *state)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    void *scanner;
    struct parser_state *state;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, state);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, void *scanner, struct parser_state *state)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, scanner, state)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    void *scanner;
    struct parser_state *state;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , scanner, state);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, scanner, state); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *scanner, struct parser_state *state)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, scanner, state)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    void *scanner;
    struct parser_state *state;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (state);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 71: /* "\"string\"" */

/* Line 1391 of yacc.c  */
#line 219 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2829 "parser_bison.c"
	break;
      case 72: /* "QUOTED_STRING" */

/* Line 1391 of yacc.c  */
#line 219 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2838 "parser_bison.c"
	break;
      case 235: /* "line" */

/* Line 1391 of yacc.c  */
#line 410 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2847 "parser_bison.c"
	break;
      case 236: /* "base_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2856 "parser_bison.c"
	break;
      case 237: /* "add_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2865 "parser_bison.c"
	break;
      case 238: /* "create_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2874 "parser_bison.c"
	break;
      case 239: /* "insert_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2883 "parser_bison.c"
	break;
      case 240: /* "delete_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2892 "parser_bison.c"
	break;
      case 241: /* "list_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2901 "parser_bison.c"
	break;
      case 242: /* "flush_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2910 "parser_bison.c"
	break;
      case 243: /* "rename_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2919 "parser_bison.c"
	break;
      case 244: /* "export_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2928 "parser_bison.c"
	break;
      case 245: /* "monitor_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2937 "parser_bison.c"
	break;
      case 246: /* "monitor_event" */

/* Line 1391 of yacc.c  */
#line 552 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2946 "parser_bison.c"
	break;
      case 250: /* "describe_cmd" */

/* Line 1391 of yacc.c  */
#line 413 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2955 "parser_bison.c"
	break;
      case 251: /* "table_block_alloc" */

/* Line 1391 of yacc.c  */
#line 422 "parser_bison.y"
	{ close_scope(state); table_free((yyvaluep->table)); };

/* Line 1391 of yacc.c  */
#line 2964 "parser_bison.c"
	break;
      case 254: /* "chain_block_alloc" */

/* Line 1391 of yacc.c  */
#line 424 "parser_bison.y"
	{ close_scope(state); chain_free((yyvaluep->chain)); };

/* Line 1391 of yacc.c  */
#line 2973 "parser_bison.c"
	break;
      case 256: /* "set_block_alloc" */

/* Line 1391 of yacc.c  */
#line 433 "parser_bison.y"
	{ set_free((yyvaluep->set)); };

/* Line 1391 of yacc.c  */
#line 2982 "parser_bison.c"
	break;
      case 260: /* "map_block_alloc" */

/* Line 1391 of yacc.c  */
#line 436 "parser_bison.y"
	{ set_free((yyvaluep->set)); };

/* Line 1391 of yacc.c  */
#line 2991 "parser_bison.c"
	break;
      case 266: /* "type_identifier" */

/* Line 1391 of yacc.c  */
#line 402 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 3000 "parser_bison.c"
	break;
      case 270: /* "identifier" */

/* Line 1391 of yacc.c  */
#line 402 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 3009 "parser_bison.c"
	break;
      case 271: /* "string" */

/* Line 1391 of yacc.c  */
#line 402 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 3018 "parser_bison.c"
	break;
      case 275: /* "table_spec" */

/* Line 1391 of yacc.c  */
#line 416 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3027 "parser_bison.c"
	break;
      case 276: /* "tables_spec" */

/* Line 1391 of yacc.c  */
#line 416 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3036 "parser_bison.c"
	break;
      case 277: /* "chain_spec" */

/* Line 1391 of yacc.c  */
#line 416 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3045 "parser_bison.c"
	break;
      case 278: /* "chain_identifier" */

/* Line 1391 of yacc.c  */
#line 416 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3054 "parser_bison.c"
	break;
      case 279: /* "set_spec" */

/* Line 1391 of yacc.c  */
#line 418 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3063 "parser_bison.c"
	break;
      case 280: /* "set_identifier" */

/* Line 1391 of yacc.c  */
#line 418 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3072 "parser_bison.c"
	break;
      case 283: /* "ruleid_spec" */

/* Line 1391 of yacc.c  */
#line 416 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3081 "parser_bison.c"
	break;
      case 284: /* "comment_spec" */

/* Line 1391 of yacc.c  */
#line 402 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 3090 "parser_bison.c"
	break;
      case 285: /* "ruleset_spec" */

/* Line 1391 of yacc.c  */
#line 416 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3099 "parser_bison.c"
	break;
      case 286: /* "rule" */

/* Line 1391 of yacc.c  */
#line 426 "parser_bison.y"
	{ rule_free((yyvaluep->rule)); };

/* Line 1391 of yacc.c  */
#line 3108 "parser_bison.c"
	break;
      case 287: /* "stmt_list" */

/* Line 1391 of yacc.c  */
#line 439 "parser_bison.y"
	{ stmt_list_free((yyvaluep->list)); xfree((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 3117 "parser_bison.c"
	break;
      case 288: /* "stmt" */

/* Line 1391 of yacc.c  */
#line 441 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3126 "parser_bison.c"
	break;
      case 289: /* "verdict_stmt" */

/* Line 1391 of yacc.c  */
#line 441 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3135 "parser_bison.c"
	break;
      case 290: /* "verdict_map_stmt" */

/* Line 1391 of yacc.c  */
#line 488 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3144 "parser_bison.c"
	break;
      case 291: /* "verdict_map_expr" */

/* Line 1391 of yacc.c  */
#line 491 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3153 "parser_bison.c"
	break;
      case 292: /* "verdict_map_list_expr" */

/* Line 1391 of yacc.c  */
#line 491 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3162 "parser_bison.c"
	break;
      case 293: /* "verdict_map_list_member_expr" */

/* Line 1391 of yacc.c  */
#line 491 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3171 "parser_bison.c"
	break;
      case 294: /* "counter_stmt" */

/* Line 1391 of yacc.c  */
#line 443 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3180 "parser_bison.c"
	break;
      case 295: /* "counter_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 443 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3189 "parser_bison.c"
	break;
      case 298: /* "log_stmt" */

/* Line 1391 of yacc.c  */
#line 449 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3198 "parser_bison.c"
	break;
      case 299: /* "log_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 449 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3207 "parser_bison.c"
	break;
      case 303: /* "limit_stmt" */

/* Line 1391 of yacc.c  */
#line 452 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3216 "parser_bison.c"
	break;
      case 305: /* "reject_stmt" */

/* Line 1391 of yacc.c  */
#line 455 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3225 "parser_bison.c"
	break;
      case 306: /* "reject_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 455 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3234 "parser_bison.c"
	break;
      case 308: /* "nat_stmt" */

/* Line 1391 of yacc.c  */
#line 457 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3243 "parser_bison.c"
	break;
      case 309: /* "nat_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 457 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3252 "parser_bison.c"
	break;
      case 311: /* "masq_stmt" */

/* Line 1391 of yacc.c  */
#line 457 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3261 "parser_bison.c"
	break;
      case 312: /* "masq_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 457 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3270 "parser_bison.c"
	break;
      case 313: /* "redir_stmt" */

/* Line 1391 of yacc.c  */
#line 457 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3279 "parser_bison.c"
	break;
      case 314: /* "redir_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 457 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3288 "parser_bison.c"
	break;
      case 318: /* "queue_stmt" */

/* Line 1391 of yacc.c  */
#line 460 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3297 "parser_bison.c"
	break;
      case 319: /* "queue_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 460 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3306 "parser_bison.c"
	break;
      case 324: /* "set_stmt" */

/* Line 1391 of yacc.c  */
#line 463 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3315 "parser_bison.c"
	break;
      case 326: /* "match_stmt" */

/* Line 1391 of yacc.c  */
#line 441 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3324 "parser_bison.c"
	break;
      case 327: /* "symbol_expr" */

/* Line 1391 of yacc.c  */
#line 467 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3333 "parser_bison.c"
	break;
      case 328: /* "integer_expr" */

/* Line 1391 of yacc.c  */
#line 467 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3342 "parser_bison.c"
	break;
      case 329: /* "primary_expr" */

/* Line 1391 of yacc.c  */
#line 469 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3351 "parser_bison.c"
	break;
      case 330: /* "shift_expr" */

/* Line 1391 of yacc.c  */
#line 469 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3360 "parser_bison.c"
	break;
      case 331: /* "and_expr" */

/* Line 1391 of yacc.c  */
#line 469 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3369 "parser_bison.c"
	break;
      case 332: /* "exclusive_or_expr" */

/* Line 1391 of yacc.c  */
#line 471 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3378 "parser_bison.c"
	break;
      case 333: /* "inclusive_or_expr" */

/* Line 1391 of yacc.c  */
#line 471 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3387 "parser_bison.c"
	break;
      case 334: /* "basic_expr" */

/* Line 1391 of yacc.c  */
#line 473 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3396 "parser_bison.c"
	break;
      case 335: /* "concat_expr" */

/* Line 1391 of yacc.c  */
#line 482 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3405 "parser_bison.c"
	break;
      case 336: /* "list_expr" */

/* Line 1391 of yacc.c  */
#line 480 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3414 "parser_bison.c"
	break;
      case 337: /* "prefix_expr" */

/* Line 1391 of yacc.c  */
#line 478 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3423 "parser_bison.c"
	break;
      case 338: /* "range_expr" */

/* Line 1391 of yacc.c  */
#line 478 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3432 "parser_bison.c"
	break;
      case 339: /* "wildcard_expr" */

/* Line 1391 of yacc.c  */
#line 478 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3441 "parser_bison.c"
	break;
      case 340: /* "multiton_expr" */

/* Line 1391 of yacc.c  */
#line 476 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3450 "parser_bison.c"
	break;
      case 341: /* "map_expr" */

/* Line 1391 of yacc.c  */
#line 485 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3459 "parser_bison.c"
	break;
      case 342: /* "expr" */

/* Line 1391 of yacc.c  */
#line 499 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3468 "parser_bison.c"
	break;
      case 343: /* "set_expr" */

/* Line 1391 of yacc.c  */
#line 494 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3477 "parser_bison.c"
	break;
      case 344: /* "set_list_expr" */

/* Line 1391 of yacc.c  */
#line 494 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3486 "parser_bison.c"
	break;
      case 345: /* "set_list_member_expr" */

/* Line 1391 of yacc.c  */
#line 494 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3495 "parser_bison.c"
	break;
      case 346: /* "set_elem_expr" */

/* Line 1391 of yacc.c  */
#line 496 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3504 "parser_bison.c"
	break;
      case 347: /* "set_elem_expr_alloc" */

/* Line 1391 of yacc.c  */
#line 496 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3513 "parser_bison.c"
	break;
      case 350: /* "set_lhs_expr" */

/* Line 1391 of yacc.c  */
#line 496 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3522 "parser_bison.c"
	break;
      case 351: /* "set_rhs_expr" */

/* Line 1391 of yacc.c  */
#line 496 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3531 "parser_bison.c"
	break;
      case 352: /* "initializer_expr" */

/* Line 1391 of yacc.c  */
#line 499 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3540 "parser_bison.c"
	break;
      case 353: /* "relational_expr" */

/* Line 1391 of yacc.c  */
#line 502 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3549 "parser_bison.c"
	break;
      case 355: /* "verdict_expr" */

/* Line 1391 of yacc.c  */
#line 467 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3558 "parser_bison.c"
	break;
      case 356: /* "meta_expr" */

/* Line 1391 of yacc.c  */
#line 543 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3567 "parser_bison.c"
	break;
      case 360: /* "meta_stmt" */

/* Line 1391 of yacc.c  */
#line 447 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3576 "parser_bison.c"
	break;
      case 361: /* "ct_expr" */

/* Line 1391 of yacc.c  */
#line 547 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3585 "parser_bison.c"
	break;
      case 363: /* "ct_stmt" */

/* Line 1391 of yacc.c  */
#line 445 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3594 "parser_bison.c"
	break;
      case 364: /* "payload_expr" */

/* Line 1391 of yacc.c  */
#line 506 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3603 "parser_bison.c"
	break;
      case 365: /* "payload_raw_expr" */

/* Line 1391 of yacc.c  */
#line 506 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3612 "parser_bison.c"
	break;
      case 367: /* "eth_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 509 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3621 "parser_bison.c"
	break;
      case 369: /* "vlan_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 509 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3630 "parser_bison.c"
	break;
      case 371: /* "arp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 512 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3639 "parser_bison.c"
	break;
      case 373: /* "ip_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 515 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3648 "parser_bison.c"
	break;
      case 375: /* "icmp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 515 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3657 "parser_bison.c"
	break;
      case 377: /* "ip6_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 518 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3666 "parser_bison.c"
	break;
      case 379: /* "icmp6_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 518 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3675 "parser_bison.c"
	break;
      case 381: /* "auth_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 521 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3684 "parser_bison.c"
	break;
      case 383: /* "esp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 521 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3693 "parser_bison.c"
	break;
      case 385: /* "comp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 521 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3702 "parser_bison.c"
	break;
      case 387: /* "udp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 524 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3711 "parser_bison.c"
	break;
      case 389: /* "udplite_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 524 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3720 "parser_bison.c"
	break;
      case 391: /* "tcp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 524 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3729 "parser_bison.c"
	break;
      case 393: /* "dccp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 527 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3738 "parser_bison.c"
	break;
      case 395: /* "sctp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 527 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3747 "parser_bison.c"
	break;
      case 397: /* "exthdr_expr" */

/* Line 1391 of yacc.c  */
#line 531 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3756 "parser_bison.c"
	break;
      case 398: /* "hbh_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 533 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3765 "parser_bison.c"
	break;
      case 400: /* "rt_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 536 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3774 "parser_bison.c"
	break;
      case 402: /* "rt0_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 536 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3783 "parser_bison.c"
	break;
      case 404: /* "rt2_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 536 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3792 "parser_bison.c"
	break;
      case 406: /* "frag_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 533 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3801 "parser_bison.c"
	break;
      case 408: /* "dst_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 533 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3810 "parser_bison.c"
	break;
      case 410: /* "mh_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 539 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3819 "parser_bison.c"
	break;

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void *scanner, struct parser_state *state);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *scanner, struct parser_state *state)
#else
int
yyparse (scanner, state)
    void *scanner;
    struct parser_state *state;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

/* User initialization code.  */

/* Line 1590 of yacc.c  */
#line 112 "parser_bison.y"
{
	location_init(scanner, state, &yylloc);
#ifdef DEBUG
	if (debug_level & DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (debug_level & DEBUG_PARSER)
		yydebug = 1;
#endif
}

/* Line 1590 of yacc.c  */
#line 3979 "parser_bison.c"

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;
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
     `$$ = $1'.

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

/* Line 1806 of yacc.c  */
#line 559 "parser_bison.y"
    {
				if ((yyvsp[(2) - (2)].cmd) != NULL) {
					LIST_HEAD(list);

					(yyvsp[(2) - (2)].cmd)->location = (yylsp[(2) - (2)]);

					list_add_tail(&(yyvsp[(2) - (2)].cmd)->list, &list);
					if (cmd_evaluate(&state->ectx, (yyvsp[(2) - (2)].cmd)) < 0) {
						if (++state->nerrs == max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, &state->cmds);
				}
			}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 584 "parser_bison.y"
    {
				if (scanner_include_file(scanner, (yyvsp[(2) - (3)].string), &(yyloc)) < 0) {
					xfree((yyvsp[(2) - (3)].string));
					YYERROR;
				}
				xfree((yyvsp[(2) - (3)].string));
			}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 592 "parser_bison.y"
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[(2) - (5)].string)) != NULL) {
					erec_queue(error(&(yylsp[(2) - (5)]), "redfinition of symbol '%s'", (yyvsp[(2) - (5)].string)),
						   state->msgs);
					YYERROR;
				}

				symbol_bind(scope, (yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].expr));
				xfree((yyvsp[(2) - (5)].string));
			}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 605 "parser_bison.y"
    {
				if (++state->nerrs == max_errors)
					YYABORT;
				yyerrok;
			}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 612 "parser_bison.y"
    { (yyval.cmd) = NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 613 "parser_bison.y"
    { (yyval.cmd) = NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 614 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(1) - (2)].cmd); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 616 "parser_bison.y"
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
				if ((yyvsp[(1) - (2)].cmd) != NULL) {
					LIST_HEAD(list);

					(yyvsp[(1) - (2)].cmd)->location = (yylsp[(1) - (2)]);

					list_add_tail(&(yyvsp[(1) - (2)].cmd)->list, &list);
					if (cmd_evaluate(&state->ectx, (yyvsp[(1) - (2)].cmd)) < 0) {
						if (++state->nerrs == max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, &state->cmds);
				}
				(yyval.cmd) = NULL;

				YYACCEPT;
			}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 644 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(1) - (1)].cmd); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 645 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 646 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 647 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 648 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 649 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 650 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 651 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 652 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 653 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 654 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 658 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 663 "parser_bison.y"
    {
				handle_merge(&(yyvsp[(3) - (6)].table)->handle, &(yyvsp[(2) - (6)].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].table));
			}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 669 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 674 "parser_bison.y"
    {
				(yyvsp[(5) - (6)].chain)->location = (yylsp[(5) - (6)]);
				handle_merge(&(yyvsp[(3) - (6)].chain)->handle, &(yyvsp[(2) - (6)].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].chain));
			}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 681 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[(2) - (3)].handle), &(yyloc), (yyvsp[(3) - (3)].rule));
			}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 685 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[(1) - (2)].handle), &(yyloc), (yyvsp[(2) - (2)].rule));
			}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 690 "parser_bison.y"
    {
				(yyvsp[(5) - (6)].set)->location = (yylsp[(5) - (6)]);
				handle_merge(&(yyvsp[(3) - (6)].set)->handle, &(yyvsp[(2) - (6)].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].set));
			}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 697 "parser_bison.y"
    {
				(yyvsp[(5) - (6)].set)->location = (yylsp[(5) - (6)]);
				handle_merge(&(yyvsp[(3) - (6)].set)->handle, &(yyvsp[(2) - (6)].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].set));
			}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 703 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[(2) - (3)].handle), &(yyloc), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 709 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 714 "parser_bison.y"
    {
				handle_merge(&(yyvsp[(3) - (6)].table)->handle, &(yyvsp[(2) - (6)].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].table));
			}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 720 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 725 "parser_bison.y"
    {
				(yyvsp[(5) - (6)].chain)->location = (yylsp[(5) - (6)]);
				handle_merge(&(yyvsp[(3) - (6)].chain)->handle, &(yyvsp[(2) - (6)].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].chain));
			}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 734 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[(2) - (3)].handle), &(yyloc), (yyvsp[(3) - (3)].rule));
			}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 740 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 744 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 748 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 752 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 756 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 760 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[(2) - (3)].handle), &(yyloc), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 766 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 770 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 774 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 778 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 782 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 786 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 792 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 796 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 800 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 804 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 810 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[(2) - (3)].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[(3) - (3)].string);
			}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 817 "parser_bison.y"
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[(1) - (1)].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 825 "parser_bison.y"
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[(3) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(1) - (3)].string));
				m->location = (yylsp[(1) - (3)]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 833 "parser_bison.y"
    { (yyval.string) = NULL; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 834 "parser_bison.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 837 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 838 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 839 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 840 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 841 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 842 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 845 "parser_bison.y"
    { (yyval.val) = NFTNL_OUTPUT_DEFAULT; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 849 "parser_bison.y"
    { (yyval.val) = NFTNL_OUTPUT_XML; }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 850 "parser_bison.y"
    { (yyval.val) = NFTNL_OUTPUT_JSON; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 854 "parser_bison.y"
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[(1) - (1)].expr);
			}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 862 "parser_bison.y"
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 869 "parser_bison.y"
    {
				if (strcmp((yyvsp[(2) - (2)].string), "dormant") == 0) {
					(yyvsp[(0) - (2)].table)->flags = TABLE_F_DORMANT;
				} else {
					erec_queue(error(&(yylsp[(2) - (2)]), "unknown table option %s", (yyvsp[(2) - (2)].string)),
						   state->msgs);
					YYERROR;
				}
			}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 880 "parser_bison.y"
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 887 "parser_bison.y"
    {
				(yyvsp[(4) - (8)].chain)->location = (yylsp[(3) - (8)]);
				handle_merge(&(yyvsp[(4) - (8)].chain)->handle, &(yyvsp[(3) - (8)].handle));
				handle_free(&(yyvsp[(3) - (8)].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[(4) - (8)].chain)->list, &(yyvsp[(1) - (8)].table)->chains);
				(yyval.table) = (yyvsp[(1) - (8)].table);
			}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 898 "parser_bison.y"
    {
				(yyvsp[(4) - (8)].set)->location = (yylsp[(3) - (8)]);
				handle_merge(&(yyvsp[(4) - (8)].set)->handle, &(yyvsp[(3) - (8)].handle));
				handle_free(&(yyvsp[(3) - (8)].handle));
				list_add_tail(&(yyvsp[(4) - (8)].set)->list, &(yyvsp[(1) - (8)].table)->sets);
				(yyval.table) = (yyvsp[(1) - (8)].table);
			}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 908 "parser_bison.y"
    {
				(yyvsp[(4) - (8)].set)->location = (yylsp[(3) - (8)]);
				handle_merge(&(yyvsp[(4) - (8)].set)->handle, &(yyvsp[(3) - (8)].handle));
				handle_free(&(yyvsp[(3) - (8)].handle));
				list_add_tail(&(yyvsp[(4) - (8)].set)->list, &(yyvsp[(1) - (8)].table)->sets);
				(yyval.table) = (yyvsp[(1) - (8)].table);
			}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 918 "parser_bison.y"
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 924 "parser_bison.y"
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 930 "parser_bison.y"
    {
				list_add_tail(&(yyvsp[(2) - (3)].rule)->list, &(yyvsp[(1) - (3)].chain)->rules);
				(yyval.chain) = (yyvsp[(1) - (3)].chain);
			}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 937 "parser_bison.y"
    {
				(yyval.set) = set_alloc(NULL);
			}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 942 "parser_bison.y"
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 946 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->keytype = (yyvsp[(3) - (4)].datatype);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 951 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->flags = (yyvsp[(3) - (4)].val);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 956 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->timeout = (yyvsp[(3) - (4)].val) * 1000;
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 961 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->gc_int = (yyvsp[(3) - (4)].val) * 1000;
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 966 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->init = (yyvsp[(4) - (4)].expr);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 974 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(1) - (3)].val) | (yyvsp[(3) - (3)].val);
			}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 980 "parser_bison.y"
    { (yyval.val) = SET_F_CONSTANT; }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 981 "parser_bison.y"
    { (yyval.val) = SET_F_INTERVAL; }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 982 "parser_bison.y"
    { (yyval.val) = SET_F_TIMEOUT; }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 986 "parser_bison.y"
    {
				(yyval.set) = set_alloc(NULL);
				(yyval.set)->flags |= NFT_SET_MAP;
			}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 992 "parser_bison.y"
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 998 "parser_bison.y"
    {
				(yyvsp[(1) - (6)].set)->keytype  = (yyvsp[(3) - (6)].datatype);
				(yyvsp[(1) - (6)].set)->datatype = (yyvsp[(5) - (6)].datatype);
				(yyval.set) = (yyvsp[(1) - (6)].set);
			}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1004 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->flags = (yyvsp[(3) - (4)].val);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1009 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->init = (yyvsp[(4) - (4)].expr);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1017 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].set)->policy = (yyvsp[(2) - (2)].val);
			}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1021 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].set)->desc.size = (yyvsp[(2) - (2)].val);
			}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1026 "parser_bison.y"
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1027 "parser_bison.y"
    { (yyval.val) = NFT_SET_POL_MEMORY; }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1031 "parser_bison.y"
    {
				if ((yyvsp[(1) - (1)].val) & ~TYPE_MASK)
					(yyval.datatype) = concat_type_alloc((yyvsp[(1) - (1)].val));
				else
					(yyval.datatype) = datatype_lookup((yyvsp[(1) - (1)].val));
			}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1040 "parser_bison.y"
    {
				const struct datatype *dtype = datatype_lookup_byname((yyvsp[(1) - (1)].string));
				if (dtype == NULL) {
					erec_queue(error(&(yylsp[(1) - (1)]), "unknown datatype %s", (yyvsp[(1) - (1)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyval.val) = dtype->type;
			}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1050 "parser_bison.y"
    {
				const struct datatype *dtype = datatype_lookup_byname((yyvsp[(3) - (3)].string));
				if (dtype == NULL) {
					erec_queue(error(&(yylsp[(3) - (3)]), "unknown datatype %s", (yyvsp[(3) - (3)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyval.val) = concat_subtype_add((yyval.val), dtype->type);
			}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1061 "parser_bison.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1062 "parser_bison.y"
    { (yyval.string) = xstrdup("mark"); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1066 "parser_bison.y"
    {
				(yyvsp[(0) - (6)].chain)->type		= chain_type_name_lookup((yyvsp[(2) - (6)].string));
				if ((yyvsp[(0) - (6)].chain)->type == NULL) {
					erec_queue(error(&(yylsp[(2) - (6)]), "unknown chain type %s", (yyvsp[(2) - (6)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (6)].chain)->hookstr	= chain_hookname_lookup((yyvsp[(4) - (6)].string));
				if ((yyvsp[(0) - (6)].chain)->hookstr == NULL) {
					erec_queue(error(&(yylsp[(4) - (6)]), "unknown chain hook %s", (yyvsp[(4) - (6)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (6)].chain)->priority	= (yyvsp[(6) - (6)].val);
				(yyvsp[(0) - (6)].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1083 "parser_bison.y"
    {
				(yyvsp[(0) - (7)].chain)->type		= chain_type_name_lookup((yyvsp[(2) - (7)].string));
				if ((yyvsp[(0) - (7)].chain)->type == NULL) {
					erec_queue(error(&(yylsp[(2) - (7)]), "unknown type name %s", (yyvsp[(2) - (7)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (7)].chain)->hookstr	= chain_hookname_lookup((yyvsp[(4) - (7)].string));
				if ((yyvsp[(0) - (7)].chain)->hookstr == NULL) {
					erec_queue(error(&(yylsp[(4) - (7)]), "unknown hook name %s", (yyvsp[(4) - (7)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (7)].chain)->priority	= -(yyvsp[(7) - (7)].val);
				(yyvsp[(0) - (7)].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1100 "parser_bison.y"
    {
				(yyvsp[(0) - (8)].chain)->type		= chain_type_name_lookup((yyvsp[(2) - (8)].string));
				if ((yyvsp[(0) - (8)].chain)->type == NULL) {
					erec_queue(error(&(yylsp[(2) - (8)]), "unknown chain type %s", (yyvsp[(2) - (8)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (8)].chain)->hookstr	= chain_hookname_lookup((yyvsp[(4) - (8)].string));
				if ((yyvsp[(0) - (8)].chain)->hookstr == NULL) {
					erec_queue(error(&(yylsp[(4) - (8)]), "unknown chain hook %s", (yyvsp[(4) - (8)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (8)].chain)->dev		= (yyvsp[(6) - (8)].string);
				(yyvsp[(0) - (8)].chain)->priority	= (yyvsp[(8) - (8)].val);
				(yyvsp[(0) - (8)].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1118 "parser_bison.y"
    {
				(yyvsp[(0) - (9)].chain)->type		= chain_type_name_lookup((yyvsp[(2) - (9)].string));
				if ((yyvsp[(0) - (9)].chain)->type == NULL) {
					erec_queue(error(&(yylsp[(2) - (9)]), "unknown type name %s", (yyvsp[(2) - (9)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (9)].chain)->hookstr	= chain_hookname_lookup((yyvsp[(4) - (9)].string));
				(yyvsp[(0) - (9)].chain)->dev		= (yyvsp[(6) - (9)].string);
				(yyvsp[(0) - (9)].chain)->priority	= -(yyvsp[(9) - (9)].val);
				(yyvsp[(0) - (9)].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1133 "parser_bison.y"
    {
				if ((yyvsp[(0) - (2)].chain)->policy != -1) {
					erec_queue(error(&(yyloc), "you cannot set chain policy twice"),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (2)].chain)->policy	= (yyvsp[(2) - (2)].val);
			}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1143 "parser_bison.y"
    { (yyval.val) = NF_ACCEPT; }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1144 "parser_bison.y"
    { (yyval.val) = NF_DROP;   }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1155 "parser_bison.y"
    {
				struct error_record *erec;
				uint64_t res;

				erec = time_parse(&(yylsp[(1) - (1)]), (yyvsp[(1) - (1)].string), &res);
				if (erec != NULL) {
					erec_queue(erec, state->msgs);
					YYERROR;
				}
				(yyval.val) = res;
			}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1168 "parser_bison.y"
    { (yyval.val) = NFPROTO_IPV4; }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1172 "parser_bison.y"
    { (yyval.val) = NFPROTO_IPV4; }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1173 "parser_bison.y"
    { (yyval.val) = NFPROTO_IPV6; }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1174 "parser_bison.y"
    { (yyval.val) = NFPROTO_INET; }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1175 "parser_bison.y"
    { (yyval.val) = NFPROTO_ARP; }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1176 "parser_bison.y"
    { (yyval.val) = NFPROTO_BRIDGE; }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1177 "parser_bison.y"
    { (yyval.val) = NFPROTO_NETDEV; }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 1181 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[(1) - (2)].val);
				(yyval.handle).table	= (yyvsp[(2) - (2)].string);
			}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 1189 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[(1) - (1)].val);
				(yyval.handle).table	= NULL;
			}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1197 "parser_bison.y"
    {
				(yyval.handle)		= (yyvsp[(1) - (2)].handle);
				(yyval.handle).chain	= (yyvsp[(2) - (2)].string);
			}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1204 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[(1) - (1)].string);
			}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1211 "parser_bison.y"
    {
				(yyval.handle)		= (yyvsp[(1) - (2)].handle);
				(yyval.handle).set		= (yyvsp[(2) - (2)].string);
			}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1218 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[(1) - (1)].string);
			}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1225 "parser_bison.y"
    {
				(yyval.val) = 0;
			}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1229 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(2) - (2)].val);
			}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1235 "parser_bison.y"
    {
				(yyval.val) = 0;
			}
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1239 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(2) - (2)].val);
			}
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1245 "parser_bison.y"
    {
				(yyval.handle)		= (yyvsp[(1) - (3)].handle);
				(yyval.handle).handle	= (yyvsp[(2) - (3)].val);
				(yyval.handle).position	= (yyvsp[(3) - (3)].val);
			}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1253 "parser_bison.y"
    {
				(yyval.string) = NULL;
			}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1257 "parser_bison.y"
    {
				(yyval.string) = (yyvsp[(2) - (2)].string);
			}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1263 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1268 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[(1) - (1)].val);
			}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1275 "parser_bison.y"
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				(yyval.rule)->handle.comment = (yyvsp[(2) - (2)].string);
				list_for_each_entry(i, (yyvsp[(1) - (2)].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[(1) - (2)].list), &(yyval.rule)->stmts);
				xfree((yyvsp[(1) - (2)].list));
			}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1288 "parser_bison.y"
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[(1) - (1)].stmt)->list, (yyval.list));
			}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1294 "parser_bison.y"
    {
				(yyval.list) = (yyvsp[(1) - (2)].list);
				list_add_tail(&(yyvsp[(2) - (2)].stmt)->list, (yyvsp[(1) - (2)].list));
			}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 1316 "parser_bison.y"
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 1320 "parser_bison.y"
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 1326 "parser_bison.y"
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 1332 "parser_bison.y"
    {
				(yyvsp[(2) - (3)].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[(2) - (3)].expr);
			}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 1337 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[(2) - (2)].string));
				xfree((yyvsp[(2) - (2)].string));
			}
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 1346 "parser_bison.y"
    {
				(yyval.expr) = set_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 1351 "parser_bison.y"
    {
				compound_expr_add((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
				(yyval.expr) = (yyvsp[(1) - (3)].expr);
			}
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 1359 "parser_bison.y"
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[(2) - (5)].expr), (yyvsp[(4) - (5)].expr));
			}
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1368 "parser_bison.y"
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 1374 "parser_bison.y"
    {
				(yyval.stmt)	= (yyvsp[(0) - (1)].stmt);
			}
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1381 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->counter.packets = (yyvsp[(2) - (2)].val);
			}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 1385 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->counter.bytes	 = (yyvsp[(2) - (2)].val);
			}
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 1395 "parser_bison.y"
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1401 "parser_bison.y"
    {
				(yyval.stmt)	= (yyvsp[(0) - (1)].stmt);
			}
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 1408 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.prefix	 = (yyvsp[(2) - (2)].string);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 1413 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.group	 = (yyvsp[(2) - (2)].val);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 1418 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.snaplen	 = (yyvsp[(2) - (2)].val);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 1423 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.qthreshold = (yyvsp[(2) - (2)].val);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 1428 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.level	= (yyvsp[(2) - (2)].val);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 1434 "parser_bison.y"
    { (yyval.val) = LOG_EMERG; }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 1435 "parser_bison.y"
    { (yyval.val) = LOG_ALERT; }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 1436 "parser_bison.y"
    { (yyval.val) = LOG_CRIT; }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 1437 "parser_bison.y"
    { (yyval.val) = LOG_ERR; }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 1438 "parser_bison.y"
    { (yyval.val) = LOG_WARNING; }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1439 "parser_bison.y"
    { (yyval.val) = LOG_NOTICE; }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1440 "parser_bison.y"
    { (yyval.val) = LOG_INFO; }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1441 "parser_bison.y"
    { (yyval.val) = LOG_DEBUG; }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1445 "parser_bison.y"
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[(3) - (5)].val);
				(yyval.stmt)->limit.unit	= (yyvsp[(5) - (5)].val);
			}
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 1452 "parser_bison.y"
    { (yyval.val) = 1ULL; }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 1453 "parser_bison.y"
    { (yyval.val) = 1ULL * 60; }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1454 "parser_bison.y"
    { (yyval.val) = 1ULL * 60 * 60; }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1455 "parser_bison.y"
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1456 "parser_bison.y"
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1463 "parser_bison.y"
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1469 "parser_bison.y"
    {
				(yyvsp[(0) - (0)].stmt)->reject.type = -1;
				(yyvsp[(0) - (0)].stmt)->reject.icmp_code = -1;
			}
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1474 "parser_bison.y"
    {
				(yyvsp[(0) - (4)].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[(0) - (4)].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[(0) - (4)].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[(4) - (4)].string));
				(yyvsp[(0) - (4)].stmt)->reject.expr->dtype = &icmp_code_type;
			}
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1484 "parser_bison.y"
    {
				(yyvsp[(0) - (4)].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[(0) - (4)].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[(0) - (4)].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[(4) - (4)].string));
				(yyvsp[(0) - (4)].stmt)->reject.expr->dtype = &icmpv6_code_type;
			}
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1494 "parser_bison.y"
    {
				(yyvsp[(0) - (4)].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[(0) - (4)].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[(4) - (4)].string));
				(yyvsp[(0) - (4)].stmt)->reject.expr->dtype = &icmpx_code_type;
			}
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1503 "parser_bison.y"
    {
				(yyvsp[(0) - (3)].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1512 "parser_bison.y"
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_SNAT;
			}
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1517 "parser_bison.y"
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_DNAT;
			}
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 1524 "parser_bison.y"
    {
				(yyvsp[(0) - (1)].stmt)->nat.addr = (yyvsp[(1) - (1)].expr);
			}
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1528 "parser_bison.y"
    {
				(yyvsp[(0) - (3)].stmt)->nat.addr = (yyvsp[(1) - (3)].expr);
				(yyvsp[(0) - (3)].stmt)->nat.proto = (yyvsp[(3) - (3)].expr);
			}
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1533 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->nat.proto = (yyvsp[(2) - (2)].expr);
			}
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 1537 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->nat.flags = (yyvsp[(2) - (2)].val);
			}
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 1544 "parser_bison.y"
    {
				(yyval.stmt) = (yyvsp[(1) - (2)].stmt);
				(yyval.stmt)->masq.flags = (yyvsp[(2) - (2)].val);
			}
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 1550 "parser_bison.y"
    { (yyval.stmt) = masq_stmt_alloc(&(yyloc)); }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 1557 "parser_bison.y"
    { (yyval.stmt) = redir_stmt_alloc(&(yyloc)); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1561 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->redir.proto = (yyvsp[(2) - (2)].expr);
			}
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1565 "parser_bison.y"
    {
				(yyvsp[(0) - (1)].stmt)->redir.flags = (yyvsp[(1) - (1)].val);
			}
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1569 "parser_bison.y"
    {
				(yyvsp[(0) - (3)].stmt)->redir.proto = (yyvsp[(2) - (3)].expr);
				(yyvsp[(0) - (3)].stmt)->redir.flags = (yyvsp[(3) - (3)].val);
			}
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1577 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(1) - (3)].val) | (yyvsp[(3) - (3)].val);
			}
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1582 "parser_bison.y"
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1583 "parser_bison.y"
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1584 "parser_bison.y"
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1592 "parser_bison.y"
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1598 "parser_bison.y"
    {
				(yyval.stmt)	= (yyvsp[(0) - (1)].stmt);
			}
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1605 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->queue.queue = (yyvsp[(2) - (2)].expr);
			}
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 1609 "parser_bison.y"
    {
				(yyvsp[(0) - (1)].stmt)->queue.flags |= (yyvsp[(1) - (1)].val);
			}
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1616 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(1) - (3)].val) | (yyvsp[(3) - (3)].val);
			}
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 1621 "parser_bison.y"
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 1622 "parser_bison.y"
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 1626 "parser_bison.y"
    {
				(yyval.stmt) = set_stmt_alloc(&(yyloc));
				(yyval.stmt)->set.op  = (yyvsp[(2) - (4)].val);
				(yyval.stmt)->set.key = (yyvsp[(3) - (4)].expr);
				(yyval.stmt)->set.set = (yyvsp[(4) - (4)].expr);
			}
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 1634 "parser_bison.y"
    { (yyval.val) = NFT_DYNSET_OP_ADD; }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 1635 "parser_bison.y"
    { (yyval.val) = NFT_DYNSET_OP_UPDATE; }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 1639 "parser_bison.y"
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1645 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[(1) - (1)].string));
				xfree((yyvsp[(1) - (1)].string));
			}
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1652 "parser_bison.y"
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[(2) - (2)].string)) == NULL) {
					erec_queue(error(&(yylsp[(2) - (2)]), "unknown identifier '%s'", (yyvsp[(2) - (2)].string)),
						   state->msgs);
					YYERROR;
				}

				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_DEFINE,
						       scope, (yyvsp[(2) - (2)].string));
				xfree((yyvsp[(2) - (2)].string));
			}
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1666 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[(2) - (2)].string));
				xfree((yyvsp[(2) - (2)].string));
			}
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1675 "parser_bison.y"
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[(1) - (1)].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1685 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1686 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 1687 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1688 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1689 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1690 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1691 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 1696 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 1700 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 1707 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 1714 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 1721 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 1731 "parser_bison.y"
    {
				if ((yyval.expr)->ops->type != EXPR_CONCAT) {
					(yyval.expr) = concat_expr_alloc(&(yyloc));
					compound_expr_add((yyval.expr), (yyvsp[(1) - (3)].expr));
				} else {
					struct location rhs[] = {
						[1]	= (yylsp[(2) - (3)]),
						[2]	= (yylsp[(3) - (3)]),
					};
					location_update(&(yyvsp[(3) - (3)].expr)->location, rhs, 2);

					(yyval.expr) = (yyvsp[(1) - (3)].expr);
					(yyval.expr)->location = (yyloc);
				}
				compound_expr_add((yyval.expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 1750 "parser_bison.y"
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[(1) - (3)].expr));
				compound_expr_add((yyval.expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 277:

/* Line 1806 of yacc.c  */
#line 1756 "parser_bison.y"
    {
				(yyvsp[(1) - (3)].expr)->location = (yyloc);
				compound_expr_add((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
				(yyval.expr) = (yyvsp[(1) - (3)].expr);
			}
    break;

  case 278:

/* Line 1806 of yacc.c  */
#line 1764 "parser_bison.y"
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].val));
			}
    break;

  case 279:

/* Line 1806 of yacc.c  */
#line 1770 "parser_bison.y"
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 280:

/* Line 1806 of yacc.c  */
#line 1776 "parser_bison.y"
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
    break;

  case 284:

/* Line 1806 of yacc.c  */
#line 1792 "parser_bison.y"
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 1804 "parser_bison.y"
    {
				(yyvsp[(2) - (3)].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[(2) - (3)].expr);
			}
    break;

  case 290:

/* Line 1806 of yacc.c  */
#line 1811 "parser_bison.y"
    {
				(yyval.expr) = set_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 291:

/* Line 1806 of yacc.c  */
#line 1816 "parser_bison.y"
    {
				compound_expr_add((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
				(yyval.expr) = (yyvsp[(1) - (3)].expr);
			}
    break;

  case 293:

/* Line 1806 of yacc.c  */
#line 1824 "parser_bison.y"
    {
				(yyval.expr) = (yyvsp[(2) - (3)].expr);
			}
    break;

  case 294:

/* Line 1806 of yacc.c  */
#line 1828 "parser_bison.y"
    {
				(yyval.expr) = (yyvsp[(2) - (3)].expr);
			}
    break;

  case 295:

/* Line 1806 of yacc.c  */
#line 1832 "parser_bison.y"
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[(2) - (5)].expr), (yyvsp[(4) - (5)].expr));
			}
    break;

  case 298:

/* Line 1806 of yacc.c  */
#line 1842 "parser_bison.y"
    {
				(yyval.expr) = set_elem_expr_alloc(&(yylsp[(1) - (1)]), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 299:

/* Line 1806 of yacc.c  */
#line 1848 "parser_bison.y"
    {
				(yyval.expr)	= (yyvsp[(0) - (1)].expr);
			}
    break;

  case 301:

/* Line 1806 of yacc.c  */
#line 1855 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].expr)->timeout = (yyvsp[(2) - (2)].val) * 1000;
			}
    break;

  case 302:

/* Line 1806 of yacc.c  */
#line 1859 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].expr)->comment = (yyvsp[(2) - (2)].string);
			}
    break;

  case 309:

/* Line 1806 of yacc.c  */
#line 1877 "parser_bison.y"
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[(1) - (2)].expr), (yyvsp[(2) - (2)].expr));
			}
    break;

  case 310:

/* Line 1806 of yacc.c  */
#line 1881 "parser_bison.y"
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_FLAGCMP, (yyvsp[(1) - (2)].expr), (yyvsp[(2) - (2)].expr));
			}
    break;

  case 311:

/* Line 1806 of yacc.c  */
#line 1885 "parser_bison.y"
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[(2) - (3)]), (yyvsp[(2) - (3)].val), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 312:

/* Line 1806 of yacc.c  */
#line 1890 "parser_bison.y"
    { (yyval.val) = OP_EQ; }
    break;

  case 313:

/* Line 1806 of yacc.c  */
#line 1891 "parser_bison.y"
    { (yyval.val) = OP_NEQ; }
    break;

  case 314:

/* Line 1806 of yacc.c  */
#line 1892 "parser_bison.y"
    { (yyval.val) = OP_LT; }
    break;

  case 315:

/* Line 1806 of yacc.c  */
#line 1893 "parser_bison.y"
    { (yyval.val) = OP_GT; }
    break;

  case 316:

/* Line 1806 of yacc.c  */
#line 1894 "parser_bison.y"
    { (yyval.val) = OP_GTE; }
    break;

  case 317:

/* Line 1806 of yacc.c  */
#line 1895 "parser_bison.y"
    { (yyval.val) = OP_LTE; }
    break;

  case 318:

/* Line 1806 of yacc.c  */
#line 1899 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
    break;

  case 319:

/* Line 1806 of yacc.c  */
#line 1903 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
    break;

  case 320:

/* Line 1806 of yacc.c  */
#line 1907 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
    break;

  case 321:

/* Line 1806 of yacc.c  */
#line 1911 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[(2) - (2)].string));
			}
    break;

  case 322:

/* Line 1806 of yacc.c  */
#line 1915 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[(2) - (2)].string));
			}
    break;

  case 323:

/* Line 1806 of yacc.c  */
#line 1919 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
    break;

  case 324:

/* Line 1806 of yacc.c  */
#line 1925 "parser_bison.y"
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[(2) - (2)].val));
			}
    break;

  case 325:

/* Line 1806 of yacc.c  */
#line 1929 "parser_bison.y"
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[(1) - (1)].val));
			}
    break;

  case 328:

/* Line 1806 of yacc.c  */
#line 1938 "parser_bison.y"
    { (yyval.val) = NFT_META_LEN; }
    break;

  case 329:

/* Line 1806 of yacc.c  */
#line 1939 "parser_bison.y"
    { (yyval.val) = NFT_META_NFPROTO; }
    break;

  case 330:

/* Line 1806 of yacc.c  */
#line 1940 "parser_bison.y"
    { (yyval.val) = NFT_META_L4PROTO; }
    break;

  case 331:

/* Line 1806 of yacc.c  */
#line 1941 "parser_bison.y"
    { (yyval.val) = NFT_META_PROTOCOL; }
    break;

  case 332:

/* Line 1806 of yacc.c  */
#line 1942 "parser_bison.y"
    { (yyval.val) = NFT_META_PRIORITY; }
    break;

  case 333:

/* Line 1806 of yacc.c  */
#line 1945 "parser_bison.y"
    { (yyval.val) = NFT_META_MARK; }
    break;

  case 334:

/* Line 1806 of yacc.c  */
#line 1946 "parser_bison.y"
    { (yyval.val) = NFT_META_IIF; }
    break;

  case 335:

/* Line 1806 of yacc.c  */
#line 1947 "parser_bison.y"
    { (yyval.val) = NFT_META_IIFNAME; }
    break;

  case 336:

/* Line 1806 of yacc.c  */
#line 1948 "parser_bison.y"
    { (yyval.val) = NFT_META_IIFTYPE; }
    break;

  case 337:

/* Line 1806 of yacc.c  */
#line 1949 "parser_bison.y"
    { (yyval.val) = NFT_META_OIF; }
    break;

  case 338:

/* Line 1806 of yacc.c  */
#line 1950 "parser_bison.y"
    { (yyval.val) = NFT_META_OIFNAME; }
    break;

  case 339:

/* Line 1806 of yacc.c  */
#line 1951 "parser_bison.y"
    { (yyval.val) = NFT_META_OIFTYPE; }
    break;

  case 340:

/* Line 1806 of yacc.c  */
#line 1952 "parser_bison.y"
    { (yyval.val) = NFT_META_SKUID; }
    break;

  case 341:

/* Line 1806 of yacc.c  */
#line 1953 "parser_bison.y"
    { (yyval.val) = NFT_META_SKGID; }
    break;

  case 342:

/* Line 1806 of yacc.c  */
#line 1954 "parser_bison.y"
    { (yyval.val) = NFT_META_NFTRACE; }
    break;

  case 343:

/* Line 1806 of yacc.c  */
#line 1955 "parser_bison.y"
    { (yyval.val) = NFT_META_RTCLASSID; }
    break;

  case 344:

/* Line 1806 of yacc.c  */
#line 1956 "parser_bison.y"
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
    break;

  case 345:

/* Line 1806 of yacc.c  */
#line 1957 "parser_bison.y"
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
    break;

  case 346:

/* Line 1806 of yacc.c  */
#line 1958 "parser_bison.y"
    { (yyval.val) = NFT_META_PKTTYPE; }
    break;

  case 347:

/* Line 1806 of yacc.c  */
#line 1959 "parser_bison.y"
    { (yyval.val) = NFT_META_CPU; }
    break;

  case 348:

/* Line 1806 of yacc.c  */
#line 1960 "parser_bison.y"
    { (yyval.val) = NFT_META_IIFGROUP; }
    break;

  case 349:

/* Line 1806 of yacc.c  */
#line 1961 "parser_bison.y"
    { (yyval.val) = NFT_META_OIFGROUP; }
    break;

  case 350:

/* Line 1806 of yacc.c  */
#line 1962 "parser_bison.y"
    { (yyval.val) = NFT_META_CGROUP; }
    break;

  case 351:

/* Line 1806 of yacc.c  */
#line 1966 "parser_bison.y"
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].expr));
			}
    break;

  case 352:

/* Line 1806 of yacc.c  */
#line 1970 "parser_bison.y"
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 353:

/* Line 1806 of yacc.c  */
#line 1976 "parser_bison.y"
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[(2) - (2)].val));
			}
    break;

  case 354:

/* Line 1806 of yacc.c  */
#line 1981 "parser_bison.y"
    { (yyval.val) = NFT_CT_STATE; }
    break;

  case 355:

/* Line 1806 of yacc.c  */
#line 1982 "parser_bison.y"
    { (yyval.val) = NFT_CT_DIRECTION; }
    break;

  case 356:

/* Line 1806 of yacc.c  */
#line 1983 "parser_bison.y"
    { (yyval.val) = NFT_CT_STATUS; }
    break;

  case 357:

/* Line 1806 of yacc.c  */
#line 1984 "parser_bison.y"
    { (yyval.val) = NFT_CT_MARK; }
    break;

  case 358:

/* Line 1806 of yacc.c  */
#line 1985 "parser_bison.y"
    { (yyval.val) = NFT_CT_EXPIRATION; }
    break;

  case 359:

/* Line 1806 of yacc.c  */
#line 1986 "parser_bison.y"
    { (yyval.val) = NFT_CT_HELPER; }
    break;

  case 360:

/* Line 1806 of yacc.c  */
#line 1987 "parser_bison.y"
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
    break;

  case 361:

/* Line 1806 of yacc.c  */
#line 1988 "parser_bison.y"
    { (yyval.val) = NFT_CT_SRC; }
    break;

  case 362:

/* Line 1806 of yacc.c  */
#line 1989 "parser_bison.y"
    { (yyval.val) = NFT_CT_DST; }
    break;

  case 363:

/* Line 1806 of yacc.c  */
#line 1990 "parser_bison.y"
    { (yyval.val) = NFT_CT_PROTOCOL; }
    break;

  case 364:

/* Line 1806 of yacc.c  */
#line 1991 "parser_bison.y"
    { (yyval.val) = NFT_CT_PROTO_SRC; }
    break;

  case 365:

/* Line 1806 of yacc.c  */
#line 1992 "parser_bison.y"
    { (yyval.val) = NFT_CT_PROTO_DST; }
    break;

  case 366:

/* Line 1806 of yacc.c  */
#line 1993 "parser_bison.y"
    { (yyval.val) = NFT_CT_LABELS; }
    break;

  case 367:

/* Line 1806 of yacc.c  */
#line 1997 "parser_bison.y"
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].expr));
			}
    break;

  case 384:

/* Line 1806 of yacc.c  */
#line 2021 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				(yyval.expr)->payload.base	= (yyvsp[(2) - (6)].val);
				(yyval.expr)->payload.offset	= (yyvsp[(4) - (6)].val);
				(yyval.expr)->len			= (yyvsp[(6) - (6)].val);
				(yyval.expr)->dtype		= &integer_type;
			}
    break;

  case 385:

/* Line 1806 of yacc.c  */
#line 2030 "parser_bison.y"
    { (yyval.val) = PROTO_BASE_LL_HDR; }
    break;

  case 386:

/* Line 1806 of yacc.c  */
#line 2031 "parser_bison.y"
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
    break;

  case 387:

/* Line 1806 of yacc.c  */
#line 2032 "parser_bison.y"
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
    break;

  case 388:

/* Line 1806 of yacc.c  */
#line 2036 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[(2) - (2)].val));
			}
    break;

  case 389:

/* Line 1806 of yacc.c  */
#line 2040 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ether");
			}
    break;

  case 390:

/* Line 1806 of yacc.c  */
#line 2047 "parser_bison.y"
    { (yyval.val) = ETHHDR_SADDR; }
    break;

  case 391:

/* Line 1806 of yacc.c  */
#line 2048 "parser_bison.y"
    { (yyval.val) = ETHHDR_DADDR; }
    break;

  case 392:

/* Line 1806 of yacc.c  */
#line 2049 "parser_bison.y"
    { (yyval.val) = ETHHDR_TYPE; }
    break;

  case 393:

/* Line 1806 of yacc.c  */
#line 2053 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[(2) - (2)].val));
			}
    break;

  case 394:

/* Line 1806 of yacc.c  */
#line 2057 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "vlan");
			}
    break;

  case 395:

/* Line 1806 of yacc.c  */
#line 2064 "parser_bison.y"
    { (yyval.val) = VLANHDR_VID; }
    break;

  case 396:

/* Line 1806 of yacc.c  */
#line 2065 "parser_bison.y"
    { (yyval.val) = VLANHDR_CFI; }
    break;

  case 397:

/* Line 1806 of yacc.c  */
#line 2066 "parser_bison.y"
    { (yyval.val) = VLANHDR_PCP; }
    break;

  case 398:

/* Line 1806 of yacc.c  */
#line 2067 "parser_bison.y"
    { (yyval.val) = VLANHDR_TYPE; }
    break;

  case 399:

/* Line 1806 of yacc.c  */
#line 2071 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 400:

/* Line 1806 of yacc.c  */
#line 2075 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "arp");
			}
    break;

  case 401:

/* Line 1806 of yacc.c  */
#line 2082 "parser_bison.y"
    { (yyval.val) = ARPHDR_HRD; }
    break;

  case 402:

/* Line 1806 of yacc.c  */
#line 2083 "parser_bison.y"
    { (yyval.val) = ARPHDR_PRO; }
    break;

  case 403:

/* Line 1806 of yacc.c  */
#line 2084 "parser_bison.y"
    { (yyval.val) = ARPHDR_HLN; }
    break;

  case 404:

/* Line 1806 of yacc.c  */
#line 2085 "parser_bison.y"
    { (yyval.val) = ARPHDR_PLN; }
    break;

  case 405:

/* Line 1806 of yacc.c  */
#line 2086 "parser_bison.y"
    { (yyval.val) = ARPHDR_OP; }
    break;

  case 406:

/* Line 1806 of yacc.c  */
#line 2090 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[(2) - (2)].val));
			}
    break;

  case 407:

/* Line 1806 of yacc.c  */
#line 2094 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ip");
			}
    break;

  case 408:

/* Line 1806 of yacc.c  */
#line 2101 "parser_bison.y"
    { (yyval.val) = IPHDR_VERSION; }
    break;

  case 409:

/* Line 1806 of yacc.c  */
#line 2102 "parser_bison.y"
    { (yyval.val) = IPHDR_HDRLENGTH; }
    break;

  case 410:

/* Line 1806 of yacc.c  */
#line 2103 "parser_bison.y"
    { (yyval.val) = IPHDR_TOS; }
    break;

  case 411:

/* Line 1806 of yacc.c  */
#line 2104 "parser_bison.y"
    { (yyval.val) = IPHDR_LENGTH; }
    break;

  case 412:

/* Line 1806 of yacc.c  */
#line 2105 "parser_bison.y"
    { (yyval.val) = IPHDR_ID; }
    break;

  case 413:

/* Line 1806 of yacc.c  */
#line 2106 "parser_bison.y"
    { (yyval.val) = IPHDR_FRAG_OFF; }
    break;

  case 414:

/* Line 1806 of yacc.c  */
#line 2107 "parser_bison.y"
    { (yyval.val) = IPHDR_TTL; }
    break;

  case 415:

/* Line 1806 of yacc.c  */
#line 2108 "parser_bison.y"
    { (yyval.val) = IPHDR_PROTOCOL; }
    break;

  case 416:

/* Line 1806 of yacc.c  */
#line 2109 "parser_bison.y"
    { (yyval.val) = IPHDR_CHECKSUM; }
    break;

  case 417:

/* Line 1806 of yacc.c  */
#line 2110 "parser_bison.y"
    { (yyval.val) = IPHDR_SADDR; }
    break;

  case 418:

/* Line 1806 of yacc.c  */
#line 2111 "parser_bison.y"
    { (yyval.val) = IPHDR_DADDR; }
    break;

  case 419:

/* Line 1806 of yacc.c  */
#line 2115 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 420:

/* Line 1806 of yacc.c  */
#line 2119 "parser_bison.y"
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 421:

/* Line 1806 of yacc.c  */
#line 2127 "parser_bison.y"
    { (yyval.val) = ICMPHDR_TYPE; }
    break;

  case 422:

/* Line 1806 of yacc.c  */
#line 2128 "parser_bison.y"
    { (yyval.val) = ICMPHDR_CODE; }
    break;

  case 423:

/* Line 1806 of yacc.c  */
#line 2129 "parser_bison.y"
    { (yyval.val) = ICMPHDR_CHECKSUM; }
    break;

  case 424:

/* Line 1806 of yacc.c  */
#line 2130 "parser_bison.y"
    { (yyval.val) = ICMPHDR_ID; }
    break;

  case 425:

/* Line 1806 of yacc.c  */
#line 2131 "parser_bison.y"
    { (yyval.val) = ICMPHDR_SEQ; }
    break;

  case 426:

/* Line 1806 of yacc.c  */
#line 2132 "parser_bison.y"
    { (yyval.val) = ICMPHDR_GATEWAY; }
    break;

  case 427:

/* Line 1806 of yacc.c  */
#line 2133 "parser_bison.y"
    { (yyval.val) = ICMPHDR_MTU; }
    break;

  case 428:

/* Line 1806 of yacc.c  */
#line 2137 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[(2) - (2)].val));
			}
    break;

  case 429:

/* Line 1806 of yacc.c  */
#line 2141 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ip6");
			}
    break;

  case 430:

/* Line 1806 of yacc.c  */
#line 2148 "parser_bison.y"
    { (yyval.val) = IP6HDR_VERSION; }
    break;

  case 431:

/* Line 1806 of yacc.c  */
#line 2149 "parser_bison.y"
    { (yyval.val) = IP6HDR_PRIORITY; }
    break;

  case 432:

/* Line 1806 of yacc.c  */
#line 2150 "parser_bison.y"
    { (yyval.val) = IP6HDR_FLOWLABEL; }
    break;

  case 433:

/* Line 1806 of yacc.c  */
#line 2151 "parser_bison.y"
    { (yyval.val) = IP6HDR_LENGTH; }
    break;

  case 434:

/* Line 1806 of yacc.c  */
#line 2152 "parser_bison.y"
    { (yyval.val) = IP6HDR_NEXTHDR; }
    break;

  case 435:

/* Line 1806 of yacc.c  */
#line 2153 "parser_bison.y"
    { (yyval.val) = IP6HDR_HOPLIMIT; }
    break;

  case 436:

/* Line 1806 of yacc.c  */
#line 2154 "parser_bison.y"
    { (yyval.val) = IP6HDR_SADDR; }
    break;

  case 437:

/* Line 1806 of yacc.c  */
#line 2155 "parser_bison.y"
    { (yyval.val) = IP6HDR_DADDR; }
    break;

  case 438:

/* Line 1806 of yacc.c  */
#line 2158 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[(2) - (2)].val));
			}
    break;

  case 439:

/* Line 1806 of yacc.c  */
#line 2162 "parser_bison.y"
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 440:

/* Line 1806 of yacc.c  */
#line 2170 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_TYPE; }
    break;

  case 441:

/* Line 1806 of yacc.c  */
#line 2171 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_CODE; }
    break;

  case 442:

/* Line 1806 of yacc.c  */
#line 2172 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
    break;

  case 443:

/* Line 1806 of yacc.c  */
#line 2173 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_PPTR; }
    break;

  case 444:

/* Line 1806 of yacc.c  */
#line 2174 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_MTU; }
    break;

  case 445:

/* Line 1806 of yacc.c  */
#line 2175 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_ID; }
    break;

  case 446:

/* Line 1806 of yacc.c  */
#line 2176 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_SEQ; }
    break;

  case 447:

/* Line 1806 of yacc.c  */
#line 2177 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
    break;

  case 448:

/* Line 1806 of yacc.c  */
#line 2181 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[(2) - (2)].val));
			}
    break;

  case 449:

/* Line 1806 of yacc.c  */
#line 2185 "parser_bison.y"
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 450:

/* Line 1806 of yacc.c  */
#line 2193 "parser_bison.y"
    { (yyval.val) = AHHDR_NEXTHDR; }
    break;

  case 451:

/* Line 1806 of yacc.c  */
#line 2194 "parser_bison.y"
    { (yyval.val) = AHHDR_HDRLENGTH; }
    break;

  case 452:

/* Line 1806 of yacc.c  */
#line 2195 "parser_bison.y"
    { (yyval.val) = AHHDR_RESERVED; }
    break;

  case 453:

/* Line 1806 of yacc.c  */
#line 2196 "parser_bison.y"
    { (yyval.val) = AHHDR_SPI; }
    break;

  case 454:

/* Line 1806 of yacc.c  */
#line 2197 "parser_bison.y"
    { (yyval.val) = AHHDR_SEQUENCE; }
    break;

  case 455:

/* Line 1806 of yacc.c  */
#line 2201 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 456:

/* Line 1806 of yacc.c  */
#line 2205 "parser_bison.y"
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 457:

/* Line 1806 of yacc.c  */
#line 2213 "parser_bison.y"
    { (yyval.val) = ESPHDR_SPI; }
    break;

  case 458:

/* Line 1806 of yacc.c  */
#line 2214 "parser_bison.y"
    { (yyval.val) = ESPHDR_SEQUENCE; }
    break;

  case 459:

/* Line 1806 of yacc.c  */
#line 2218 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 460:

/* Line 1806 of yacc.c  */
#line 2222 "parser_bison.y"
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 461:

/* Line 1806 of yacc.c  */
#line 2230 "parser_bison.y"
    { (yyval.val) = COMPHDR_NEXTHDR; }
    break;

  case 462:

/* Line 1806 of yacc.c  */
#line 2231 "parser_bison.y"
    { (yyval.val) = COMPHDR_FLAGS; }
    break;

  case 463:

/* Line 1806 of yacc.c  */
#line 2232 "parser_bison.y"
    { (yyval.val) = COMPHDR_CPI; }
    break;

  case 464:

/* Line 1806 of yacc.c  */
#line 2236 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 465:

/* Line 1806 of yacc.c  */
#line 2240 "parser_bison.y"
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 466:

/* Line 1806 of yacc.c  */
#line 2248 "parser_bison.y"
    { (yyval.val) = UDPHDR_SPORT; }
    break;

  case 467:

/* Line 1806 of yacc.c  */
#line 2249 "parser_bison.y"
    { (yyval.val) = UDPHDR_DPORT; }
    break;

  case 468:

/* Line 1806 of yacc.c  */
#line 2250 "parser_bison.y"
    { (yyval.val) = UDPHDR_LENGTH; }
    break;

  case 469:

/* Line 1806 of yacc.c  */
#line 2251 "parser_bison.y"
    { (yyval.val) = UDPHDR_CHECKSUM; }
    break;

  case 470:

/* Line 1806 of yacc.c  */
#line 2255 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[(2) - (2)].val));
			}
    break;

  case 471:

/* Line 1806 of yacc.c  */
#line 2259 "parser_bison.y"
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 472:

/* Line 1806 of yacc.c  */
#line 2267 "parser_bison.y"
    { (yyval.val) = UDPHDR_SPORT; }
    break;

  case 473:

/* Line 1806 of yacc.c  */
#line 2268 "parser_bison.y"
    { (yyval.val) = UDPHDR_DPORT; }
    break;

  case 474:

/* Line 1806 of yacc.c  */
#line 2269 "parser_bison.y"
    { (yyval.val) = UDPHDR_LENGTH; }
    break;

  case 475:

/* Line 1806 of yacc.c  */
#line 2270 "parser_bison.y"
    { (yyval.val) = UDPHDR_CHECKSUM; }
    break;

  case 476:

/* Line 1806 of yacc.c  */
#line 2274 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 477:

/* Line 1806 of yacc.c  */
#line 2278 "parser_bison.y"
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 478:

/* Line 1806 of yacc.c  */
#line 2286 "parser_bison.y"
    { (yyval.val) = TCPHDR_SPORT; }
    break;

  case 479:

/* Line 1806 of yacc.c  */
#line 2287 "parser_bison.y"
    { (yyval.val) = TCPHDR_DPORT; }
    break;

  case 480:

/* Line 1806 of yacc.c  */
#line 2288 "parser_bison.y"
    { (yyval.val) = TCPHDR_SEQ; }
    break;

  case 481:

/* Line 1806 of yacc.c  */
#line 2289 "parser_bison.y"
    { (yyval.val) = TCPHDR_ACKSEQ; }
    break;

  case 482:

/* Line 1806 of yacc.c  */
#line 2290 "parser_bison.y"
    { (yyval.val) = TCPHDR_DOFF; }
    break;

  case 483:

/* Line 1806 of yacc.c  */
#line 2291 "parser_bison.y"
    { (yyval.val) = TCPHDR_RESERVED; }
    break;

  case 484:

/* Line 1806 of yacc.c  */
#line 2292 "parser_bison.y"
    { (yyval.val) = TCPHDR_FLAGS; }
    break;

  case 485:

/* Line 1806 of yacc.c  */
#line 2293 "parser_bison.y"
    { (yyval.val) = TCPHDR_WINDOW; }
    break;

  case 486:

/* Line 1806 of yacc.c  */
#line 2294 "parser_bison.y"
    { (yyval.val) = TCPHDR_CHECKSUM; }
    break;

  case 487:

/* Line 1806 of yacc.c  */
#line 2295 "parser_bison.y"
    { (yyval.val) = TCPHDR_URGPTR; }
    break;

  case 488:

/* Line 1806 of yacc.c  */
#line 2299 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 489:

/* Line 1806 of yacc.c  */
#line 2303 "parser_bison.y"
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 490:

/* Line 1806 of yacc.c  */
#line 2311 "parser_bison.y"
    { (yyval.val) = DCCPHDR_SPORT; }
    break;

  case 491:

/* Line 1806 of yacc.c  */
#line 2312 "parser_bison.y"
    { (yyval.val) = DCCPHDR_DPORT; }
    break;

  case 492:

/* Line 1806 of yacc.c  */
#line 2313 "parser_bison.y"
    { (yyval.val) = DCCPHDR_TYPE; }
    break;

  case 493:

/* Line 1806 of yacc.c  */
#line 2317 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 494:

/* Line 1806 of yacc.c  */
#line 2321 "parser_bison.y"
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 495:

/* Line 1806 of yacc.c  */
#line 2329 "parser_bison.y"
    { (yyval.val) = SCTPHDR_SPORT; }
    break;

  case 496:

/* Line 1806 of yacc.c  */
#line 2330 "parser_bison.y"
    { (yyval.val) = SCTPHDR_DPORT; }
    break;

  case 497:

/* Line 1806 of yacc.c  */
#line 2331 "parser_bison.y"
    { (yyval.val) = SCTPHDR_VTAG; }
    break;

  case 498:

/* Line 1806 of yacc.c  */
#line 2332 "parser_bison.y"
    { (yyval.val) = SCTPHDR_CHECKSUM; }
    break;

  case 506:

/* Line 1806 of yacc.c  */
#line 2345 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[(2) - (2)].val));
			}
    break;

  case 507:

/* Line 1806 of yacc.c  */
#line 2350 "parser_bison.y"
    { (yyval.val) = HBHHDR_NEXTHDR; }
    break;

  case 508:

/* Line 1806 of yacc.c  */
#line 2351 "parser_bison.y"
    { (yyval.val) = HBHHDR_HDRLENGTH; }
    break;

  case 509:

/* Line 1806 of yacc.c  */
#line 2355 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[(2) - (2)].val));
			}
    break;

  case 510:

/* Line 1806 of yacc.c  */
#line 2360 "parser_bison.y"
    { (yyval.val) = RTHDR_NEXTHDR; }
    break;

  case 511:

/* Line 1806 of yacc.c  */
#line 2361 "parser_bison.y"
    { (yyval.val) = RTHDR_HDRLENGTH; }
    break;

  case 512:

/* Line 1806 of yacc.c  */
#line 2362 "parser_bison.y"
    { (yyval.val) = RTHDR_TYPE; }
    break;

  case 513:

/* Line 1806 of yacc.c  */
#line 2363 "parser_bison.y"
    { (yyval.val) = RTHDR_SEG_LEFT; }
    break;

  case 514:

/* Line 1806 of yacc.c  */
#line 2367 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[(2) - (2)].val));
			}
    break;

  case 515:

/* Line 1806 of yacc.c  */
#line 2373 "parser_bison.y"
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[(3) - (4)].val) - 1;
			}
    break;

  case 516:

/* Line 1806 of yacc.c  */
#line 2379 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[(2) - (2)].val));
			}
    break;

  case 517:

/* Line 1806 of yacc.c  */
#line 2384 "parser_bison.y"
    { (yyval.val) = RT2HDR_ADDR; }
    break;

  case 518:

/* Line 1806 of yacc.c  */
#line 2388 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[(2) - (2)].val));
			}
    break;

  case 519:

/* Line 1806 of yacc.c  */
#line 2393 "parser_bison.y"
    { (yyval.val) = FRAGHDR_NEXTHDR; }
    break;

  case 520:

/* Line 1806 of yacc.c  */
#line 2394 "parser_bison.y"
    { (yyval.val) = FRAGHDR_RESERVED; }
    break;

  case 521:

/* Line 1806 of yacc.c  */
#line 2395 "parser_bison.y"
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
    break;

  case 522:

/* Line 1806 of yacc.c  */
#line 2396 "parser_bison.y"
    { (yyval.val) = FRAGHDR_RESERVED2; }
    break;

  case 523:

/* Line 1806 of yacc.c  */
#line 2397 "parser_bison.y"
    { (yyval.val) = FRAGHDR_MFRAGS; }
    break;

  case 524:

/* Line 1806 of yacc.c  */
#line 2398 "parser_bison.y"
    { (yyval.val) = FRAGHDR_ID; }
    break;

  case 525:

/* Line 1806 of yacc.c  */
#line 2402 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[(2) - (2)].val));
			}
    break;

  case 526:

/* Line 1806 of yacc.c  */
#line 2407 "parser_bison.y"
    { (yyval.val) = DSTHDR_NEXTHDR; }
    break;

  case 527:

/* Line 1806 of yacc.c  */
#line 2408 "parser_bison.y"
    { (yyval.val) = DSTHDR_HDRLENGTH; }
    break;

  case 528:

/* Line 1806 of yacc.c  */
#line 2412 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[(2) - (2)].val));
			}
    break;

  case 529:

/* Line 1806 of yacc.c  */
#line 2417 "parser_bison.y"
    { (yyval.val) = MHHDR_NEXTHDR; }
    break;

  case 530:

/* Line 1806 of yacc.c  */
#line 2418 "parser_bison.y"
    { (yyval.val) = MHHDR_HDRLENGTH; }
    break;

  case 531:

/* Line 1806 of yacc.c  */
#line 2419 "parser_bison.y"
    { (yyval.val) = MHHDR_TYPE; }
    break;

  case 532:

/* Line 1806 of yacc.c  */
#line 2420 "parser_bison.y"
    { (yyval.val) = MHHDR_RESERVED; }
    break;

  case 533:

/* Line 1806 of yacc.c  */
#line 2421 "parser_bison.y"
    { (yyval.val) = MHHDR_CHECKSUM; }
    break;



/* Line 1806 of yacc.c  */
#line 7927 "parser_bison.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 2424 "parser_bison.y"


