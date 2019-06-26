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
    HOOK = 290,
    DEVICE = 291,
    DEVICES = 292,
    TABLE = 293,
    TABLES = 294,
    CHAIN = 295,
    CHAINS = 296,
    RULE = 297,
    RULES = 298,
    SETS = 299,
    SET = 300,
    ELEMENT = 301,
    MAP = 302,
    MAPS = 303,
    FLOWTABLE = 304,
    HANDLE = 305,
    RULESET = 306,
    TRACE = 307,
    INET = 308,
    NETDEV = 309,
    ADD = 310,
    UPDATE = 311,
    REPLACE = 312,
    CREATE = 313,
    INSERT = 314,
    DELETE = 315,
    GET = 316,
    LIST = 317,
    RESET = 318,
    FLUSH = 319,
    RENAME = 320,
    DESCRIBE = 321,
    IMPORT = 322,
    EXPORT = 323,
    MONITOR = 324,
    ALL = 325,
    ACCEPT = 326,
    DROP = 327,
    CONTINUE = 328,
    JUMP = 329,
    GOTO = 330,
    RETURN = 331,
    TO = 332,
    CONSTANT = 333,
    INTERVAL = 334,
    DYNAMIC = 335,
    AUTOMERGE = 336,
    TIMEOUT = 337,
    GC_INTERVAL = 338,
    ELEMENTS = 339,
    POLICY = 340,
    MEMORY = 341,
    PERFORMANCE = 342,
    SIZE = 343,
    FLOW = 344,
    OFFLOAD = 345,
    METER = 346,
    METERS = 347,
    FLOWTABLES = 348,
    NUM = 349,
    STRING = 350,
    QUOTED_STRING = 351,
    ASTERISK_STRING = 352,
    LL_HDR = 353,
    NETWORK_HDR = 354,
    TRANSPORT_HDR = 355,
    BRIDGE = 356,
    ETHER = 357,
    SADDR = 358,
    DADDR = 359,
    TYPE = 360,
    VLAN = 361,
    ID = 362,
    CFI = 363,
    PCP = 364,
    ARP = 365,
    HTYPE = 366,
    PTYPE = 367,
    HLEN = 368,
    PLEN = 369,
    OPERATION = 370,
    IP = 371,
    HDRVERSION = 372,
    HDRLENGTH = 373,
    DSCP = 374,
    ECN = 375,
    LENGTH = 376,
    FRAG_OFF = 377,
    TTL = 378,
    PROTOCOL = 379,
    CHECKSUM = 380,
    ICMP = 381,
    CODE = 382,
    SEQUENCE = 383,
    GATEWAY = 384,
    MTU = 385,
    IGMP = 386,
    MRT = 387,
    OPTIONS = 388,
    IP6 = 389,
    PRIORITY = 390,
    FLOWLABEL = 391,
    NEXTHDR = 392,
    HOPLIMIT = 393,
    ICMP6 = 394,
    PPTR = 395,
    MAXDELAY = 396,
    AH = 397,
    RESERVED = 398,
    SPI = 399,
    ESP = 400,
    COMP = 401,
    FLAGS = 402,
    CPI = 403,
    UDP = 404,
    SPORT = 405,
    DPORT = 406,
    UDPLITE = 407,
    CSUMCOV = 408,
    TCP = 409,
    ACKSEQ = 410,
    DOFF = 411,
    WINDOW = 412,
    URGPTR = 413,
    OPTION = 414,
    ECHO = 415,
    EOL = 416,
    MAXSEG = 417,
    NOOP = 418,
    SACK = 419,
    SACK0 = 420,
    SACK1 = 421,
    SACK2 = 422,
    SACK3 = 423,
    SACK_PERMITTED = 424,
    TIMESTAMP = 425,
    KIND = 426,
    COUNT = 427,
    LEFT = 428,
    RIGHT = 429,
    TSVAL = 430,
    TSECR = 431,
    DCCP = 432,
    SCTP = 433,
    VTAG = 434,
    RT = 435,
    RT0 = 436,
    RT2 = 437,
    RT4 = 438,
    SEG_LEFT = 439,
    ADDR = 440,
    LAST_ENT = 441,
    TAG = 442,
    SID = 443,
    HBH = 444,
    FRAG = 445,
    RESERVED2 = 446,
    MORE_FRAGMENTS = 447,
    DST = 448,
    MH = 449,
    META = 450,
    MARK = 451,
    IIF = 452,
    IIFNAME = 453,
    IIFTYPE = 454,
    OIF = 455,
    OIFNAME = 456,
    OIFTYPE = 457,
    SKUID = 458,
    SKGID = 459,
    NFTRACE = 460,
    RTCLASSID = 461,
    IBRIPORT = 462,
    OBRIPORT = 463,
    IBRIDGENAME = 464,
    OBRIDGENAME = 465,
    PKTTYPE = 466,
    CPU = 467,
    IIFGROUP = 468,
    OIFGROUP = 469,
    CGROUP = 470,
    CLASSID = 471,
    NEXTHOP = 472,
    CT = 473,
    L3PROTOCOL = 474,
    PROTO_SRC = 475,
    PROTO_DST = 476,
    ZONE = 477,
    DIRECTION = 478,
    EVENT = 479,
    EXPIRATION = 480,
    HELPER = 481,
    LABEL = 482,
    STATE = 483,
    STATUS = 484,
    ORIGINAL = 485,
    REPLY = 486,
    COUNTER = 487,
    NAME = 488,
    PACKETS = 489,
    BYTES = 490,
    AVGPKT = 491,
    COUNTERS = 492,
    QUOTAS = 493,
    LIMITS = 494,
    HELPERS = 495,
    LOG = 496,
    PREFIX = 497,
    GROUP = 498,
    SNAPLEN = 499,
    QUEUE_THRESHOLD = 500,
    LEVEL = 501,
    LIMIT = 502,
    RATE = 503,
    BURST = 504,
    OVER = 505,
    UNTIL = 506,
    QUOTA = 507,
    USED = 508,
    SECMARK = 509,
    SECMARKS = 510,
    NANOSECOND = 511,
    MICROSECOND = 512,
    MILLISECOND = 513,
    SECOND = 514,
    MINUTE = 515,
    HOUR = 516,
    DAY = 517,
    WEEK = 518,
    _REJECT = 519,
    WITH = 520,
    ICMPX = 521,
    SNAT = 522,
    DNAT = 523,
    MASQUERADE = 524,
    REDIRECT = 525,
    RANDOM = 526,
    FULLY_RANDOM = 527,
    PERSISTENT = 528,
    QUEUE = 529,
    QUEUENUM = 530,
    BYPASS = 531,
    FANOUT = 532,
    DUP = 533,
    FWD = 534,
    NUMGEN = 535,
    INC = 536,
    MOD = 537,
    OFFSET = 538,
    JHASH = 539,
    SYMHASH = 540,
    SEED = 541,
    POSITION = 542,
    INDEX = 543,
    COMMENT = 544,
    XML = 545,
    JSON = 546,
    VM = 547,
    NOTRACK = 548,
    EXISTS = 549,
    MISSING = 550,
    EXTHDR = 551,
    IPSEC = 552,
    MODE = 553,
    REQID = 554,
    SPNUM = 555,
    TRANSPORT = 556,
    TUNNEL = 557,
    IN = 558,
    OUT = 559
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
#define HOOK 290
#define DEVICE 291
#define DEVICES 292
#define TABLE 293
#define TABLES 294
#define CHAIN 295
#define CHAINS 296
#define RULE 297
#define RULES 298
#define SETS 299
#define SET 300
#define ELEMENT 301
#define MAP 302
#define MAPS 303
#define FLOWTABLE 304
#define HANDLE 305
#define RULESET 306
#define TRACE 307
#define INET 308
#define NETDEV 309
#define ADD 310
#define UPDATE 311
#define REPLACE 312
#define CREATE 313
#define INSERT 314
#define DELETE 315
#define GET 316
#define LIST 317
#define RESET 318
#define FLUSH 319
#define RENAME 320
#define DESCRIBE 321
#define IMPORT 322
#define EXPORT 323
#define MONITOR 324
#define ALL 325
#define ACCEPT 326
#define DROP 327
#define CONTINUE 328
#define JUMP 329
#define GOTO 330
#define RETURN 331
#define TO 332
#define CONSTANT 333
#define INTERVAL 334
#define DYNAMIC 335
#define AUTOMERGE 336
#define TIMEOUT 337
#define GC_INTERVAL 338
#define ELEMENTS 339
#define POLICY 340
#define MEMORY 341
#define PERFORMANCE 342
#define SIZE 343
#define FLOW 344
#define OFFLOAD 345
#define METER 346
#define METERS 347
#define FLOWTABLES 348
#define NUM 349
#define STRING 350
#define QUOTED_STRING 351
#define ASTERISK_STRING 352
#define LL_HDR 353
#define NETWORK_HDR 354
#define TRANSPORT_HDR 355
#define BRIDGE 356
#define ETHER 357
#define SADDR 358
#define DADDR 359
#define TYPE 360
#define VLAN 361
#define ID 362
#define CFI 363
#define PCP 364
#define ARP 365
#define HTYPE 366
#define PTYPE 367
#define HLEN 368
#define PLEN 369
#define OPERATION 370
#define IP 371
#define HDRVERSION 372
#define HDRLENGTH 373
#define DSCP 374
#define ECN 375
#define LENGTH 376
#define FRAG_OFF 377
#define TTL 378
#define PROTOCOL 379
#define CHECKSUM 380
#define ICMP 381
#define CODE 382
#define SEQUENCE 383
#define GATEWAY 384
#define MTU 385
#define IGMP 386
#define MRT 387
#define OPTIONS 388
#define IP6 389
#define PRIORITY 390
#define FLOWLABEL 391
#define NEXTHDR 392
#define HOPLIMIT 393
#define ICMP6 394
#define PPTR 395
#define MAXDELAY 396
#define AH 397
#define RESERVED 398
#define SPI 399
#define ESP 400
#define COMP 401
#define FLAGS 402
#define CPI 403
#define UDP 404
#define SPORT 405
#define DPORT 406
#define UDPLITE 407
#define CSUMCOV 408
#define TCP 409
#define ACKSEQ 410
#define DOFF 411
#define WINDOW 412
#define URGPTR 413
#define OPTION 414
#define ECHO 415
#define EOL 416
#define MAXSEG 417
#define NOOP 418
#define SACK 419
#define SACK0 420
#define SACK1 421
#define SACK2 422
#define SACK3 423
#define SACK_PERMITTED 424
#define TIMESTAMP 425
#define KIND 426
#define COUNT 427
#define LEFT 428
#define RIGHT 429
#define TSVAL 430
#define TSECR 431
#define DCCP 432
#define SCTP 433
#define VTAG 434
#define RT 435
#define RT0 436
#define RT2 437
#define RT4 438
#define SEG_LEFT 439
#define ADDR 440
#define LAST_ENT 441
#define TAG 442
#define SID 443
#define HBH 444
#define FRAG 445
#define RESERVED2 446
#define MORE_FRAGMENTS 447
#define DST 448
#define MH 449
#define META 450
#define MARK 451
#define IIF 452
#define IIFNAME 453
#define IIFTYPE 454
#define OIF 455
#define OIFNAME 456
#define OIFTYPE 457
#define SKUID 458
#define SKGID 459
#define NFTRACE 460
#define RTCLASSID 461
#define IBRIPORT 462
#define OBRIPORT 463
#define IBRIDGENAME 464
#define OBRIDGENAME 465
#define PKTTYPE 466
#define CPU 467
#define IIFGROUP 468
#define OIFGROUP 469
#define CGROUP 470
#define CLASSID 471
#define NEXTHOP 472
#define CT 473
#define L3PROTOCOL 474
#define PROTO_SRC 475
#define PROTO_DST 476
#define ZONE 477
#define DIRECTION 478
#define EVENT 479
#define EXPIRATION 480
#define HELPER 481
#define LABEL 482
#define STATE 483
#define STATUS 484
#define ORIGINAL 485
#define REPLY 486
#define COUNTER 487
#define NAME 488
#define PACKETS 489
#define BYTES 490
#define AVGPKT 491
#define COUNTERS 492
#define QUOTAS 493
#define LIMITS 494
#define HELPERS 495
#define LOG 496
#define PREFIX 497
#define GROUP 498
#define SNAPLEN 499
#define QUEUE_THRESHOLD 500
#define LEVEL 501
#define LIMIT 502
#define RATE 503
#define BURST 504
#define OVER 505
#define UNTIL 506
#define QUOTA 507
#define USED 508
#define SECMARK 509
#define SECMARKS 510
#define NANOSECOND 511
#define MICROSECOND 512
#define MILLISECOND 513
#define SECOND 514
#define MINUTE 515
#define HOUR 516
#define DAY 517
#define WEEK 518
#define _REJECT 519
#define WITH 520
#define ICMPX 521
#define SNAT 522
#define DNAT 523
#define MASQUERADE 524
#define REDIRECT 525
#define RANDOM 526
#define FULLY_RANDOM 527
#define PERSISTENT 528
#define QUEUE 529
#define QUEUENUM 530
#define BYPASS 531
#define FANOUT 532
#define DUP 533
#define FWD 534
#define NUMGEN 535
#define INC 536
#define MOD 537
#define OFFSET 538
#define JHASH 539
#define SYMHASH 540
#define SEED 541
#define POSITION 542
#define INDEX 543
#define COMMENT 544
#define XML 545
#define JSON 546
#define VM 547
#define NOTRACK 548
#define EXISTS 549
#define MISSING 550
#define EXTHDR 551
#define IPSEC 552
#define MODE 553
#define REQID 554
#define SPNUM 555
#define TRANSPORT 556
#define TUNNEL 557
#define IN 558
#define OUT 559

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

#line 691 "parser_bison.h" /* yacc.c:1909  */
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
