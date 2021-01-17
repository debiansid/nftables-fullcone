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
    NOP = 430,
    SACK = 431,
    SACK0 = 432,
    SACK1 = 433,
    SACK2 = 434,
    SACK3 = 435,
    SACK_PERM = 436,
    TIMESTAMP = 437,
    KIND = 438,
    COUNT = 439,
    LEFT = 440,
    RIGHT = 441,
    TSVAL = 442,
    TSECR = 443,
    DCCP = 444,
    SCTP = 445,
    VTAG = 446,
    RT = 447,
    RT0 = 448,
    RT2 = 449,
    RT4 = 450,
    SEG_LEFT = 451,
    ADDR = 452,
    LAST_ENT = 453,
    TAG = 454,
    SID = 455,
    HBH = 456,
    FRAG = 457,
    RESERVED2 = 458,
    MORE_FRAGMENTS = 459,
    DST = 460,
    MH = 461,
    META = 462,
    MARK = 463,
    IIF = 464,
    IIFNAME = 465,
    IIFTYPE = 466,
    OIF = 467,
    OIFNAME = 468,
    OIFTYPE = 469,
    SKUID = 470,
    SKGID = 471,
    NFTRACE = 472,
    RTCLASSID = 473,
    IBRIPORT = 474,
    OBRIPORT = 475,
    IBRIDGENAME = 476,
    OBRIDGENAME = 477,
    PKTTYPE = 478,
    CPU = 479,
    IIFGROUP = 480,
    OIFGROUP = 481,
    CGROUP = 482,
    TIME = 483,
    CLASSID = 484,
    NEXTHOP = 485,
    CT = 486,
    L3PROTOCOL = 487,
    PROTO_SRC = 488,
    PROTO_DST = 489,
    ZONE = 490,
    DIRECTION = 491,
    EVENT = 492,
    EXPECTATION = 493,
    EXPIRATION = 494,
    HELPER = 495,
    LABEL = 496,
    STATE = 497,
    STATUS = 498,
    ORIGINAL = 499,
    REPLY = 500,
    COUNTER = 501,
    NAME = 502,
    PACKETS = 503,
    BYTES = 504,
    AVGPKT = 505,
    COUNTERS = 506,
    QUOTAS = 507,
    LIMITS = 508,
    SYNPROXYS = 509,
    HELPERS = 510,
    LOG = 511,
    PREFIX = 512,
    GROUP = 513,
    SNAPLEN = 514,
    QUEUE_THRESHOLD = 515,
    LEVEL = 516,
    LIMIT = 517,
    RATE = 518,
    BURST = 519,
    OVER = 520,
    UNTIL = 521,
    QUOTA = 522,
    USED = 523,
    SECMARK = 524,
    SECMARKS = 525,
    NANOSECOND = 526,
    MICROSECOND = 527,
    MILLISECOND = 528,
    SECOND = 529,
    MINUTE = 530,
    HOUR = 531,
    DAY = 532,
    WEEK = 533,
    _REJECT = 534,
    WITH = 535,
    ICMPX = 536,
    SNAT = 537,
    DNAT = 538,
    MASQUERADE = 539,
    REDIRECT = 540,
    RANDOM = 541,
    FULLY_RANDOM = 542,
    PERSISTENT = 543,
    QUEUE = 544,
    QUEUENUM = 545,
    BYPASS = 546,
    FANOUT = 547,
    DUP = 548,
    FWD = 549,
    NUMGEN = 550,
    INC = 551,
    MOD = 552,
    OFFSET = 553,
    JHASH = 554,
    SYMHASH = 555,
    SEED = 556,
    POSITION = 557,
    INDEX = 558,
    COMMENT = 559,
    XML = 560,
    JSON = 561,
    VM = 562,
    NOTRACK = 563,
    EXISTS = 564,
    MISSING = 565,
    EXTHDR = 566,
    IPSEC = 567,
    MODE = 568,
    REQID = 569,
    SPNUM = 570,
    TRANSPORT = 571,
    TUNNEL = 572,
    IN = 573,
    OUT = 574
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
#define NOP 430
#define SACK 431
#define SACK0 432
#define SACK1 433
#define SACK2 434
#define SACK3 435
#define SACK_PERM 436
#define TIMESTAMP 437
#define KIND 438
#define COUNT 439
#define LEFT 440
#define RIGHT 441
#define TSVAL 442
#define TSECR 443
#define DCCP 444
#define SCTP 445
#define VTAG 446
#define RT 447
#define RT0 448
#define RT2 449
#define RT4 450
#define SEG_LEFT 451
#define ADDR 452
#define LAST_ENT 453
#define TAG 454
#define SID 455
#define HBH 456
#define FRAG 457
#define RESERVED2 458
#define MORE_FRAGMENTS 459
#define DST 460
#define MH 461
#define META 462
#define MARK 463
#define IIF 464
#define IIFNAME 465
#define IIFTYPE 466
#define OIF 467
#define OIFNAME 468
#define OIFTYPE 469
#define SKUID 470
#define SKGID 471
#define NFTRACE 472
#define RTCLASSID 473
#define IBRIPORT 474
#define OBRIPORT 475
#define IBRIDGENAME 476
#define OBRIDGENAME 477
#define PKTTYPE 478
#define CPU 479
#define IIFGROUP 480
#define OIFGROUP 481
#define CGROUP 482
#define TIME 483
#define CLASSID 484
#define NEXTHOP 485
#define CT 486
#define L3PROTOCOL 487
#define PROTO_SRC 488
#define PROTO_DST 489
#define ZONE 490
#define DIRECTION 491
#define EVENT 492
#define EXPECTATION 493
#define EXPIRATION 494
#define HELPER 495
#define LABEL 496
#define STATE 497
#define STATUS 498
#define ORIGINAL 499
#define REPLY 500
#define COUNTER 501
#define NAME 502
#define PACKETS 503
#define BYTES 504
#define AVGPKT 505
#define COUNTERS 506
#define QUOTAS 507
#define LIMITS 508
#define SYNPROXYS 509
#define HELPERS 510
#define LOG 511
#define PREFIX 512
#define GROUP 513
#define SNAPLEN 514
#define QUEUE_THRESHOLD 515
#define LEVEL 516
#define LIMIT 517
#define RATE 518
#define BURST 519
#define OVER 520
#define UNTIL 521
#define QUOTA 522
#define USED 523
#define SECMARK 524
#define SECMARKS 525
#define NANOSECOND 526
#define MICROSECOND 527
#define MILLISECOND 528
#define SECOND 529
#define MINUTE 530
#define HOUR 531
#define DAY 532
#define WEEK 533
#define _REJECT 534
#define WITH 535
#define ICMPX 536
#define SNAT 537
#define DNAT 538
#define MASQUERADE 539
#define REDIRECT 540
#define RANDOM 541
#define FULLY_RANDOM 542
#define PERSISTENT 543
#define QUEUE 544
#define QUEUENUM 545
#define BYPASS 546
#define FANOUT 547
#define DUP 548
#define FWD 549
#define NUMGEN 550
#define INC 551
#define MOD 552
#define OFFSET 553
#define JHASH 554
#define SYMHASH 555
#define SEED 556
#define POSITION 557
#define INDEX 558
#define COMMENT 559
#define XML 560
#define JSON 561
#define VM 562
#define NOTRACK 563
#define EXISTS 564
#define MISSING 565
#define EXTHDR 566
#define IPSEC 567
#define MODE 568
#define REQID 569
#define SPNUM 570
#define TRANSPORT 571
#define TUNNEL 572
#define IN 573
#define OUT 574

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

#line 722 "parser_bison.h" /* yacc.c:1921  */
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
