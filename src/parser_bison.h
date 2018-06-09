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
    INCLUDE = 280,
    DEFINE = 281,
    REDEFINE = 282,
    UNDEFINE = 283,
    FIB = 284,
    SOCKET = 285,
    TRANSPARENT = 286,
    HOOK = 287,
    DEVICE = 288,
    DEVICES = 289,
    TABLE = 290,
    TABLES = 291,
    CHAIN = 292,
    CHAINS = 293,
    RULE = 294,
    RULES = 295,
    SETS = 296,
    SET = 297,
    ELEMENT = 298,
    MAP = 299,
    MAPS = 300,
    FLOWTABLE = 301,
    HANDLE = 302,
    RULESET = 303,
    TRACE = 304,
    INET = 305,
    NETDEV = 306,
    ADD = 307,
    UPDATE = 308,
    REPLACE = 309,
    CREATE = 310,
    INSERT = 311,
    DELETE = 312,
    GET = 313,
    LIST = 314,
    RESET = 315,
    FLUSH = 316,
    RENAME = 317,
    DESCRIBE = 318,
    IMPORT = 319,
    EXPORT = 320,
    MONITOR = 321,
    ALL = 322,
    ACCEPT = 323,
    DROP = 324,
    CONTINUE = 325,
    JUMP = 326,
    GOTO = 327,
    RETURN = 328,
    TO = 329,
    CONSTANT = 330,
    INTERVAL = 331,
    AUTOMERGE = 332,
    TIMEOUT = 333,
    GC_INTERVAL = 334,
    ELEMENTS = 335,
    POLICY = 336,
    MEMORY = 337,
    PERFORMANCE = 338,
    SIZE = 339,
    FLOW = 340,
    OFFLOAD = 341,
    METER = 342,
    METERS = 343,
    FLOWTABLES = 344,
    NUM = 345,
    STRING = 346,
    QUOTED_STRING = 347,
    ASTERISK_STRING = 348,
    LL_HDR = 349,
    NETWORK_HDR = 350,
    TRANSPORT_HDR = 351,
    BRIDGE = 352,
    ETHER = 353,
    SADDR = 354,
    DADDR = 355,
    TYPE = 356,
    VLAN = 357,
    ID = 358,
    CFI = 359,
    PCP = 360,
    ARP = 361,
    HTYPE = 362,
    PTYPE = 363,
    HLEN = 364,
    PLEN = 365,
    OPERATION = 366,
    IP = 367,
    HDRVERSION = 368,
    HDRLENGTH = 369,
    DSCP = 370,
    ECN = 371,
    LENGTH = 372,
    FRAG_OFF = 373,
    TTL = 374,
    PROTOCOL = 375,
    CHECKSUM = 376,
    ICMP = 377,
    CODE = 378,
    SEQUENCE = 379,
    GATEWAY = 380,
    MTU = 381,
    OPTIONS = 382,
    IP6 = 383,
    PRIORITY = 384,
    FLOWLABEL = 385,
    NEXTHDR = 386,
    HOPLIMIT = 387,
    ICMP6 = 388,
    PPTR = 389,
    MAXDELAY = 390,
    AH = 391,
    RESERVED = 392,
    SPI = 393,
    ESP = 394,
    COMP = 395,
    FLAGS = 396,
    CPI = 397,
    UDP = 398,
    SPORT = 399,
    DPORT = 400,
    UDPLITE = 401,
    CSUMCOV = 402,
    TCP = 403,
    ACKSEQ = 404,
    DOFF = 405,
    WINDOW = 406,
    URGPTR = 407,
    OPTION = 408,
    ECHO = 409,
    EOL = 410,
    MAXSEG = 411,
    NOOP = 412,
    SACK = 413,
    SACK0 = 414,
    SACK1 = 415,
    SACK2 = 416,
    SACK3 = 417,
    SACK_PERMITTED = 418,
    TIMESTAMP = 419,
    KIND = 420,
    COUNT = 421,
    LEFT = 422,
    RIGHT = 423,
    TSVAL = 424,
    TSECR = 425,
    DCCP = 426,
    SCTP = 427,
    VTAG = 428,
    RT = 429,
    RT0 = 430,
    RT2 = 431,
    RT4 = 432,
    SEG_LEFT = 433,
    ADDR = 434,
    LAST_ENT = 435,
    TAG = 436,
    SID = 437,
    HBH = 438,
    FRAG = 439,
    RESERVED2 = 440,
    MORE_FRAGMENTS = 441,
    DST = 442,
    MH = 443,
    META = 444,
    MARK = 445,
    IIF = 446,
    IIFNAME = 447,
    IIFTYPE = 448,
    OIF = 449,
    OIFNAME = 450,
    OIFTYPE = 451,
    SKUID = 452,
    SKGID = 453,
    NFTRACE = 454,
    RTCLASSID = 455,
    IBRIPORT = 456,
    OBRIPORT = 457,
    IBRIDGENAME = 458,
    OBRIDGENAME = 459,
    PKTTYPE = 460,
    CPU = 461,
    IIFGROUP = 462,
    OIFGROUP = 463,
    CGROUP = 464,
    CLASSID = 465,
    NEXTHOP = 466,
    CT = 467,
    L3PROTOCOL = 468,
    PROTO_SRC = 469,
    PROTO_DST = 470,
    ZONE = 471,
    DIRECTION = 472,
    EVENT = 473,
    EXPIRATION = 474,
    HELPER = 475,
    LABEL = 476,
    STATE = 477,
    STATUS = 478,
    ORIGINAL = 479,
    REPLY = 480,
    COUNTER = 481,
    NAME = 482,
    PACKETS = 483,
    BYTES = 484,
    AVGPKT = 485,
    COUNTERS = 486,
    QUOTAS = 487,
    LIMITS = 488,
    HELPERS = 489,
    LOG = 490,
    PREFIX = 491,
    GROUP = 492,
    SNAPLEN = 493,
    QUEUE_THRESHOLD = 494,
    LEVEL = 495,
    LIMIT = 496,
    RATE = 497,
    BURST = 498,
    OVER = 499,
    UNTIL = 500,
    QUOTA = 501,
    USED = 502,
    NANOSECOND = 503,
    MICROSECOND = 504,
    MILLISECOND = 505,
    SECOND = 506,
    MINUTE = 507,
    HOUR = 508,
    DAY = 509,
    WEEK = 510,
    _REJECT = 511,
    WITH = 512,
    ICMPX = 513,
    SNAT = 514,
    DNAT = 515,
    MASQUERADE = 516,
    REDIRECT = 517,
    RANDOM = 518,
    FULLY_RANDOM = 519,
    PERSISTENT = 520,
    QUEUE = 521,
    QUEUENUM = 522,
    BYPASS = 523,
    FANOUT = 524,
    DUP = 525,
    FWD = 526,
    NUMGEN = 527,
    INC = 528,
    MOD = 529,
    OFFSET = 530,
    JHASH = 531,
    SYMHASH = 532,
    SEED = 533,
    POSITION = 534,
    INDEX = 535,
    COMMENT = 536,
    XML = 537,
    JSON = 538,
    VM = 539,
    NOTRACK = 540,
    EXISTS = 541,
    MISSING = 542,
    EXTHDR = 543
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
#define REDEFINE 282
#define UNDEFINE 283
#define FIB 284
#define SOCKET 285
#define TRANSPARENT 286
#define HOOK 287
#define DEVICE 288
#define DEVICES 289
#define TABLE 290
#define TABLES 291
#define CHAIN 292
#define CHAINS 293
#define RULE 294
#define RULES 295
#define SETS 296
#define SET 297
#define ELEMENT 298
#define MAP 299
#define MAPS 300
#define FLOWTABLE 301
#define HANDLE 302
#define RULESET 303
#define TRACE 304
#define INET 305
#define NETDEV 306
#define ADD 307
#define UPDATE 308
#define REPLACE 309
#define CREATE 310
#define INSERT 311
#define DELETE 312
#define GET 313
#define LIST 314
#define RESET 315
#define FLUSH 316
#define RENAME 317
#define DESCRIBE 318
#define IMPORT 319
#define EXPORT 320
#define MONITOR 321
#define ALL 322
#define ACCEPT 323
#define DROP 324
#define CONTINUE 325
#define JUMP 326
#define GOTO 327
#define RETURN 328
#define TO 329
#define CONSTANT 330
#define INTERVAL 331
#define AUTOMERGE 332
#define TIMEOUT 333
#define GC_INTERVAL 334
#define ELEMENTS 335
#define POLICY 336
#define MEMORY 337
#define PERFORMANCE 338
#define SIZE 339
#define FLOW 340
#define OFFLOAD 341
#define METER 342
#define METERS 343
#define FLOWTABLES 344
#define NUM 345
#define STRING 346
#define QUOTED_STRING 347
#define ASTERISK_STRING 348
#define LL_HDR 349
#define NETWORK_HDR 350
#define TRANSPORT_HDR 351
#define BRIDGE 352
#define ETHER 353
#define SADDR 354
#define DADDR 355
#define TYPE 356
#define VLAN 357
#define ID 358
#define CFI 359
#define PCP 360
#define ARP 361
#define HTYPE 362
#define PTYPE 363
#define HLEN 364
#define PLEN 365
#define OPERATION 366
#define IP 367
#define HDRVERSION 368
#define HDRLENGTH 369
#define DSCP 370
#define ECN 371
#define LENGTH 372
#define FRAG_OFF 373
#define TTL 374
#define PROTOCOL 375
#define CHECKSUM 376
#define ICMP 377
#define CODE 378
#define SEQUENCE 379
#define GATEWAY 380
#define MTU 381
#define OPTIONS 382
#define IP6 383
#define PRIORITY 384
#define FLOWLABEL 385
#define NEXTHDR 386
#define HOPLIMIT 387
#define ICMP6 388
#define PPTR 389
#define MAXDELAY 390
#define AH 391
#define RESERVED 392
#define SPI 393
#define ESP 394
#define COMP 395
#define FLAGS 396
#define CPI 397
#define UDP 398
#define SPORT 399
#define DPORT 400
#define UDPLITE 401
#define CSUMCOV 402
#define TCP 403
#define ACKSEQ 404
#define DOFF 405
#define WINDOW 406
#define URGPTR 407
#define OPTION 408
#define ECHO 409
#define EOL 410
#define MAXSEG 411
#define NOOP 412
#define SACK 413
#define SACK0 414
#define SACK1 415
#define SACK2 416
#define SACK3 417
#define SACK_PERMITTED 418
#define TIMESTAMP 419
#define KIND 420
#define COUNT 421
#define LEFT 422
#define RIGHT 423
#define TSVAL 424
#define TSECR 425
#define DCCP 426
#define SCTP 427
#define VTAG 428
#define RT 429
#define RT0 430
#define RT2 431
#define RT4 432
#define SEG_LEFT 433
#define ADDR 434
#define LAST_ENT 435
#define TAG 436
#define SID 437
#define HBH 438
#define FRAG 439
#define RESERVED2 440
#define MORE_FRAGMENTS 441
#define DST 442
#define MH 443
#define META 444
#define MARK 445
#define IIF 446
#define IIFNAME 447
#define IIFTYPE 448
#define OIF 449
#define OIFNAME 450
#define OIFTYPE 451
#define SKUID 452
#define SKGID 453
#define NFTRACE 454
#define RTCLASSID 455
#define IBRIPORT 456
#define OBRIPORT 457
#define IBRIDGENAME 458
#define OBRIDGENAME 459
#define PKTTYPE 460
#define CPU 461
#define IIFGROUP 462
#define OIFGROUP 463
#define CGROUP 464
#define CLASSID 465
#define NEXTHOP 466
#define CT 467
#define L3PROTOCOL 468
#define PROTO_SRC 469
#define PROTO_DST 470
#define ZONE 471
#define DIRECTION 472
#define EVENT 473
#define EXPIRATION 474
#define HELPER 475
#define LABEL 476
#define STATE 477
#define STATUS 478
#define ORIGINAL 479
#define REPLY 480
#define COUNTER 481
#define NAME 482
#define PACKETS 483
#define BYTES 484
#define AVGPKT 485
#define COUNTERS 486
#define QUOTAS 487
#define LIMITS 488
#define HELPERS 489
#define LOG 490
#define PREFIX 491
#define GROUP 492
#define SNAPLEN 493
#define QUEUE_THRESHOLD 494
#define LEVEL 495
#define LIMIT 496
#define RATE 497
#define BURST 498
#define OVER 499
#define UNTIL 500
#define QUOTA 501
#define USED 502
#define NANOSECOND 503
#define MICROSECOND 504
#define MILLISECOND 505
#define SECOND 506
#define MINUTE 507
#define HOUR 508
#define DAY 509
#define WEEK 510
#define _REJECT 511
#define WITH 512
#define ICMPX 513
#define SNAT 514
#define DNAT 515
#define MASQUERADE 516
#define REDIRECT 517
#define RANDOM 518
#define FULLY_RANDOM 519
#define PERSISTENT 520
#define QUEUE 521
#define QUEUENUM 522
#define BYPASS 523
#define FANOUT 524
#define DUP 525
#define FWD 526
#define NUMGEN 527
#define INC 528
#define MOD 529
#define OFFSET 530
#define JHASH 531
#define SYMHASH 532
#define SEED 533
#define POSITION 534
#define INDEX 535
#define COMMENT 536
#define XML 537
#define JSON 538
#define VM 539
#define NOTRACK 540
#define EXISTS 541
#define MISSING 542
#define EXTHDR 543

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
	struct ct		*ct;
	struct limit		*limit;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	const struct exthdr_desc *exthdr_desc;

#line 657 "parser_bison.h" /* yacc.c:1909  */
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
