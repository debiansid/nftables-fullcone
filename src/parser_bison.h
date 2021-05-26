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
    WILDCARD = 288,
    CGROUPV2 = 289,
    TPROXY = 290,
    OSF = 291,
    SYNPROXY = 292,
    MSS = 293,
    WSCALE = 294,
    TYPEOF = 295,
    HOOK = 296,
    DEVICE = 297,
    DEVICES = 298,
    TABLE = 299,
    TABLES = 300,
    CHAIN = 301,
    CHAINS = 302,
    RULE = 303,
    RULES = 304,
    SETS = 305,
    SET = 306,
    ELEMENT = 307,
    MAP = 308,
    MAPS = 309,
    FLOWTABLE = 310,
    HANDLE = 311,
    RULESET = 312,
    TRACE = 313,
    INET = 314,
    NETDEV = 315,
    ADD = 316,
    UPDATE = 317,
    REPLACE = 318,
    CREATE = 319,
    INSERT = 320,
    DELETE = 321,
    GET = 322,
    LIST = 323,
    RESET = 324,
    FLUSH = 325,
    RENAME = 326,
    DESCRIBE = 327,
    IMPORT = 328,
    EXPORT = 329,
    MONITOR = 330,
    ALL = 331,
    ACCEPT = 332,
    DROP = 333,
    CONTINUE = 334,
    JUMP = 335,
    GOTO = 336,
    RETURN = 337,
    TO = 338,
    CONSTANT = 339,
    INTERVAL = 340,
    DYNAMIC = 341,
    AUTOMERGE = 342,
    TIMEOUT = 343,
    GC_INTERVAL = 344,
    ELEMENTS = 345,
    EXPIRES = 346,
    POLICY = 347,
    MEMORY = 348,
    PERFORMANCE = 349,
    SIZE = 350,
    FLOW = 351,
    OFFLOAD = 352,
    METER = 353,
    METERS = 354,
    FLOWTABLES = 355,
    NUM = 356,
    STRING = 357,
    QUOTED_STRING = 358,
    ASTERISK_STRING = 359,
    LL_HDR = 360,
    NETWORK_HDR = 361,
    TRANSPORT_HDR = 362,
    BRIDGE = 363,
    ETHER = 364,
    SADDR = 365,
    DADDR = 366,
    TYPE = 367,
    VLAN = 368,
    ID = 369,
    CFI = 370,
    PCP = 371,
    ARP = 372,
    HTYPE = 373,
    PTYPE = 374,
    HLEN = 375,
    PLEN = 376,
    OPERATION = 377,
    IP = 378,
    HDRVERSION = 379,
    HDRLENGTH = 380,
    DSCP = 381,
    ECN = 382,
    LENGTH = 383,
    FRAG_OFF = 384,
    TTL = 385,
    PROTOCOL = 386,
    CHECKSUM = 387,
    PTR = 388,
    VALUE = 389,
    LSRR = 390,
    RR = 391,
    SSRR = 392,
    RA = 393,
    ICMP = 394,
    CODE = 395,
    SEQUENCE = 396,
    GATEWAY = 397,
    MTU = 398,
    IGMP = 399,
    MRT = 400,
    OPTIONS = 401,
    IP6 = 402,
    PRIORITY = 403,
    FLOWLABEL = 404,
    NEXTHDR = 405,
    HOPLIMIT = 406,
    ICMP6 = 407,
    PPTR = 408,
    MAXDELAY = 409,
    AH = 410,
    RESERVED = 411,
    SPI = 412,
    ESP = 413,
    COMP = 414,
    FLAGS = 415,
    CPI = 416,
    PORT = 417,
    UDP = 418,
    SPORT = 419,
    DPORT = 420,
    UDPLITE = 421,
    CSUMCOV = 422,
    TCP = 423,
    ACKSEQ = 424,
    DOFF = 425,
    WINDOW = 426,
    URGPTR = 427,
    OPTION = 428,
    ECHO = 429,
    EOL = 430,
    NOP = 431,
    SACK = 432,
    SACK0 = 433,
    SACK1 = 434,
    SACK2 = 435,
    SACK3 = 436,
    SACK_PERM = 437,
    TIMESTAMP = 438,
    KIND = 439,
    COUNT = 440,
    LEFT = 441,
    RIGHT = 442,
    TSVAL = 443,
    TSECR = 444,
    DCCP = 445,
    SCTP = 446,
    CHUNK = 447,
    DATA = 448,
    INIT = 449,
    INIT_ACK = 450,
    HEARTBEAT = 451,
    HEARTBEAT_ACK = 452,
    ABORT = 453,
    SHUTDOWN = 454,
    SHUTDOWN_ACK = 455,
    ERROR = 456,
    COOKIE_ECHO = 457,
    COOKIE_ACK = 458,
    ECNE = 459,
    CWR = 460,
    SHUTDOWN_COMPLETE = 461,
    ASCONF_ACK = 462,
    FORWARD_TSN = 463,
    ASCONF = 464,
    TSN = 465,
    STREAM = 466,
    SSN = 467,
    PPID = 468,
    INIT_TAG = 469,
    A_RWND = 470,
    NUM_OSTREAMS = 471,
    NUM_ISTREAMS = 472,
    INIT_TSN = 473,
    CUM_TSN_ACK = 474,
    NUM_GACK_BLOCKS = 475,
    NUM_DUP_TSNS = 476,
    LOWEST_TSN = 477,
    SEQNO = 478,
    NEW_CUM_TSN = 479,
    VTAG = 480,
    RT = 481,
    RT0 = 482,
    RT2 = 483,
    RT4 = 484,
    SEG_LEFT = 485,
    ADDR = 486,
    LAST_ENT = 487,
    TAG = 488,
    SID = 489,
    HBH = 490,
    FRAG = 491,
    RESERVED2 = 492,
    MORE_FRAGMENTS = 493,
    DST = 494,
    MH = 495,
    META = 496,
    MARK = 497,
    IIF = 498,
    IIFNAME = 499,
    IIFTYPE = 500,
    OIF = 501,
    OIFNAME = 502,
    OIFTYPE = 503,
    SKUID = 504,
    SKGID = 505,
    NFTRACE = 506,
    RTCLASSID = 507,
    IBRIPORT = 508,
    OBRIPORT = 509,
    IBRIDGENAME = 510,
    OBRIDGENAME = 511,
    PKTTYPE = 512,
    CPU = 513,
    IIFGROUP = 514,
    OIFGROUP = 515,
    CGROUP = 516,
    TIME = 517,
    CLASSID = 518,
    NEXTHOP = 519,
    CT = 520,
    L3PROTOCOL = 521,
    PROTO_SRC = 522,
    PROTO_DST = 523,
    ZONE = 524,
    DIRECTION = 525,
    EVENT = 526,
    EXPECTATION = 527,
    EXPIRATION = 528,
    HELPER = 529,
    LABEL = 530,
    STATE = 531,
    STATUS = 532,
    ORIGINAL = 533,
    REPLY = 534,
    COUNTER = 535,
    NAME = 536,
    PACKETS = 537,
    BYTES = 538,
    AVGPKT = 539,
    COUNTERS = 540,
    QUOTAS = 541,
    LIMITS = 542,
    SYNPROXYS = 543,
    HELPERS = 544,
    LOG = 545,
    PREFIX = 546,
    GROUP = 547,
    SNAPLEN = 548,
    QUEUE_THRESHOLD = 549,
    LEVEL = 550,
    LIMIT = 551,
    RATE = 552,
    BURST = 553,
    OVER = 554,
    UNTIL = 555,
    QUOTA = 556,
    USED = 557,
    SECMARK = 558,
    SECMARKS = 559,
    SECOND = 560,
    MINUTE = 561,
    HOUR = 562,
    DAY = 563,
    WEEK = 564,
    _REJECT = 565,
    WITH = 566,
    ICMPX = 567,
    SNAT = 568,
    DNAT = 569,
    MASQUERADE = 570,
    REDIRECT = 571,
    RANDOM = 572,
    FULLY_RANDOM = 573,
    PERSISTENT = 574,
    QUEUE = 575,
    QUEUENUM = 576,
    BYPASS = 577,
    FANOUT = 578,
    DUP = 579,
    FWD = 580,
    NUMGEN = 581,
    INC = 582,
    MOD = 583,
    OFFSET = 584,
    JHASH = 585,
    SYMHASH = 586,
    SEED = 587,
    POSITION = 588,
    INDEX = 589,
    COMMENT = 590,
    XML = 591,
    JSON = 592,
    VM = 593,
    NOTRACK = 594,
    EXISTS = 595,
    MISSING = 596,
    EXTHDR = 597,
    IPSEC = 598,
    REQID = 599,
    SPNUM = 600,
    IN = 601,
    OUT = 602
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
#define WILDCARD 288
#define CGROUPV2 289
#define TPROXY 290
#define OSF 291
#define SYNPROXY 292
#define MSS 293
#define WSCALE 294
#define TYPEOF 295
#define HOOK 296
#define DEVICE 297
#define DEVICES 298
#define TABLE 299
#define TABLES 300
#define CHAIN 301
#define CHAINS 302
#define RULE 303
#define RULES 304
#define SETS 305
#define SET 306
#define ELEMENT 307
#define MAP 308
#define MAPS 309
#define FLOWTABLE 310
#define HANDLE 311
#define RULESET 312
#define TRACE 313
#define INET 314
#define NETDEV 315
#define ADD 316
#define UPDATE 317
#define REPLACE 318
#define CREATE 319
#define INSERT 320
#define DELETE 321
#define GET 322
#define LIST 323
#define RESET 324
#define FLUSH 325
#define RENAME 326
#define DESCRIBE 327
#define IMPORT 328
#define EXPORT 329
#define MONITOR 330
#define ALL 331
#define ACCEPT 332
#define DROP 333
#define CONTINUE 334
#define JUMP 335
#define GOTO 336
#define RETURN 337
#define TO 338
#define CONSTANT 339
#define INTERVAL 340
#define DYNAMIC 341
#define AUTOMERGE 342
#define TIMEOUT 343
#define GC_INTERVAL 344
#define ELEMENTS 345
#define EXPIRES 346
#define POLICY 347
#define MEMORY 348
#define PERFORMANCE 349
#define SIZE 350
#define FLOW 351
#define OFFLOAD 352
#define METER 353
#define METERS 354
#define FLOWTABLES 355
#define NUM 356
#define STRING 357
#define QUOTED_STRING 358
#define ASTERISK_STRING 359
#define LL_HDR 360
#define NETWORK_HDR 361
#define TRANSPORT_HDR 362
#define BRIDGE 363
#define ETHER 364
#define SADDR 365
#define DADDR 366
#define TYPE 367
#define VLAN 368
#define ID 369
#define CFI 370
#define PCP 371
#define ARP 372
#define HTYPE 373
#define PTYPE 374
#define HLEN 375
#define PLEN 376
#define OPERATION 377
#define IP 378
#define HDRVERSION 379
#define HDRLENGTH 380
#define DSCP 381
#define ECN 382
#define LENGTH 383
#define FRAG_OFF 384
#define TTL 385
#define PROTOCOL 386
#define CHECKSUM 387
#define PTR 388
#define VALUE 389
#define LSRR 390
#define RR 391
#define SSRR 392
#define RA 393
#define ICMP 394
#define CODE 395
#define SEQUENCE 396
#define GATEWAY 397
#define MTU 398
#define IGMP 399
#define MRT 400
#define OPTIONS 401
#define IP6 402
#define PRIORITY 403
#define FLOWLABEL 404
#define NEXTHDR 405
#define HOPLIMIT 406
#define ICMP6 407
#define PPTR 408
#define MAXDELAY 409
#define AH 410
#define RESERVED 411
#define SPI 412
#define ESP 413
#define COMP 414
#define FLAGS 415
#define CPI 416
#define PORT 417
#define UDP 418
#define SPORT 419
#define DPORT 420
#define UDPLITE 421
#define CSUMCOV 422
#define TCP 423
#define ACKSEQ 424
#define DOFF 425
#define WINDOW 426
#define URGPTR 427
#define OPTION 428
#define ECHO 429
#define EOL 430
#define NOP 431
#define SACK 432
#define SACK0 433
#define SACK1 434
#define SACK2 435
#define SACK3 436
#define SACK_PERM 437
#define TIMESTAMP 438
#define KIND 439
#define COUNT 440
#define LEFT 441
#define RIGHT 442
#define TSVAL 443
#define TSECR 444
#define DCCP 445
#define SCTP 446
#define CHUNK 447
#define DATA 448
#define INIT 449
#define INIT_ACK 450
#define HEARTBEAT 451
#define HEARTBEAT_ACK 452
#define ABORT 453
#define SHUTDOWN 454
#define SHUTDOWN_ACK 455
#define ERROR 456
#define COOKIE_ECHO 457
#define COOKIE_ACK 458
#define ECNE 459
#define CWR 460
#define SHUTDOWN_COMPLETE 461
#define ASCONF_ACK 462
#define FORWARD_TSN 463
#define ASCONF 464
#define TSN 465
#define STREAM 466
#define SSN 467
#define PPID 468
#define INIT_TAG 469
#define A_RWND 470
#define NUM_OSTREAMS 471
#define NUM_ISTREAMS 472
#define INIT_TSN 473
#define CUM_TSN_ACK 474
#define NUM_GACK_BLOCKS 475
#define NUM_DUP_TSNS 476
#define LOWEST_TSN 477
#define SEQNO 478
#define NEW_CUM_TSN 479
#define VTAG 480
#define RT 481
#define RT0 482
#define RT2 483
#define RT4 484
#define SEG_LEFT 485
#define ADDR 486
#define LAST_ENT 487
#define TAG 488
#define SID 489
#define HBH 490
#define FRAG 491
#define RESERVED2 492
#define MORE_FRAGMENTS 493
#define DST 494
#define MH 495
#define META 496
#define MARK 497
#define IIF 498
#define IIFNAME 499
#define IIFTYPE 500
#define OIF 501
#define OIFNAME 502
#define OIFTYPE 503
#define SKUID 504
#define SKGID 505
#define NFTRACE 506
#define RTCLASSID 507
#define IBRIPORT 508
#define OBRIPORT 509
#define IBRIDGENAME 510
#define OBRIDGENAME 511
#define PKTTYPE 512
#define CPU 513
#define IIFGROUP 514
#define OIFGROUP 515
#define CGROUP 516
#define TIME 517
#define CLASSID 518
#define NEXTHOP 519
#define CT 520
#define L3PROTOCOL 521
#define PROTO_SRC 522
#define PROTO_DST 523
#define ZONE 524
#define DIRECTION 525
#define EVENT 526
#define EXPECTATION 527
#define EXPIRATION 528
#define HELPER 529
#define LABEL 530
#define STATE 531
#define STATUS 532
#define ORIGINAL 533
#define REPLY 534
#define COUNTER 535
#define NAME 536
#define PACKETS 537
#define BYTES 538
#define AVGPKT 539
#define COUNTERS 540
#define QUOTAS 541
#define LIMITS 542
#define SYNPROXYS 543
#define HELPERS 544
#define LOG 545
#define PREFIX 546
#define GROUP 547
#define SNAPLEN 548
#define QUEUE_THRESHOLD 549
#define LEVEL 550
#define LIMIT 551
#define RATE 552
#define BURST 553
#define OVER 554
#define UNTIL 555
#define QUOTA 556
#define USED 557
#define SECMARK 558
#define SECMARKS 559
#define SECOND 560
#define MINUTE 561
#define HOUR 562
#define DAY 563
#define WEEK 564
#define _REJECT 565
#define WITH 566
#define ICMPX 567
#define SNAT 568
#define DNAT 569
#define MASQUERADE 570
#define REDIRECT 571
#define RANDOM 572
#define FULLY_RANDOM 573
#define PERSISTENT 574
#define QUEUE 575
#define QUEUENUM 576
#define BYPASS 577
#define FANOUT 578
#define DUP 579
#define FWD 580
#define NUMGEN 581
#define INC 582
#define MOD 583
#define OFFSET 584
#define JHASH 585
#define SYMHASH 586
#define SEED 587
#define POSITION 588
#define INDEX 589
#define COMMENT 590
#define XML 591
#define JSON 592
#define VM 593
#define NOTRACK 594
#define EXISTS 595
#define MISSING 596
#define EXTHDR 597
#define IPSEC 598
#define REQID 599
#define SPNUM 600
#define IN 601
#define OUT 602

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 166 "parser_bison.y" /* yacc.c:1921  */

	uint64_t		val;
	uint32_t		val32;
	uint8_t			val8;
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
	struct ct		*ct;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	struct prio_spec	prio_spec;

#line 778 "parser_bison.h" /* yacc.c:1921  */
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
