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
    HOOKS = 297,
    DEVICE = 298,
    DEVICES = 299,
    TABLE = 300,
    TABLES = 301,
    CHAIN = 302,
    CHAINS = 303,
    RULE = 304,
    RULES = 305,
    SETS = 306,
    SET = 307,
    ELEMENT = 308,
    MAP = 309,
    MAPS = 310,
    FLOWTABLE = 311,
    HANDLE = 312,
    RULESET = 313,
    TRACE = 314,
    INET = 315,
    NETDEV = 316,
    ADD = 317,
    UPDATE = 318,
    REPLACE = 319,
    CREATE = 320,
    INSERT = 321,
    DELETE = 322,
    GET = 323,
    LIST = 324,
    RESET = 325,
    FLUSH = 326,
    RENAME = 327,
    DESCRIBE = 328,
    IMPORT = 329,
    EXPORT = 330,
    MONITOR = 331,
    ALL = 332,
    ACCEPT = 333,
    DROP = 334,
    CONTINUE = 335,
    JUMP = 336,
    GOTO = 337,
    RETURN = 338,
    TO = 339,
    CONSTANT = 340,
    INTERVAL = 341,
    DYNAMIC = 342,
    AUTOMERGE = 343,
    TIMEOUT = 344,
    GC_INTERVAL = 345,
    ELEMENTS = 346,
    EXPIRES = 347,
    POLICY = 348,
    MEMORY = 349,
    PERFORMANCE = 350,
    SIZE = 351,
    FLOW = 352,
    OFFLOAD = 353,
    METER = 354,
    METERS = 355,
    FLOWTABLES = 356,
    NUM = 357,
    STRING = 358,
    QUOTED_STRING = 359,
    ASTERISK_STRING = 360,
    LL_HDR = 361,
    NETWORK_HDR = 362,
    TRANSPORT_HDR = 363,
    BRIDGE = 364,
    ETHER = 365,
    SADDR = 366,
    DADDR = 367,
    TYPE = 368,
    VLAN = 369,
    ID = 370,
    CFI = 371,
    DEI = 372,
    PCP = 373,
    ARP = 374,
    HTYPE = 375,
    PTYPE = 376,
    HLEN = 377,
    PLEN = 378,
    OPERATION = 379,
    IP = 380,
    HDRVERSION = 381,
    HDRLENGTH = 382,
    DSCP = 383,
    ECN = 384,
    LENGTH = 385,
    FRAG_OFF = 386,
    TTL = 387,
    PROTOCOL = 388,
    CHECKSUM = 389,
    PTR = 390,
    VALUE = 391,
    LSRR = 392,
    RR = 393,
    SSRR = 394,
    RA = 395,
    ICMP = 396,
    CODE = 397,
    SEQUENCE = 398,
    GATEWAY = 399,
    MTU = 400,
    IGMP = 401,
    MRT = 402,
    OPTIONS = 403,
    IP6 = 404,
    PRIORITY = 405,
    FLOWLABEL = 406,
    NEXTHDR = 407,
    HOPLIMIT = 408,
    ICMP6 = 409,
    PPTR = 410,
    MAXDELAY = 411,
    AH = 412,
    RESERVED = 413,
    SPI = 414,
    ESP = 415,
    COMP = 416,
    FLAGS = 417,
    CPI = 418,
    PORT = 419,
    UDP = 420,
    SPORT = 421,
    DPORT = 422,
    UDPLITE = 423,
    CSUMCOV = 424,
    TCP = 425,
    ACKSEQ = 426,
    DOFF = 427,
    WINDOW = 428,
    URGPTR = 429,
    OPTION = 430,
    ECHO = 431,
    EOL = 432,
    NOP = 433,
    SACK = 434,
    SACK0 = 435,
    SACK1 = 436,
    SACK2 = 437,
    SACK3 = 438,
    SACK_PERM = 439,
    TIMESTAMP = 440,
    KIND = 441,
    COUNT = 442,
    LEFT = 443,
    RIGHT = 444,
    TSVAL = 445,
    TSECR = 446,
    DCCP = 447,
    SCTP = 448,
    CHUNK = 449,
    DATA = 450,
    INIT = 451,
    INIT_ACK = 452,
    HEARTBEAT = 453,
    HEARTBEAT_ACK = 454,
    ABORT = 455,
    SHUTDOWN = 456,
    SHUTDOWN_ACK = 457,
    ERROR = 458,
    COOKIE_ECHO = 459,
    COOKIE_ACK = 460,
    ECNE = 461,
    CWR = 462,
    SHUTDOWN_COMPLETE = 463,
    ASCONF_ACK = 464,
    FORWARD_TSN = 465,
    ASCONF = 466,
    TSN = 467,
    STREAM = 468,
    SSN = 469,
    PPID = 470,
    INIT_TAG = 471,
    A_RWND = 472,
    NUM_OSTREAMS = 473,
    NUM_ISTREAMS = 474,
    INIT_TSN = 475,
    CUM_TSN_ACK = 476,
    NUM_GACK_BLOCKS = 477,
    NUM_DUP_TSNS = 478,
    LOWEST_TSN = 479,
    SEQNO = 480,
    NEW_CUM_TSN = 481,
    VTAG = 482,
    RT = 483,
    RT0 = 484,
    RT2 = 485,
    RT4 = 486,
    SEG_LEFT = 487,
    ADDR = 488,
    LAST_ENT = 489,
    TAG = 490,
    SID = 491,
    HBH = 492,
    FRAG = 493,
    RESERVED2 = 494,
    MORE_FRAGMENTS = 495,
    DST = 496,
    MH = 497,
    META = 498,
    MARK = 499,
    IIF = 500,
    IIFNAME = 501,
    IIFTYPE = 502,
    OIF = 503,
    OIFNAME = 504,
    OIFTYPE = 505,
    SKUID = 506,
    SKGID = 507,
    NFTRACE = 508,
    RTCLASSID = 509,
    IBRIPORT = 510,
    OBRIPORT = 511,
    IBRIDGENAME = 512,
    OBRIDGENAME = 513,
    PKTTYPE = 514,
    CPU = 515,
    IIFGROUP = 516,
    OIFGROUP = 517,
    CGROUP = 518,
    TIME = 519,
    CLASSID = 520,
    NEXTHOP = 521,
    CT = 522,
    L3PROTOCOL = 523,
    PROTO_SRC = 524,
    PROTO_DST = 525,
    ZONE = 526,
    DIRECTION = 527,
    EVENT = 528,
    EXPECTATION = 529,
    EXPIRATION = 530,
    HELPER = 531,
    LABEL = 532,
    STATE = 533,
    STATUS = 534,
    ORIGINAL = 535,
    REPLY = 536,
    COUNTER = 537,
    NAME = 538,
    PACKETS = 539,
    BYTES = 540,
    AVGPKT = 541,
    COUNTERS = 542,
    QUOTAS = 543,
    LIMITS = 544,
    SYNPROXYS = 545,
    HELPERS = 546,
    LOG = 547,
    PREFIX = 548,
    GROUP = 549,
    SNAPLEN = 550,
    QUEUE_THRESHOLD = 551,
    LEVEL = 552,
    LIMIT = 553,
    RATE = 554,
    BURST = 555,
    OVER = 556,
    UNTIL = 557,
    QUOTA = 558,
    USED = 559,
    SECMARK = 560,
    SECMARKS = 561,
    SECOND = 562,
    MINUTE = 563,
    HOUR = 564,
    DAY = 565,
    WEEK = 566,
    _REJECT = 567,
    WITH = 568,
    ICMPX = 569,
    SNAT = 570,
    DNAT = 571,
    MASQUERADE = 572,
    REDIRECT = 573,
    RANDOM = 574,
    FULLY_RANDOM = 575,
    PERSISTENT = 576,
    QUEUE = 577,
    QUEUENUM = 578,
    BYPASS = 579,
    FANOUT = 580,
    DUP = 581,
    FWD = 582,
    NUMGEN = 583,
    INC = 584,
    MOD = 585,
    OFFSET = 586,
    JHASH = 587,
    SYMHASH = 588,
    SEED = 589,
    POSITION = 590,
    INDEX = 591,
    COMMENT = 592,
    XML = 593,
    JSON = 594,
    VM = 595,
    NOTRACK = 596,
    EXISTS = 597,
    MISSING = 598,
    EXTHDR = 599,
    IPSEC = 600,
    REQID = 601,
    SPNUM = 602,
    IN = 603,
    OUT = 604
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
#define HOOKS 297
#define DEVICE 298
#define DEVICES 299
#define TABLE 300
#define TABLES 301
#define CHAIN 302
#define CHAINS 303
#define RULE 304
#define RULES 305
#define SETS 306
#define SET 307
#define ELEMENT 308
#define MAP 309
#define MAPS 310
#define FLOWTABLE 311
#define HANDLE 312
#define RULESET 313
#define TRACE 314
#define INET 315
#define NETDEV 316
#define ADD 317
#define UPDATE 318
#define REPLACE 319
#define CREATE 320
#define INSERT 321
#define DELETE 322
#define GET 323
#define LIST 324
#define RESET 325
#define FLUSH 326
#define RENAME 327
#define DESCRIBE 328
#define IMPORT 329
#define EXPORT 330
#define MONITOR 331
#define ALL 332
#define ACCEPT 333
#define DROP 334
#define CONTINUE 335
#define JUMP 336
#define GOTO 337
#define RETURN 338
#define TO 339
#define CONSTANT 340
#define INTERVAL 341
#define DYNAMIC 342
#define AUTOMERGE 343
#define TIMEOUT 344
#define GC_INTERVAL 345
#define ELEMENTS 346
#define EXPIRES 347
#define POLICY 348
#define MEMORY 349
#define PERFORMANCE 350
#define SIZE 351
#define FLOW 352
#define OFFLOAD 353
#define METER 354
#define METERS 355
#define FLOWTABLES 356
#define NUM 357
#define STRING 358
#define QUOTED_STRING 359
#define ASTERISK_STRING 360
#define LL_HDR 361
#define NETWORK_HDR 362
#define TRANSPORT_HDR 363
#define BRIDGE 364
#define ETHER 365
#define SADDR 366
#define DADDR 367
#define TYPE 368
#define VLAN 369
#define ID 370
#define CFI 371
#define DEI 372
#define PCP 373
#define ARP 374
#define HTYPE 375
#define PTYPE 376
#define HLEN 377
#define PLEN 378
#define OPERATION 379
#define IP 380
#define HDRVERSION 381
#define HDRLENGTH 382
#define DSCP 383
#define ECN 384
#define LENGTH 385
#define FRAG_OFF 386
#define TTL 387
#define PROTOCOL 388
#define CHECKSUM 389
#define PTR 390
#define VALUE 391
#define LSRR 392
#define RR 393
#define SSRR 394
#define RA 395
#define ICMP 396
#define CODE 397
#define SEQUENCE 398
#define GATEWAY 399
#define MTU 400
#define IGMP 401
#define MRT 402
#define OPTIONS 403
#define IP6 404
#define PRIORITY 405
#define FLOWLABEL 406
#define NEXTHDR 407
#define HOPLIMIT 408
#define ICMP6 409
#define PPTR 410
#define MAXDELAY 411
#define AH 412
#define RESERVED 413
#define SPI 414
#define ESP 415
#define COMP 416
#define FLAGS 417
#define CPI 418
#define PORT 419
#define UDP 420
#define SPORT 421
#define DPORT 422
#define UDPLITE 423
#define CSUMCOV 424
#define TCP 425
#define ACKSEQ 426
#define DOFF 427
#define WINDOW 428
#define URGPTR 429
#define OPTION 430
#define ECHO 431
#define EOL 432
#define NOP 433
#define SACK 434
#define SACK0 435
#define SACK1 436
#define SACK2 437
#define SACK3 438
#define SACK_PERM 439
#define TIMESTAMP 440
#define KIND 441
#define COUNT 442
#define LEFT 443
#define RIGHT 444
#define TSVAL 445
#define TSECR 446
#define DCCP 447
#define SCTP 448
#define CHUNK 449
#define DATA 450
#define INIT 451
#define INIT_ACK 452
#define HEARTBEAT 453
#define HEARTBEAT_ACK 454
#define ABORT 455
#define SHUTDOWN 456
#define SHUTDOWN_ACK 457
#define ERROR 458
#define COOKIE_ECHO 459
#define COOKIE_ACK 460
#define ECNE 461
#define CWR 462
#define SHUTDOWN_COMPLETE 463
#define ASCONF_ACK 464
#define FORWARD_TSN 465
#define ASCONF 466
#define TSN 467
#define STREAM 468
#define SSN 469
#define PPID 470
#define INIT_TAG 471
#define A_RWND 472
#define NUM_OSTREAMS 473
#define NUM_ISTREAMS 474
#define INIT_TSN 475
#define CUM_TSN_ACK 476
#define NUM_GACK_BLOCKS 477
#define NUM_DUP_TSNS 478
#define LOWEST_TSN 479
#define SEQNO 480
#define NEW_CUM_TSN 481
#define VTAG 482
#define RT 483
#define RT0 484
#define RT2 485
#define RT4 486
#define SEG_LEFT 487
#define ADDR 488
#define LAST_ENT 489
#define TAG 490
#define SID 491
#define HBH 492
#define FRAG 493
#define RESERVED2 494
#define MORE_FRAGMENTS 495
#define DST 496
#define MH 497
#define META 498
#define MARK 499
#define IIF 500
#define IIFNAME 501
#define IIFTYPE 502
#define OIF 503
#define OIFNAME 504
#define OIFTYPE 505
#define SKUID 506
#define SKGID 507
#define NFTRACE 508
#define RTCLASSID 509
#define IBRIPORT 510
#define OBRIPORT 511
#define IBRIDGENAME 512
#define OBRIDGENAME 513
#define PKTTYPE 514
#define CPU 515
#define IIFGROUP 516
#define OIFGROUP 517
#define CGROUP 518
#define TIME 519
#define CLASSID 520
#define NEXTHOP 521
#define CT 522
#define L3PROTOCOL 523
#define PROTO_SRC 524
#define PROTO_DST 525
#define ZONE 526
#define DIRECTION 527
#define EVENT 528
#define EXPECTATION 529
#define EXPIRATION 530
#define HELPER 531
#define LABEL 532
#define STATE 533
#define STATUS 534
#define ORIGINAL 535
#define REPLY 536
#define COUNTER 537
#define NAME 538
#define PACKETS 539
#define BYTES 540
#define AVGPKT 541
#define COUNTERS 542
#define QUOTAS 543
#define LIMITS 544
#define SYNPROXYS 545
#define HELPERS 546
#define LOG 547
#define PREFIX 548
#define GROUP 549
#define SNAPLEN 550
#define QUEUE_THRESHOLD 551
#define LEVEL 552
#define LIMIT 553
#define RATE 554
#define BURST 555
#define OVER 556
#define UNTIL 557
#define QUOTA 558
#define USED 559
#define SECMARK 560
#define SECMARKS 561
#define SECOND 562
#define MINUTE 563
#define HOUR 564
#define DAY 565
#define WEEK 566
#define _REJECT 567
#define WITH 568
#define ICMPX 569
#define SNAT 570
#define DNAT 571
#define MASQUERADE 572
#define REDIRECT 573
#define RANDOM 574
#define FULLY_RANDOM 575
#define PERSISTENT 576
#define QUEUE 577
#define QUEUENUM 578
#define BYPASS 579
#define FANOUT 580
#define DUP 581
#define FWD 582
#define NUMGEN 583
#define INC 584
#define MOD 585
#define OFFSET 586
#define JHASH 587
#define SYMHASH 588
#define SEED 589
#define POSITION 590
#define INDEX 591
#define COMMENT 592
#define XML 593
#define JSON 594
#define VM 595
#define NOTRACK 596
#define EXISTS 597
#define MISSING 598
#define EXTHDR 599
#define IPSEC 600
#define REQID 601
#define SPNUM 602
#define IN 603
#define OUT 604

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 167 "parser_bison.y" /* yacc.c:1921  */

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

#line 782 "parser_bison.h" /* yacc.c:1921  */
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
