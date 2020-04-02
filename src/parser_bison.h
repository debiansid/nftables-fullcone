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
    TYPEOF = 294,
    HOOK = 295,
    DEVICE = 296,
    DEVICES = 297,
    TABLE = 298,
    TABLES = 299,
    CHAIN = 300,
    CHAINS = 301,
    RULE = 302,
    RULES = 303,
    SETS = 304,
    SET = 305,
    ELEMENT = 306,
    MAP = 307,
    MAPS = 308,
    FLOWTABLE = 309,
    HANDLE = 310,
    RULESET = 311,
    TRACE = 312,
    INET = 313,
    NETDEV = 314,
    ADD = 315,
    UPDATE = 316,
    REPLACE = 317,
    CREATE = 318,
    INSERT = 319,
    DELETE = 320,
    GET = 321,
    LIST = 322,
    RESET = 323,
    FLUSH = 324,
    RENAME = 325,
    DESCRIBE = 326,
    IMPORT = 327,
    EXPORT = 328,
    MONITOR = 329,
    ALL = 330,
    ACCEPT = 331,
    DROP = 332,
    CONTINUE = 333,
    JUMP = 334,
    GOTO = 335,
    RETURN = 336,
    TO = 337,
    CONSTANT = 338,
    INTERVAL = 339,
    DYNAMIC = 340,
    AUTOMERGE = 341,
    TIMEOUT = 342,
    GC_INTERVAL = 343,
    ELEMENTS = 344,
    EXPIRES = 345,
    POLICY = 346,
    MEMORY = 347,
    PERFORMANCE = 348,
    SIZE = 349,
    FLOW = 350,
    OFFLOAD = 351,
    METER = 352,
    METERS = 353,
    FLOWTABLES = 354,
    NUM = 355,
    STRING = 356,
    QUOTED_STRING = 357,
    ASTERISK_STRING = 358,
    LL_HDR = 359,
    NETWORK_HDR = 360,
    TRANSPORT_HDR = 361,
    BRIDGE = 362,
    ETHER = 363,
    SADDR = 364,
    DADDR = 365,
    TYPE = 366,
    VLAN = 367,
    ID = 368,
    CFI = 369,
    PCP = 370,
    ARP = 371,
    HTYPE = 372,
    PTYPE = 373,
    HLEN = 374,
    PLEN = 375,
    OPERATION = 376,
    IP = 377,
    HDRVERSION = 378,
    HDRLENGTH = 379,
    DSCP = 380,
    ECN = 381,
    LENGTH = 382,
    FRAG_OFF = 383,
    TTL = 384,
    PROTOCOL = 385,
    CHECKSUM = 386,
    PTR = 387,
    VALUE = 388,
    LSRR = 389,
    RR = 390,
    SSRR = 391,
    RA = 392,
    ICMP = 393,
    CODE = 394,
    SEQUENCE = 395,
    GATEWAY = 396,
    MTU = 397,
    IGMP = 398,
    MRT = 399,
    OPTIONS = 400,
    IP6 = 401,
    PRIORITY = 402,
    FLOWLABEL = 403,
    NEXTHDR = 404,
    HOPLIMIT = 405,
    ICMP6 = 406,
    PPTR = 407,
    MAXDELAY = 408,
    AH = 409,
    RESERVED = 410,
    SPI = 411,
    ESP = 412,
    COMP = 413,
    FLAGS = 414,
    CPI = 415,
    PORT = 416,
    UDP = 417,
    SPORT = 418,
    DPORT = 419,
    UDPLITE = 420,
    CSUMCOV = 421,
    TCP = 422,
    ACKSEQ = 423,
    DOFF = 424,
    WINDOW = 425,
    URGPTR = 426,
    OPTION = 427,
    ECHO = 428,
    EOL = 429,
    MAXSEG = 430,
    NOOP = 431,
    SACK = 432,
    SACK0 = 433,
    SACK1 = 434,
    SACK2 = 435,
    SACK3 = 436,
    SACK_PERMITTED = 437,
    TIMESTAMP = 438,
    KIND = 439,
    COUNT = 440,
    LEFT = 441,
    RIGHT = 442,
    TSVAL = 443,
    TSECR = 444,
    DCCP = 445,
    SCTP = 446,
    VTAG = 447,
    RT = 448,
    RT0 = 449,
    RT2 = 450,
    RT4 = 451,
    SEG_LEFT = 452,
    ADDR = 453,
    LAST_ENT = 454,
    TAG = 455,
    SID = 456,
    HBH = 457,
    FRAG = 458,
    RESERVED2 = 459,
    MORE_FRAGMENTS = 460,
    DST = 461,
    MH = 462,
    META = 463,
    MARK = 464,
    IIF = 465,
    IIFNAME = 466,
    IIFTYPE = 467,
    OIF = 468,
    OIFNAME = 469,
    OIFTYPE = 470,
    SKUID = 471,
    SKGID = 472,
    NFTRACE = 473,
    RTCLASSID = 474,
    IBRIPORT = 475,
    OBRIPORT = 476,
    IBRIDGENAME = 477,
    OBRIDGENAME = 478,
    PKTTYPE = 479,
    CPU = 480,
    IIFGROUP = 481,
    OIFGROUP = 482,
    CGROUP = 483,
    TIME = 484,
    CLASSID = 485,
    NEXTHOP = 486,
    CT = 487,
    L3PROTOCOL = 488,
    PROTO_SRC = 489,
    PROTO_DST = 490,
    ZONE = 491,
    DIRECTION = 492,
    EVENT = 493,
    EXPECTATION = 494,
    EXPIRATION = 495,
    HELPER = 496,
    LABEL = 497,
    STATE = 498,
    STATUS = 499,
    ORIGINAL = 500,
    REPLY = 501,
    COUNTER = 502,
    NAME = 503,
    PACKETS = 504,
    BYTES = 505,
    AVGPKT = 506,
    COUNTERS = 507,
    QUOTAS = 508,
    LIMITS = 509,
    SYNPROXYS = 510,
    HELPERS = 511,
    LOG = 512,
    PREFIX = 513,
    GROUP = 514,
    SNAPLEN = 515,
    QUEUE_THRESHOLD = 516,
    LEVEL = 517,
    LIMIT = 518,
    RATE = 519,
    BURST = 520,
    OVER = 521,
    UNTIL = 522,
    QUOTA = 523,
    USED = 524,
    SECMARK = 525,
    SECMARKS = 526,
    NANOSECOND = 527,
    MICROSECOND = 528,
    MILLISECOND = 529,
    SECOND = 530,
    MINUTE = 531,
    HOUR = 532,
    DAY = 533,
    WEEK = 534,
    _REJECT = 535,
    WITH = 536,
    ICMPX = 537,
    SNAT = 538,
    DNAT = 539,
    MASQUERADE = 540,
    REDIRECT = 541,
    RANDOM = 542,
    FULLY_RANDOM = 543,
    PERSISTENT = 544,
    QUEUE = 545,
    QUEUENUM = 546,
    BYPASS = 547,
    FANOUT = 548,
    DUP = 549,
    FWD = 550,
    NUMGEN = 551,
    INC = 552,
    MOD = 553,
    OFFSET = 554,
    JHASH = 555,
    SYMHASH = 556,
    SEED = 557,
    POSITION = 558,
    INDEX = 559,
    COMMENT = 560,
    XML = 561,
    JSON = 562,
    VM = 563,
    NOTRACK = 564,
    EXISTS = 565,
    MISSING = 566,
    EXTHDR = 567,
    IPSEC = 568,
    MODE = 569,
    REQID = 570,
    SPNUM = 571,
    TRANSPORT = 572,
    TUNNEL = 573,
    IN = 574,
    OUT = 575
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
#define TYPEOF 294
#define HOOK 295
#define DEVICE 296
#define DEVICES 297
#define TABLE 298
#define TABLES 299
#define CHAIN 300
#define CHAINS 301
#define RULE 302
#define RULES 303
#define SETS 304
#define SET 305
#define ELEMENT 306
#define MAP 307
#define MAPS 308
#define FLOWTABLE 309
#define HANDLE 310
#define RULESET 311
#define TRACE 312
#define INET 313
#define NETDEV 314
#define ADD 315
#define UPDATE 316
#define REPLACE 317
#define CREATE 318
#define INSERT 319
#define DELETE 320
#define GET 321
#define LIST 322
#define RESET 323
#define FLUSH 324
#define RENAME 325
#define DESCRIBE 326
#define IMPORT 327
#define EXPORT 328
#define MONITOR 329
#define ALL 330
#define ACCEPT 331
#define DROP 332
#define CONTINUE 333
#define JUMP 334
#define GOTO 335
#define RETURN 336
#define TO 337
#define CONSTANT 338
#define INTERVAL 339
#define DYNAMIC 340
#define AUTOMERGE 341
#define TIMEOUT 342
#define GC_INTERVAL 343
#define ELEMENTS 344
#define EXPIRES 345
#define POLICY 346
#define MEMORY 347
#define PERFORMANCE 348
#define SIZE 349
#define FLOW 350
#define OFFLOAD 351
#define METER 352
#define METERS 353
#define FLOWTABLES 354
#define NUM 355
#define STRING 356
#define QUOTED_STRING 357
#define ASTERISK_STRING 358
#define LL_HDR 359
#define NETWORK_HDR 360
#define TRANSPORT_HDR 361
#define BRIDGE 362
#define ETHER 363
#define SADDR 364
#define DADDR 365
#define TYPE 366
#define VLAN 367
#define ID 368
#define CFI 369
#define PCP 370
#define ARP 371
#define HTYPE 372
#define PTYPE 373
#define HLEN 374
#define PLEN 375
#define OPERATION 376
#define IP 377
#define HDRVERSION 378
#define HDRLENGTH 379
#define DSCP 380
#define ECN 381
#define LENGTH 382
#define FRAG_OFF 383
#define TTL 384
#define PROTOCOL 385
#define CHECKSUM 386
#define PTR 387
#define VALUE 388
#define LSRR 389
#define RR 390
#define SSRR 391
#define RA 392
#define ICMP 393
#define CODE 394
#define SEQUENCE 395
#define GATEWAY 396
#define MTU 397
#define IGMP 398
#define MRT 399
#define OPTIONS 400
#define IP6 401
#define PRIORITY 402
#define FLOWLABEL 403
#define NEXTHDR 404
#define HOPLIMIT 405
#define ICMP6 406
#define PPTR 407
#define MAXDELAY 408
#define AH 409
#define RESERVED 410
#define SPI 411
#define ESP 412
#define COMP 413
#define FLAGS 414
#define CPI 415
#define PORT 416
#define UDP 417
#define SPORT 418
#define DPORT 419
#define UDPLITE 420
#define CSUMCOV 421
#define TCP 422
#define ACKSEQ 423
#define DOFF 424
#define WINDOW 425
#define URGPTR 426
#define OPTION 427
#define ECHO 428
#define EOL 429
#define MAXSEG 430
#define NOOP 431
#define SACK 432
#define SACK0 433
#define SACK1 434
#define SACK2 435
#define SACK3 436
#define SACK_PERMITTED 437
#define TIMESTAMP 438
#define KIND 439
#define COUNT 440
#define LEFT 441
#define RIGHT 442
#define TSVAL 443
#define TSECR 444
#define DCCP 445
#define SCTP 446
#define VTAG 447
#define RT 448
#define RT0 449
#define RT2 450
#define RT4 451
#define SEG_LEFT 452
#define ADDR 453
#define LAST_ENT 454
#define TAG 455
#define SID 456
#define HBH 457
#define FRAG 458
#define RESERVED2 459
#define MORE_FRAGMENTS 460
#define DST 461
#define MH 462
#define META 463
#define MARK 464
#define IIF 465
#define IIFNAME 466
#define IIFTYPE 467
#define OIF 468
#define OIFNAME 469
#define OIFTYPE 470
#define SKUID 471
#define SKGID 472
#define NFTRACE 473
#define RTCLASSID 474
#define IBRIPORT 475
#define OBRIPORT 476
#define IBRIDGENAME 477
#define OBRIDGENAME 478
#define PKTTYPE 479
#define CPU 480
#define IIFGROUP 481
#define OIFGROUP 482
#define CGROUP 483
#define TIME 484
#define CLASSID 485
#define NEXTHOP 486
#define CT 487
#define L3PROTOCOL 488
#define PROTO_SRC 489
#define PROTO_DST 490
#define ZONE 491
#define DIRECTION 492
#define EVENT 493
#define EXPECTATION 494
#define EXPIRATION 495
#define HELPER 496
#define LABEL 497
#define STATE 498
#define STATUS 499
#define ORIGINAL 500
#define REPLY 501
#define COUNTER 502
#define NAME 503
#define PACKETS 504
#define BYTES 505
#define AVGPKT 506
#define COUNTERS 507
#define QUOTAS 508
#define LIMITS 509
#define SYNPROXYS 510
#define HELPERS 511
#define LOG 512
#define PREFIX 513
#define GROUP 514
#define SNAPLEN 515
#define QUEUE_THRESHOLD 516
#define LEVEL 517
#define LIMIT 518
#define RATE 519
#define BURST 520
#define OVER 521
#define UNTIL 522
#define QUOTA 523
#define USED 524
#define SECMARK 525
#define SECMARKS 526
#define NANOSECOND 527
#define MICROSECOND 528
#define MILLISECOND 529
#define SECOND 530
#define MINUTE 531
#define HOUR 532
#define DAY 533
#define WEEK 534
#define _REJECT 535
#define WITH 536
#define ICMPX 537
#define SNAT 538
#define DNAT 539
#define MASQUERADE 540
#define REDIRECT 541
#define RANDOM 542
#define FULLY_RANDOM 543
#define PERSISTENT 544
#define QUEUE 545
#define QUEUENUM 546
#define BYPASS 547
#define FANOUT 548
#define DUP 549
#define FWD 550
#define NUMGEN 551
#define INC 552
#define MOD 553
#define OFFSET 554
#define JHASH 555
#define SYMHASH 556
#define SEED 557
#define POSITION 558
#define INDEX 559
#define COMMENT 560
#define XML 561
#define JSON 562
#define VM 563
#define NOTRACK 564
#define EXISTS 565
#define MISSING 566
#define EXTHDR 567
#define IPSEC 568
#define MODE 569
#define REQID 570
#define SPNUM 571
#define TRANSPORT 572
#define TUNNEL 573
#define IN 574
#define OUT 575

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 154 "parser_bison.y" /* yacc.c:1921  */

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
	const struct exthdr_desc *exthdr_desc;

#line 725 "parser_bison.h" /* yacc.c:1921  */
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
