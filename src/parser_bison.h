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
    HOOK = 285,
    DEVICE = 286,
    DEVICES = 287,
    TABLE = 288,
    TABLES = 289,
    CHAIN = 290,
    CHAINS = 291,
    RULE = 292,
    RULES = 293,
    SETS = 294,
    SET = 295,
    ELEMENT = 296,
    MAP = 297,
    MAPS = 298,
    FLOWTABLE = 299,
    HANDLE = 300,
    RULESET = 301,
    TRACE = 302,
    INET = 303,
    NETDEV = 304,
    ADD = 305,
    UPDATE = 306,
    REPLACE = 307,
    CREATE = 308,
    INSERT = 309,
    DELETE = 310,
    GET = 311,
    LIST = 312,
    RESET = 313,
    FLUSH = 314,
    RENAME = 315,
    DESCRIBE = 316,
    IMPORT = 317,
    EXPORT = 318,
    MONITOR = 319,
    ALL = 320,
    ACCEPT = 321,
    DROP = 322,
    CONTINUE = 323,
    JUMP = 324,
    GOTO = 325,
    RETURN = 326,
    TO = 327,
    CONSTANT = 328,
    INTERVAL = 329,
    AUTOMERGE = 330,
    TIMEOUT = 331,
    GC_INTERVAL = 332,
    ELEMENTS = 333,
    POLICY = 334,
    MEMORY = 335,
    PERFORMANCE = 336,
    SIZE = 337,
    FLOW = 338,
    OFFLOAD = 339,
    METER = 340,
    METERS = 341,
    FLOWTABLES = 342,
    NUM = 343,
    STRING = 344,
    QUOTED_STRING = 345,
    ASTERISK_STRING = 346,
    LL_HDR = 347,
    NETWORK_HDR = 348,
    TRANSPORT_HDR = 349,
    BRIDGE = 350,
    ETHER = 351,
    SADDR = 352,
    DADDR = 353,
    TYPE = 354,
    VLAN = 355,
    ID = 356,
    CFI = 357,
    PCP = 358,
    ARP = 359,
    HTYPE = 360,
    PTYPE = 361,
    HLEN = 362,
    PLEN = 363,
    OPERATION = 364,
    IP = 365,
    HDRVERSION = 366,
    HDRLENGTH = 367,
    DSCP = 368,
    ECN = 369,
    LENGTH = 370,
    FRAG_OFF = 371,
    TTL = 372,
    PROTOCOL = 373,
    CHECKSUM = 374,
    ICMP = 375,
    CODE = 376,
    SEQUENCE = 377,
    GATEWAY = 378,
    MTU = 379,
    OPTIONS = 380,
    IP6 = 381,
    PRIORITY = 382,
    FLOWLABEL = 383,
    NEXTHDR = 384,
    HOPLIMIT = 385,
    ICMP6 = 386,
    PPTR = 387,
    MAXDELAY = 388,
    AH = 389,
    RESERVED = 390,
    SPI = 391,
    ESP = 392,
    COMP = 393,
    FLAGS = 394,
    CPI = 395,
    UDP = 396,
    SPORT = 397,
    DPORT = 398,
    UDPLITE = 399,
    CSUMCOV = 400,
    TCP = 401,
    ACKSEQ = 402,
    DOFF = 403,
    WINDOW = 404,
    URGPTR = 405,
    OPTION = 406,
    ECHO = 407,
    EOL = 408,
    MAXSEG = 409,
    NOOP = 410,
    SACK = 411,
    SACK0 = 412,
    SACK1 = 413,
    SACK2 = 414,
    SACK3 = 415,
    SACK_PERMITTED = 416,
    TIMESTAMP = 417,
    KIND = 418,
    COUNT = 419,
    LEFT = 420,
    RIGHT = 421,
    TSVAL = 422,
    TSECR = 423,
    DCCP = 424,
    SCTP = 425,
    VTAG = 426,
    RT = 427,
    RT0 = 428,
    RT2 = 429,
    RT4 = 430,
    SEG_LEFT = 431,
    ADDR = 432,
    LAST_ENT = 433,
    TAG = 434,
    SID = 435,
    HBH = 436,
    FRAG = 437,
    RESERVED2 = 438,
    MORE_FRAGMENTS = 439,
    DST = 440,
    MH = 441,
    META = 442,
    MARK = 443,
    IIF = 444,
    IIFNAME = 445,
    IIFTYPE = 446,
    OIF = 447,
    OIFNAME = 448,
    OIFTYPE = 449,
    SKUID = 450,
    SKGID = 451,
    NFTRACE = 452,
    RTCLASSID = 453,
    IBRIPORT = 454,
    OBRIPORT = 455,
    IBRIDGENAME = 456,
    OBRIDGENAME = 457,
    PKTTYPE = 458,
    CPU = 459,
    IIFGROUP = 460,
    OIFGROUP = 461,
    CGROUP = 462,
    CLASSID = 463,
    NEXTHOP = 464,
    CT = 465,
    L3PROTOCOL = 466,
    PROTO_SRC = 467,
    PROTO_DST = 468,
    ZONE = 469,
    DIRECTION = 470,
    EVENT = 471,
    EXPIRATION = 472,
    HELPER = 473,
    LABEL = 474,
    STATE = 475,
    STATUS = 476,
    ORIGINAL = 477,
    REPLY = 478,
    COUNTER = 479,
    NAME = 480,
    PACKETS = 481,
    BYTES = 482,
    AVGPKT = 483,
    COUNTERS = 484,
    QUOTAS = 485,
    LIMITS = 486,
    HELPERS = 487,
    LOG = 488,
    PREFIX = 489,
    GROUP = 490,
    SNAPLEN = 491,
    QUEUE_THRESHOLD = 492,
    LEVEL = 493,
    LIMIT = 494,
    RATE = 495,
    BURST = 496,
    OVER = 497,
    UNTIL = 498,
    QUOTA = 499,
    USED = 500,
    NANOSECOND = 501,
    MICROSECOND = 502,
    MILLISECOND = 503,
    SECOND = 504,
    MINUTE = 505,
    HOUR = 506,
    DAY = 507,
    WEEK = 508,
    _REJECT = 509,
    WITH = 510,
    ICMPX = 511,
    SNAT = 512,
    DNAT = 513,
    MASQUERADE = 514,
    REDIRECT = 515,
    RANDOM = 516,
    FULLY_RANDOM = 517,
    PERSISTENT = 518,
    QUEUE = 519,
    QUEUENUM = 520,
    BYPASS = 521,
    FANOUT = 522,
    DUP = 523,
    FWD = 524,
    NUMGEN = 525,
    INC = 526,
    MOD = 527,
    OFFSET = 528,
    JHASH = 529,
    SYMHASH = 530,
    SEED = 531,
    POSITION = 532,
    INDEX = 533,
    COMMENT = 534,
    XML = 535,
    JSON = 536,
    VM = 537,
    NOTRACK = 538,
    EXISTS = 539,
    MISSING = 540,
    EXTHDR = 541
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
#define HOOK 285
#define DEVICE 286
#define DEVICES 287
#define TABLE 288
#define TABLES 289
#define CHAIN 290
#define CHAINS 291
#define RULE 292
#define RULES 293
#define SETS 294
#define SET 295
#define ELEMENT 296
#define MAP 297
#define MAPS 298
#define FLOWTABLE 299
#define HANDLE 300
#define RULESET 301
#define TRACE 302
#define INET 303
#define NETDEV 304
#define ADD 305
#define UPDATE 306
#define REPLACE 307
#define CREATE 308
#define INSERT 309
#define DELETE 310
#define GET 311
#define LIST 312
#define RESET 313
#define FLUSH 314
#define RENAME 315
#define DESCRIBE 316
#define IMPORT 317
#define EXPORT 318
#define MONITOR 319
#define ALL 320
#define ACCEPT 321
#define DROP 322
#define CONTINUE 323
#define JUMP 324
#define GOTO 325
#define RETURN 326
#define TO 327
#define CONSTANT 328
#define INTERVAL 329
#define AUTOMERGE 330
#define TIMEOUT 331
#define GC_INTERVAL 332
#define ELEMENTS 333
#define POLICY 334
#define MEMORY 335
#define PERFORMANCE 336
#define SIZE 337
#define FLOW 338
#define OFFLOAD 339
#define METER 340
#define METERS 341
#define FLOWTABLES 342
#define NUM 343
#define STRING 344
#define QUOTED_STRING 345
#define ASTERISK_STRING 346
#define LL_HDR 347
#define NETWORK_HDR 348
#define TRANSPORT_HDR 349
#define BRIDGE 350
#define ETHER 351
#define SADDR 352
#define DADDR 353
#define TYPE 354
#define VLAN 355
#define ID 356
#define CFI 357
#define PCP 358
#define ARP 359
#define HTYPE 360
#define PTYPE 361
#define HLEN 362
#define PLEN 363
#define OPERATION 364
#define IP 365
#define HDRVERSION 366
#define HDRLENGTH 367
#define DSCP 368
#define ECN 369
#define LENGTH 370
#define FRAG_OFF 371
#define TTL 372
#define PROTOCOL 373
#define CHECKSUM 374
#define ICMP 375
#define CODE 376
#define SEQUENCE 377
#define GATEWAY 378
#define MTU 379
#define OPTIONS 380
#define IP6 381
#define PRIORITY 382
#define FLOWLABEL 383
#define NEXTHDR 384
#define HOPLIMIT 385
#define ICMP6 386
#define PPTR 387
#define MAXDELAY 388
#define AH 389
#define RESERVED 390
#define SPI 391
#define ESP 392
#define COMP 393
#define FLAGS 394
#define CPI 395
#define UDP 396
#define SPORT 397
#define DPORT 398
#define UDPLITE 399
#define CSUMCOV 400
#define TCP 401
#define ACKSEQ 402
#define DOFF 403
#define WINDOW 404
#define URGPTR 405
#define OPTION 406
#define ECHO 407
#define EOL 408
#define MAXSEG 409
#define NOOP 410
#define SACK 411
#define SACK0 412
#define SACK1 413
#define SACK2 414
#define SACK3 415
#define SACK_PERMITTED 416
#define TIMESTAMP 417
#define KIND 418
#define COUNT 419
#define LEFT 420
#define RIGHT 421
#define TSVAL 422
#define TSECR 423
#define DCCP 424
#define SCTP 425
#define VTAG 426
#define RT 427
#define RT0 428
#define RT2 429
#define RT4 430
#define SEG_LEFT 431
#define ADDR 432
#define LAST_ENT 433
#define TAG 434
#define SID 435
#define HBH 436
#define FRAG 437
#define RESERVED2 438
#define MORE_FRAGMENTS 439
#define DST 440
#define MH 441
#define META 442
#define MARK 443
#define IIF 444
#define IIFNAME 445
#define IIFTYPE 446
#define OIF 447
#define OIFNAME 448
#define OIFTYPE 449
#define SKUID 450
#define SKGID 451
#define NFTRACE 452
#define RTCLASSID 453
#define IBRIPORT 454
#define OBRIPORT 455
#define IBRIDGENAME 456
#define OBRIDGENAME 457
#define PKTTYPE 458
#define CPU 459
#define IIFGROUP 460
#define OIFGROUP 461
#define CGROUP 462
#define CLASSID 463
#define NEXTHOP 464
#define CT 465
#define L3PROTOCOL 466
#define PROTO_SRC 467
#define PROTO_DST 468
#define ZONE 469
#define DIRECTION 470
#define EVENT 471
#define EXPIRATION 472
#define HELPER 473
#define LABEL 474
#define STATE 475
#define STATUS 476
#define ORIGINAL 477
#define REPLY 478
#define COUNTER 479
#define NAME 480
#define PACKETS 481
#define BYTES 482
#define AVGPKT 483
#define COUNTERS 484
#define QUOTAS 485
#define LIMITS 486
#define HELPERS 487
#define LOG 488
#define PREFIX 489
#define GROUP 490
#define SNAPLEN 491
#define QUEUE_THRESHOLD 492
#define LEVEL 493
#define LIMIT 494
#define RATE 495
#define BURST 496
#define OVER 497
#define UNTIL 498
#define QUOTA 499
#define USED 500
#define NANOSECOND 501
#define MICROSECOND 502
#define MILLISECOND 503
#define SECOND 504
#define MINUTE 505
#define HOUR 506
#define DAY 507
#define WEEK 508
#define _REJECT 509
#define WITH 510
#define ICMPX 511
#define SNAT 512
#define DNAT 513
#define MASQUERADE 514
#define REDIRECT 515
#define RANDOM 516
#define FULLY_RANDOM 517
#define PERSISTENT 518
#define QUEUE 519
#define QUEUENUM 520
#define BYPASS 521
#define FANOUT 522
#define DUP 523
#define FWD 524
#define NUMGEN 525
#define INC 526
#define MOD 527
#define OFFSET 528
#define JHASH 529
#define SYMHASH 530
#define SEED 531
#define POSITION 532
#define INDEX 533
#define COMMENT 534
#define XML 535
#define JSON 536
#define VM 537
#define NOTRACK 538
#define EXISTS 539
#define MISSING 540
#define EXTHDR 541

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

#line 653 "parser_bison.h" /* yacc.c:1909  */
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
