/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 130 "parser_bison.y" /* yacc.c:1909  */

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

#line 616 "parser_bison.h" /* yacc.c:1909  */
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
