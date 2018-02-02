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
#line 134 "parser_bison.y" /* yacc.c:1909  */

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

#line 626 "parser_bison.h" /* yacc.c:1909  */
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
