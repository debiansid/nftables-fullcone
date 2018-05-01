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
    REDEFINE = 283,
    UNDEFINE = 284,
    FIB = 285,
    HOOK = 286,
    DEVICE = 287,
    DEVICES = 288,
    TABLE = 289,
    TABLES = 290,
    CHAIN = 291,
    CHAINS = 292,
    RULE = 293,
    RULES = 294,
    SETS = 295,
    SET = 296,
    ELEMENT = 297,
    MAP = 298,
    MAPS = 299,
    FLOWTABLE = 300,
    HANDLE = 301,
    RULESET = 302,
    TRACE = 303,
    INET = 304,
    NETDEV = 305,
    ADD = 306,
    UPDATE = 307,
    REPLACE = 308,
    CREATE = 309,
    INSERT = 310,
    DELETE = 311,
    GET = 312,
    LIST = 313,
    RESET = 314,
    FLUSH = 315,
    RENAME = 316,
    DESCRIBE = 317,
    IMPORT = 318,
    EXPORT = 319,
    MONITOR = 320,
    ALL = 321,
    ACCEPT = 322,
    DROP = 323,
    CONTINUE = 324,
    JUMP = 325,
    GOTO = 326,
    RETURN = 327,
    TO = 328,
    CONSTANT = 329,
    INTERVAL = 330,
    AUTOMERGE = 331,
    TIMEOUT = 332,
    GC_INTERVAL = 333,
    ELEMENTS = 334,
    POLICY = 335,
    MEMORY = 336,
    PERFORMANCE = 337,
    SIZE = 338,
    FLOW = 339,
    OFFLOAD = 340,
    METER = 341,
    METERS = 342,
    FLOWTABLES = 343,
    NUM = 344,
    STRING = 345,
    QUOTED_STRING = 346,
    ASTERISK_STRING = 347,
    LL_HDR = 348,
    NETWORK_HDR = 349,
    TRANSPORT_HDR = 350,
    BRIDGE = 351,
    ETHER = 352,
    SADDR = 353,
    DADDR = 354,
    TYPE = 355,
    VLAN = 356,
    ID = 357,
    CFI = 358,
    PCP = 359,
    ARP = 360,
    HTYPE = 361,
    PTYPE = 362,
    HLEN = 363,
    PLEN = 364,
    OPERATION = 365,
    IP = 366,
    HDRVERSION = 367,
    HDRLENGTH = 368,
    DSCP = 369,
    ECN = 370,
    LENGTH = 371,
    FRAG_OFF = 372,
    TTL = 373,
    PROTOCOL = 374,
    CHECKSUM = 375,
    ICMP = 376,
    CODE = 377,
    SEQUENCE = 378,
    GATEWAY = 379,
    MTU = 380,
    OPTIONS = 381,
    IP6 = 382,
    PRIORITY = 383,
    FLOWLABEL = 384,
    NEXTHDR = 385,
    HOPLIMIT = 386,
    ICMP6 = 387,
    PPTR = 388,
    MAXDELAY = 389,
    AH = 390,
    RESERVED = 391,
    SPI = 392,
    ESP = 393,
    COMP = 394,
    FLAGS = 395,
    CPI = 396,
    UDP = 397,
    SPORT = 398,
    DPORT = 399,
    UDPLITE = 400,
    CSUMCOV = 401,
    TCP = 402,
    ACKSEQ = 403,
    DOFF = 404,
    WINDOW = 405,
    URGPTR = 406,
    OPTION = 407,
    ECHO = 408,
    EOL = 409,
    MAXSEG = 410,
    NOOP = 411,
    SACK = 412,
    SACK0 = 413,
    SACK1 = 414,
    SACK2 = 415,
    SACK3 = 416,
    SACK_PERMITTED = 417,
    TIMESTAMP = 418,
    KIND = 419,
    COUNT = 420,
    LEFT = 421,
    RIGHT = 422,
    TSVAL = 423,
    TSECR = 424,
    DCCP = 425,
    SCTP = 426,
    VTAG = 427,
    RT = 428,
    RT0 = 429,
    RT2 = 430,
    RT4 = 431,
    SEG_LEFT = 432,
    ADDR = 433,
    LAST_ENT = 434,
    TAG = 435,
    SID = 436,
    HBH = 437,
    FRAG = 438,
    RESERVED2 = 439,
    MORE_FRAGMENTS = 440,
    DST = 441,
    MH = 442,
    META = 443,
    MARK = 444,
    IIF = 445,
    IIFNAME = 446,
    IIFTYPE = 447,
    OIF = 448,
    OIFNAME = 449,
    OIFTYPE = 450,
    SKUID = 451,
    SKGID = 452,
    NFTRACE = 453,
    RTCLASSID = 454,
    IBRIPORT = 455,
    OBRIPORT = 456,
    IBRIDGENAME = 457,
    OBRIDGENAME = 458,
    PKTTYPE = 459,
    CPU = 460,
    IIFGROUP = 461,
    OIFGROUP = 462,
    CGROUP = 463,
    CLASSID = 464,
    NEXTHOP = 465,
    CT = 466,
    L3PROTOCOL = 467,
    PROTO_SRC = 468,
    PROTO_DST = 469,
    ZONE = 470,
    DIRECTION = 471,
    EVENT = 472,
    EXPIRATION = 473,
    HELPER = 474,
    LABEL = 475,
    STATE = 476,
    STATUS = 477,
    ORIGINAL = 478,
    REPLY = 479,
    COUNTER = 480,
    NAME = 481,
    PACKETS = 482,
    BYTES = 483,
    AVGPKT = 484,
    COUNTERS = 485,
    QUOTAS = 486,
    LIMITS = 487,
    HELPERS = 488,
    LOG = 489,
    PREFIX = 490,
    GROUP = 491,
    SNAPLEN = 492,
    QUEUE_THRESHOLD = 493,
    LEVEL = 494,
    LIMIT = 495,
    RATE = 496,
    BURST = 497,
    OVER = 498,
    UNTIL = 499,
    QUOTA = 500,
    USED = 501,
    NANOSECOND = 502,
    MICROSECOND = 503,
    MILLISECOND = 504,
    SECOND = 505,
    MINUTE = 506,
    HOUR = 507,
    DAY = 508,
    WEEK = 509,
    _REJECT = 510,
    WITH = 511,
    ICMPX = 512,
    SNAT = 513,
    DNAT = 514,
    MASQUERADE = 515,
    REDIRECT = 516,
    RANDOM = 517,
    FULLY_RANDOM = 518,
    PERSISTENT = 519,
    QUEUE = 520,
    QUEUENUM = 521,
    BYPASS = 522,
    FANOUT = 523,
    DUP = 524,
    FWD = 525,
    NUMGEN = 526,
    INC = 527,
    MOD = 528,
    OFFSET = 529,
    JHASH = 530,
    SYMHASH = 531,
    SEED = 532,
    POSITION = 533,
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
#define LOOKUP 280
#define INCLUDE 281
#define DEFINE 282
#define REDEFINE 283
#define UNDEFINE 284
#define FIB 285
#define HOOK 286
#define DEVICE 287
#define DEVICES 288
#define TABLE 289
#define TABLES 290
#define CHAIN 291
#define CHAINS 292
#define RULE 293
#define RULES 294
#define SETS 295
#define SET 296
#define ELEMENT 297
#define MAP 298
#define MAPS 299
#define FLOWTABLE 300
#define HANDLE 301
#define RULESET 302
#define TRACE 303
#define INET 304
#define NETDEV 305
#define ADD 306
#define UPDATE 307
#define REPLACE 308
#define CREATE 309
#define INSERT 310
#define DELETE 311
#define GET 312
#define LIST 313
#define RESET 314
#define FLUSH 315
#define RENAME 316
#define DESCRIBE 317
#define IMPORT 318
#define EXPORT 319
#define MONITOR 320
#define ALL 321
#define ACCEPT 322
#define DROP 323
#define CONTINUE 324
#define JUMP 325
#define GOTO 326
#define RETURN 327
#define TO 328
#define CONSTANT 329
#define INTERVAL 330
#define AUTOMERGE 331
#define TIMEOUT 332
#define GC_INTERVAL 333
#define ELEMENTS 334
#define POLICY 335
#define MEMORY 336
#define PERFORMANCE 337
#define SIZE 338
#define FLOW 339
#define OFFLOAD 340
#define METER 341
#define METERS 342
#define FLOWTABLES 343
#define NUM 344
#define STRING 345
#define QUOTED_STRING 346
#define ASTERISK_STRING 347
#define LL_HDR 348
#define NETWORK_HDR 349
#define TRANSPORT_HDR 350
#define BRIDGE 351
#define ETHER 352
#define SADDR 353
#define DADDR 354
#define TYPE 355
#define VLAN 356
#define ID 357
#define CFI 358
#define PCP 359
#define ARP 360
#define HTYPE 361
#define PTYPE 362
#define HLEN 363
#define PLEN 364
#define OPERATION 365
#define IP 366
#define HDRVERSION 367
#define HDRLENGTH 368
#define DSCP 369
#define ECN 370
#define LENGTH 371
#define FRAG_OFF 372
#define TTL 373
#define PROTOCOL 374
#define CHECKSUM 375
#define ICMP 376
#define CODE 377
#define SEQUENCE 378
#define GATEWAY 379
#define MTU 380
#define OPTIONS 381
#define IP6 382
#define PRIORITY 383
#define FLOWLABEL 384
#define NEXTHDR 385
#define HOPLIMIT 386
#define ICMP6 387
#define PPTR 388
#define MAXDELAY 389
#define AH 390
#define RESERVED 391
#define SPI 392
#define ESP 393
#define COMP 394
#define FLAGS 395
#define CPI 396
#define UDP 397
#define SPORT 398
#define DPORT 399
#define UDPLITE 400
#define CSUMCOV 401
#define TCP 402
#define ACKSEQ 403
#define DOFF 404
#define WINDOW 405
#define URGPTR 406
#define OPTION 407
#define ECHO 408
#define EOL 409
#define MAXSEG 410
#define NOOP 411
#define SACK 412
#define SACK0 413
#define SACK1 414
#define SACK2 415
#define SACK3 416
#define SACK_PERMITTED 417
#define TIMESTAMP 418
#define KIND 419
#define COUNT 420
#define LEFT 421
#define RIGHT 422
#define TSVAL 423
#define TSECR 424
#define DCCP 425
#define SCTP 426
#define VTAG 427
#define RT 428
#define RT0 429
#define RT2 430
#define RT4 431
#define SEG_LEFT 432
#define ADDR 433
#define LAST_ENT 434
#define TAG 435
#define SID 436
#define HBH 437
#define FRAG 438
#define RESERVED2 439
#define MORE_FRAGMENTS 440
#define DST 441
#define MH 442
#define META 443
#define MARK 444
#define IIF 445
#define IIFNAME 446
#define IIFTYPE 447
#define OIF 448
#define OIFNAME 449
#define OIFTYPE 450
#define SKUID 451
#define SKGID 452
#define NFTRACE 453
#define RTCLASSID 454
#define IBRIPORT 455
#define OBRIPORT 456
#define IBRIDGENAME 457
#define OBRIDGENAME 458
#define PKTTYPE 459
#define CPU 460
#define IIFGROUP 461
#define OIFGROUP 462
#define CGROUP 463
#define CLASSID 464
#define NEXTHOP 465
#define CT 466
#define L3PROTOCOL 467
#define PROTO_SRC 468
#define PROTO_DST 469
#define ZONE 470
#define DIRECTION 471
#define EVENT 472
#define EXPIRATION 473
#define HELPER 474
#define LABEL 475
#define STATE 476
#define STATUS 477
#define ORIGINAL 478
#define REPLY 479
#define COUNTER 480
#define NAME 481
#define PACKETS 482
#define BYTES 483
#define AVGPKT 484
#define COUNTERS 485
#define QUOTAS 486
#define LIMITS 487
#define HELPERS 488
#define LOG 489
#define PREFIX 490
#define GROUP 491
#define SNAPLEN 492
#define QUEUE_THRESHOLD 493
#define LEVEL 494
#define LIMIT 495
#define RATE 496
#define BURST 497
#define OVER 498
#define UNTIL 499
#define QUOTA 500
#define USED 501
#define NANOSECOND 502
#define MICROSECOND 503
#define MILLISECOND 504
#define SECOND 505
#define MINUTE 506
#define HOUR 507
#define DAY 508
#define WEEK 509
#define _REJECT 510
#define WITH 511
#define ICMPX 512
#define SNAT 513
#define DNAT 514
#define MASQUERADE 515
#define REDIRECT 516
#define RANDOM 517
#define FULLY_RANDOM 518
#define PERSISTENT 519
#define QUEUE 520
#define QUEUENUM 521
#define BYPASS 522
#define FANOUT 523
#define DUP 524
#define FWD 525
#define NUMGEN 526
#define INC 527
#define MOD 528
#define OFFSET 529
#define JHASH 530
#define SYMHASH 531
#define SEED 532
#define POSITION 533
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
