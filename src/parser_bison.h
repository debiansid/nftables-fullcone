/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    PLUS = 280,
    INCLUDE = 281,
    DEFINE = 282,
    REDEFINE = 283,
    UNDEFINE = 284,
    FIB = 285,
    SOCKET = 286,
    TRANSPARENT = 287,
    TPROXY = 288,
    OSF = 289,
    SYNPROXY = 290,
    MSS = 291,
    WSCALE = 292,
    SACKPERM = 293,
    HOOK = 294,
    DEVICE = 295,
    DEVICES = 296,
    TABLE = 297,
    TABLES = 298,
    CHAIN = 299,
    CHAINS = 300,
    RULE = 301,
    RULES = 302,
    SETS = 303,
    SET = 304,
    ELEMENT = 305,
    MAP = 306,
    MAPS = 307,
    FLOWTABLE = 308,
    HANDLE = 309,
    RULESET = 310,
    TRACE = 311,
    INET = 312,
    NETDEV = 313,
    ADD = 314,
    UPDATE = 315,
    REPLACE = 316,
    CREATE = 317,
    INSERT = 318,
    DELETE = 319,
    GET = 320,
    LIST = 321,
    RESET = 322,
    FLUSH = 323,
    RENAME = 324,
    DESCRIBE = 325,
    IMPORT = 326,
    EXPORT = 327,
    MONITOR = 328,
    ALL = 329,
    ACCEPT = 330,
    DROP = 331,
    CONTINUE = 332,
    JUMP = 333,
    GOTO = 334,
    RETURN = 335,
    TO = 336,
    CONSTANT = 337,
    INTERVAL = 338,
    DYNAMIC = 339,
    AUTOMERGE = 340,
    TIMEOUT = 341,
    GC_INTERVAL = 342,
    ELEMENTS = 343,
    EXPIRES = 344,
    POLICY = 345,
    MEMORY = 346,
    PERFORMANCE = 347,
    SIZE = 348,
    FLOW = 349,
    OFFLOAD = 350,
    METER = 351,
    METERS = 352,
    FLOWTABLES = 353,
    NUM = 354,
    STRING = 355,
    QUOTED_STRING = 356,
    ASTERISK_STRING = 357,
    LL_HDR = 358,
    NETWORK_HDR = 359,
    TRANSPORT_HDR = 360,
    BRIDGE = 361,
    ETHER = 362,
    SADDR = 363,
    DADDR = 364,
    TYPE = 365,
    VLAN = 366,
    ID = 367,
    CFI = 368,
    PCP = 369,
    ARP = 370,
    HTYPE = 371,
    PTYPE = 372,
    HLEN = 373,
    PLEN = 374,
    OPERATION = 375,
    IP = 376,
    HDRVERSION = 377,
    HDRLENGTH = 378,
    DSCP = 379,
    ECN = 380,
    LENGTH = 381,
    FRAG_OFF = 382,
    TTL = 383,
    PROTOCOL = 384,
    CHECKSUM = 385,
    PTR = 386,
    VALUE = 387,
    LSRR = 388,
    RR = 389,
    SSRR = 390,
    RA = 391,
    ICMP = 392,
    CODE = 393,
    SEQUENCE = 394,
    GATEWAY = 395,
    MTU = 396,
    IGMP = 397,
    MRT = 398,
    OPTIONS = 399,
    IP6 = 400,
    PRIORITY = 401,
    FLOWLABEL = 402,
    NEXTHDR = 403,
    HOPLIMIT = 404,
    ICMP6 = 405,
    PPTR = 406,
    MAXDELAY = 407,
    AH = 408,
    RESERVED = 409,
    SPI = 410,
    ESP = 411,
    COMP = 412,
    FLAGS = 413,
    CPI = 414,
    UDP = 415,
    SPORT = 416,
    DPORT = 417,
    UDPLITE = 418,
    CSUMCOV = 419,
    TCP = 420,
    ACKSEQ = 421,
    DOFF = 422,
    WINDOW = 423,
    URGPTR = 424,
    OPTION = 425,
    ECHO = 426,
    EOL = 427,
    MAXSEG = 428,
    NOOP = 429,
    SACK = 430,
    SACK0 = 431,
    SACK1 = 432,
    SACK2 = 433,
    SACK3 = 434,
    SACK_PERMITTED = 435,
    TIMESTAMP = 436,
    KIND = 437,
    COUNT = 438,
    LEFT = 439,
    RIGHT = 440,
    TSVAL = 441,
    TSECR = 442,
    DCCP = 443,
    SCTP = 444,
    VTAG = 445,
    RT = 446,
    RT0 = 447,
    RT2 = 448,
    RT4 = 449,
    SEG_LEFT = 450,
    ADDR = 451,
    LAST_ENT = 452,
    TAG = 453,
    SID = 454,
    HBH = 455,
    FRAG = 456,
    RESERVED2 = 457,
    MORE_FRAGMENTS = 458,
    DST = 459,
    MH = 460,
    META = 461,
    MARK = 462,
    IIF = 463,
    IIFNAME = 464,
    IIFTYPE = 465,
    OIF = 466,
    OIFNAME = 467,
    OIFTYPE = 468,
    SKUID = 469,
    SKGID = 470,
    NFTRACE = 471,
    RTCLASSID = 472,
    IBRIPORT = 473,
    OBRIPORT = 474,
    IBRIDGENAME = 475,
    OBRIDGENAME = 476,
    PKTTYPE = 477,
    CPU = 478,
    IIFGROUP = 479,
    OIFGROUP = 480,
    CGROUP = 481,
    CLASSID = 482,
    NEXTHOP = 483,
    CT = 484,
    L3PROTOCOL = 485,
    PROTO_SRC = 486,
    PROTO_DST = 487,
    ZONE = 488,
    DIRECTION = 489,
    EVENT = 490,
    EXPECTATION = 491,
    EXPIRATION = 492,
    HELPER = 493,
    LABEL = 494,
    STATE = 495,
    STATUS = 496,
    ORIGINAL = 497,
    REPLY = 498,
    COUNTER = 499,
    NAME = 500,
    PACKETS = 501,
    BYTES = 502,
    AVGPKT = 503,
    COUNTERS = 504,
    QUOTAS = 505,
    LIMITS = 506,
    HELPERS = 507,
    LOG = 508,
    PREFIX = 509,
    GROUP = 510,
    SNAPLEN = 511,
    QUEUE_THRESHOLD = 512,
    LEVEL = 513,
    LIMIT = 514,
    RATE = 515,
    BURST = 516,
    OVER = 517,
    UNTIL = 518,
    QUOTA = 519,
    USED = 520,
    SECMARK = 521,
    SECMARKS = 522,
    NANOSECOND = 523,
    MICROSECOND = 524,
    MILLISECOND = 525,
    SECOND = 526,
    MINUTE = 527,
    HOUR = 528,
    DAY = 529,
    WEEK = 530,
    _REJECT = 531,
    WITH = 532,
    ICMPX = 533,
    SNAT = 534,
    DNAT = 535,
    MASQUERADE = 536,
    REDIRECT = 537,
    RANDOM = 538,
    FULLY_RANDOM = 539,
    PERSISTENT = 540,
    QUEUE = 541,
    QUEUENUM = 542,
    BYPASS = 543,
    FANOUT = 544,
    DUP = 545,
    FWD = 546,
    NUMGEN = 547,
    INC = 548,
    MOD = 549,
    OFFSET = 550,
    JHASH = 551,
    SYMHASH = 552,
    SEED = 553,
    POSITION = 554,
    INDEX = 555,
    COMMENT = 556,
    XML = 557,
    JSON = 558,
    VM = 559,
    NOTRACK = 560,
    EXISTS = 561,
    MISSING = 562,
    EXTHDR = 563,
    IPSEC = 564,
    MODE = 565,
    REQID = 566,
    SPNUM = 567,
    TRANSPORT = 568,
    TUNNEL = 569,
    IN = 570,
    OUT = 571
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
#define PLUS 280
#define INCLUDE 281
#define DEFINE 282
#define REDEFINE 283
#define UNDEFINE 284
#define FIB 285
#define SOCKET 286
#define TRANSPARENT 287
#define TPROXY 288
#define OSF 289
#define SYNPROXY 290
#define MSS 291
#define WSCALE 292
#define SACKPERM 293
#define HOOK 294
#define DEVICE 295
#define DEVICES 296
#define TABLE 297
#define TABLES 298
#define CHAIN 299
#define CHAINS 300
#define RULE 301
#define RULES 302
#define SETS 303
#define SET 304
#define ELEMENT 305
#define MAP 306
#define MAPS 307
#define FLOWTABLE 308
#define HANDLE 309
#define RULESET 310
#define TRACE 311
#define INET 312
#define NETDEV 313
#define ADD 314
#define UPDATE 315
#define REPLACE 316
#define CREATE 317
#define INSERT 318
#define DELETE 319
#define GET 320
#define LIST 321
#define RESET 322
#define FLUSH 323
#define RENAME 324
#define DESCRIBE 325
#define IMPORT 326
#define EXPORT 327
#define MONITOR 328
#define ALL 329
#define ACCEPT 330
#define DROP 331
#define CONTINUE 332
#define JUMP 333
#define GOTO 334
#define RETURN 335
#define TO 336
#define CONSTANT 337
#define INTERVAL 338
#define DYNAMIC 339
#define AUTOMERGE 340
#define TIMEOUT 341
#define GC_INTERVAL 342
#define ELEMENTS 343
#define EXPIRES 344
#define POLICY 345
#define MEMORY 346
#define PERFORMANCE 347
#define SIZE 348
#define FLOW 349
#define OFFLOAD 350
#define METER 351
#define METERS 352
#define FLOWTABLES 353
#define NUM 354
#define STRING 355
#define QUOTED_STRING 356
#define ASTERISK_STRING 357
#define LL_HDR 358
#define NETWORK_HDR 359
#define TRANSPORT_HDR 360
#define BRIDGE 361
#define ETHER 362
#define SADDR 363
#define DADDR 364
#define TYPE 365
#define VLAN 366
#define ID 367
#define CFI 368
#define PCP 369
#define ARP 370
#define HTYPE 371
#define PTYPE 372
#define HLEN 373
#define PLEN 374
#define OPERATION 375
#define IP 376
#define HDRVERSION 377
#define HDRLENGTH 378
#define DSCP 379
#define ECN 380
#define LENGTH 381
#define FRAG_OFF 382
#define TTL 383
#define PROTOCOL 384
#define CHECKSUM 385
#define PTR 386
#define VALUE 387
#define LSRR 388
#define RR 389
#define SSRR 390
#define RA 391
#define ICMP 392
#define CODE 393
#define SEQUENCE 394
#define GATEWAY 395
#define MTU 396
#define IGMP 397
#define MRT 398
#define OPTIONS 399
#define IP6 400
#define PRIORITY 401
#define FLOWLABEL 402
#define NEXTHDR 403
#define HOPLIMIT 404
#define ICMP6 405
#define PPTR 406
#define MAXDELAY 407
#define AH 408
#define RESERVED 409
#define SPI 410
#define ESP 411
#define COMP 412
#define FLAGS 413
#define CPI 414
#define UDP 415
#define SPORT 416
#define DPORT 417
#define UDPLITE 418
#define CSUMCOV 419
#define TCP 420
#define ACKSEQ 421
#define DOFF 422
#define WINDOW 423
#define URGPTR 424
#define OPTION 425
#define ECHO 426
#define EOL 427
#define MAXSEG 428
#define NOOP 429
#define SACK 430
#define SACK0 431
#define SACK1 432
#define SACK2 433
#define SACK3 434
#define SACK_PERMITTED 435
#define TIMESTAMP 436
#define KIND 437
#define COUNT 438
#define LEFT 439
#define RIGHT 440
#define TSVAL 441
#define TSECR 442
#define DCCP 443
#define SCTP 444
#define VTAG 445
#define RT 446
#define RT0 447
#define RT2 448
#define RT4 449
#define SEG_LEFT 450
#define ADDR 451
#define LAST_ENT 452
#define TAG 453
#define SID 454
#define HBH 455
#define FRAG 456
#define RESERVED2 457
#define MORE_FRAGMENTS 458
#define DST 459
#define MH 460
#define META 461
#define MARK 462
#define IIF 463
#define IIFNAME 464
#define IIFTYPE 465
#define OIF 466
#define OIFNAME 467
#define OIFTYPE 468
#define SKUID 469
#define SKGID 470
#define NFTRACE 471
#define RTCLASSID 472
#define IBRIPORT 473
#define OBRIPORT 474
#define IBRIDGENAME 475
#define OBRIDGENAME 476
#define PKTTYPE 477
#define CPU 478
#define IIFGROUP 479
#define OIFGROUP 480
#define CGROUP 481
#define CLASSID 482
#define NEXTHOP 483
#define CT 484
#define L3PROTOCOL 485
#define PROTO_SRC 486
#define PROTO_DST 487
#define ZONE 488
#define DIRECTION 489
#define EVENT 490
#define EXPECTATION 491
#define EXPIRATION 492
#define HELPER 493
#define LABEL 494
#define STATE 495
#define STATUS 496
#define ORIGINAL 497
#define REPLY 498
#define COUNTER 499
#define NAME 500
#define PACKETS 501
#define BYTES 502
#define AVGPKT 503
#define COUNTERS 504
#define QUOTAS 505
#define LIMITS 506
#define HELPERS 507
#define LOG 508
#define PREFIX 509
#define GROUP 510
#define SNAPLEN 511
#define QUEUE_THRESHOLD 512
#define LEVEL 513
#define LIMIT 514
#define RATE 515
#define BURST 516
#define OVER 517
#define UNTIL 518
#define QUOTA 519
#define USED 520
#define SECMARK 521
#define SECMARKS 522
#define NANOSECOND 523
#define MICROSECOND 524
#define MILLISECOND 525
#define SECOND 526
#define MINUTE 527
#define HOUR 528
#define DAY 529
#define WEEK 530
#define _REJECT 531
#define WITH 532
#define ICMPX 533
#define SNAT 534
#define DNAT 535
#define MASQUERADE 536
#define REDIRECT 537
#define RANDOM 538
#define FULLY_RANDOM 539
#define PERSISTENT 540
#define QUEUE 541
#define QUEUENUM 542
#define BYPASS 543
#define FANOUT 544
#define DUP 545
#define FWD 546
#define NUMGEN 547
#define INC 548
#define MOD 549
#define OFFSET 550
#define JHASH 551
#define SYMHASH 552
#define SEED 553
#define POSITION 554
#define INDEX 555
#define COMMENT 556
#define XML 557
#define JSON 558
#define VM 559
#define NOTRACK 560
#define EXISTS 561
#define MISSING 562
#define EXTHDR 563
#define IPSEC 564
#define MODE 565
#define REQID 566
#define SPNUM 567
#define TRANSPORT 568
#define TUNNEL 569
#define IN 570
#define OUT 571

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 135 "parser_bison.y" /* yacc.c:1921  */

	uint64_t		val;
	uint32_t		val32;
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
	struct secmark		*secmark;
	struct ct		*ct;
	struct limit		*limit;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	struct prio_spec	prio_spec;
	const struct exthdr_desc *exthdr_desc;

#line 720 "parser_bison.h" /* yacc.c:1921  */
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
