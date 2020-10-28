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
    TPROXY = 289,
    OSF = 290,
    SYNPROXY = 291,
    MSS = 292,
    WSCALE = 293,
    SACKPERM = 294,
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
    MAXSEG = 431,
    NOOP = 432,
    SACK = 433,
    SACK0 = 434,
    SACK1 = 435,
    SACK2 = 436,
    SACK3 = 437,
    SACK_PERMITTED = 438,
    TIMESTAMP = 439,
    KIND = 440,
    COUNT = 441,
    LEFT = 442,
    RIGHT = 443,
    TSVAL = 444,
    TSECR = 445,
    DCCP = 446,
    SCTP = 447,
    VTAG = 448,
    RT = 449,
    RT0 = 450,
    RT2 = 451,
    RT4 = 452,
    SEG_LEFT = 453,
    ADDR = 454,
    LAST_ENT = 455,
    TAG = 456,
    SID = 457,
    HBH = 458,
    FRAG = 459,
    RESERVED2 = 460,
    MORE_FRAGMENTS = 461,
    DST = 462,
    MH = 463,
    META = 464,
    MARK = 465,
    IIF = 466,
    IIFNAME = 467,
    IIFTYPE = 468,
    OIF = 469,
    OIFNAME = 470,
    OIFTYPE = 471,
    SKUID = 472,
    SKGID = 473,
    NFTRACE = 474,
    RTCLASSID = 475,
    IBRIPORT = 476,
    OBRIPORT = 477,
    IBRIDGENAME = 478,
    OBRIDGENAME = 479,
    PKTTYPE = 480,
    CPU = 481,
    IIFGROUP = 482,
    OIFGROUP = 483,
    CGROUP = 484,
    TIME = 485,
    CLASSID = 486,
    NEXTHOP = 487,
    CT = 488,
    L3PROTOCOL = 489,
    PROTO_SRC = 490,
    PROTO_DST = 491,
    ZONE = 492,
    DIRECTION = 493,
    EVENT = 494,
    EXPECTATION = 495,
    EXPIRATION = 496,
    HELPER = 497,
    LABEL = 498,
    STATE = 499,
    STATUS = 500,
    ORIGINAL = 501,
    REPLY = 502,
    COUNTER = 503,
    NAME = 504,
    PACKETS = 505,
    BYTES = 506,
    AVGPKT = 507,
    COUNTERS = 508,
    QUOTAS = 509,
    LIMITS = 510,
    SYNPROXYS = 511,
    HELPERS = 512,
    LOG = 513,
    PREFIX = 514,
    GROUP = 515,
    SNAPLEN = 516,
    QUEUE_THRESHOLD = 517,
    LEVEL = 518,
    LIMIT = 519,
    RATE = 520,
    BURST = 521,
    OVER = 522,
    UNTIL = 523,
    QUOTA = 524,
    USED = 525,
    SECMARK = 526,
    SECMARKS = 527,
    NANOSECOND = 528,
    MICROSECOND = 529,
    MILLISECOND = 530,
    SECOND = 531,
    MINUTE = 532,
    HOUR = 533,
    DAY = 534,
    WEEK = 535,
    _REJECT = 536,
    WITH = 537,
    ICMPX = 538,
    SNAT = 539,
    DNAT = 540,
    MASQUERADE = 541,
    REDIRECT = 542,
    RANDOM = 543,
    FULLY_RANDOM = 544,
    PERSISTENT = 545,
    QUEUE = 546,
    QUEUENUM = 547,
    BYPASS = 548,
    FANOUT = 549,
    DUP = 550,
    FWD = 551,
    NUMGEN = 552,
    INC = 553,
    MOD = 554,
    OFFSET = 555,
    JHASH = 556,
    SYMHASH = 557,
    SEED = 558,
    POSITION = 559,
    INDEX = 560,
    COMMENT = 561,
    XML = 562,
    JSON = 563,
    VM = 564,
    NOTRACK = 565,
    EXISTS = 566,
    MISSING = 567,
    EXTHDR = 568,
    IPSEC = 569,
    MODE = 570,
    REQID = 571,
    SPNUM = 572,
    TRANSPORT = 573,
    TUNNEL = 574,
    IN = 575,
    OUT = 576
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
#define TPROXY 289
#define OSF 290
#define SYNPROXY 291
#define MSS 292
#define WSCALE 293
#define SACKPERM 294
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
#define MAXSEG 431
#define NOOP 432
#define SACK 433
#define SACK0 434
#define SACK1 435
#define SACK2 436
#define SACK3 437
#define SACK_PERMITTED 438
#define TIMESTAMP 439
#define KIND 440
#define COUNT 441
#define LEFT 442
#define RIGHT 443
#define TSVAL 444
#define TSECR 445
#define DCCP 446
#define SCTP 447
#define VTAG 448
#define RT 449
#define RT0 450
#define RT2 451
#define RT4 452
#define SEG_LEFT 453
#define ADDR 454
#define LAST_ENT 455
#define TAG 456
#define SID 457
#define HBH 458
#define FRAG 459
#define RESERVED2 460
#define MORE_FRAGMENTS 461
#define DST 462
#define MH 463
#define META 464
#define MARK 465
#define IIF 466
#define IIFNAME 467
#define IIFTYPE 468
#define OIF 469
#define OIFNAME 470
#define OIFTYPE 471
#define SKUID 472
#define SKGID 473
#define NFTRACE 474
#define RTCLASSID 475
#define IBRIPORT 476
#define OBRIPORT 477
#define IBRIDGENAME 478
#define OBRIDGENAME 479
#define PKTTYPE 480
#define CPU 481
#define IIFGROUP 482
#define OIFGROUP 483
#define CGROUP 484
#define TIME 485
#define CLASSID 486
#define NEXTHOP 487
#define CT 488
#define L3PROTOCOL 489
#define PROTO_SRC 490
#define PROTO_DST 491
#define ZONE 492
#define DIRECTION 493
#define EVENT 494
#define EXPECTATION 495
#define EXPIRATION 496
#define HELPER 497
#define LABEL 498
#define STATE 499
#define STATUS 500
#define ORIGINAL 501
#define REPLY 502
#define COUNTER 503
#define NAME 504
#define PACKETS 505
#define BYTES 506
#define AVGPKT 507
#define COUNTERS 508
#define QUOTAS 509
#define LIMITS 510
#define SYNPROXYS 511
#define HELPERS 512
#define LOG 513
#define PREFIX 514
#define GROUP 515
#define SNAPLEN 516
#define QUEUE_THRESHOLD 517
#define LEVEL 518
#define LIMIT 519
#define RATE 520
#define BURST 521
#define OVER 522
#define UNTIL 523
#define QUOTA 524
#define USED 525
#define SECMARK 526
#define SECMARKS 527
#define NANOSECOND 528
#define MICROSECOND 529
#define MILLISECOND 530
#define SECOND 531
#define MINUTE 532
#define HOUR 533
#define DAY 534
#define WEEK 535
#define _REJECT 536
#define WITH 537
#define ICMPX 538
#define SNAT 539
#define DNAT 540
#define MASQUERADE 541
#define REDIRECT 542
#define RANDOM 543
#define FULLY_RANDOM 544
#define PERSISTENT 545
#define QUEUE 546
#define QUEUENUM 547
#define BYPASS 548
#define FANOUT 549
#define DUP 550
#define FWD 551
#define NUMGEN 552
#define INC 553
#define MOD 554
#define OFFSET 555
#define JHASH 556
#define SYMHASH 557
#define SEED 558
#define POSITION 559
#define INDEX 560
#define COMMENT 561
#define XML 562
#define JSON 563
#define VM 564
#define NOTRACK 565
#define EXISTS 566
#define MISSING 567
#define EXTHDR 568
#define IPSEC 569
#define MODE 570
#define REQID 571
#define SPNUM 572
#define TRANSPORT 573
#define TUNNEL 574
#define IN 575
#define OUT 576

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 165 "parser_bison.y" /* yacc.c:1921  */

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

#line 727 "parser_bison.h" /* yacc.c:1921  */
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
