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
    HANDLE = 299,
    RULESET = 300,
    TRACE = 301,
    INET = 302,
    NETDEV = 303,
    ADD = 304,
    UPDATE = 305,
    REPLACE = 306,
    CREATE = 307,
    INSERT = 308,
    DELETE = 309,
    LIST = 310,
    RESET = 311,
    FLUSH = 312,
    RENAME = 313,
    DESCRIBE = 314,
    IMPORT = 315,
    EXPORT = 316,
    MONITOR = 317,
    ALL = 318,
    ACCEPT = 319,
    DROP = 320,
    CONTINUE = 321,
    JUMP = 322,
    GOTO = 323,
    RETURN = 324,
    TO = 325,
    CONSTANT = 326,
    INTERVAL = 327,
    AUTOMERGE = 328,
    TIMEOUT = 329,
    GC_INTERVAL = 330,
    ELEMENTS = 331,
    POLICY = 332,
    MEMORY = 333,
    PERFORMANCE = 334,
    SIZE = 335,
    FLOW = 336,
    METER = 337,
    METERS = 338,
    NUM = 339,
    STRING = 340,
    QUOTED_STRING = 341,
    ASTERISK_STRING = 342,
    LL_HDR = 343,
    NETWORK_HDR = 344,
    TRANSPORT_HDR = 345,
    BRIDGE = 346,
    ETHER = 347,
    SADDR = 348,
    DADDR = 349,
    TYPE = 350,
    VLAN = 351,
    ID = 352,
    CFI = 353,
    PCP = 354,
    ARP = 355,
    HTYPE = 356,
    PTYPE = 357,
    HLEN = 358,
    PLEN = 359,
    OPERATION = 360,
    IP = 361,
    HDRVERSION = 362,
    HDRLENGTH = 363,
    DSCP = 364,
    ECN = 365,
    LENGTH = 366,
    FRAG_OFF = 367,
    TTL = 368,
    PROTOCOL = 369,
    CHECKSUM = 370,
    ICMP = 371,
    CODE = 372,
    SEQUENCE = 373,
    GATEWAY = 374,
    MTU = 375,
    OPTIONS = 376,
    IP6 = 377,
    PRIORITY = 378,
    FLOWLABEL = 379,
    NEXTHDR = 380,
    HOPLIMIT = 381,
    ICMP6 = 382,
    PPTR = 383,
    MAXDELAY = 384,
    AH = 385,
    RESERVED = 386,
    SPI = 387,
    ESP = 388,
    COMP = 389,
    FLAGS = 390,
    CPI = 391,
    UDP = 392,
    SPORT = 393,
    DPORT = 394,
    UDPLITE = 395,
    CSUMCOV = 396,
    TCP = 397,
    ACKSEQ = 398,
    DOFF = 399,
    WINDOW = 400,
    URGPTR = 401,
    OPTION = 402,
    ECHO = 403,
    EOL = 404,
    MAXSEG = 405,
    NOOP = 406,
    SACK = 407,
    SACK0 = 408,
    SACK1 = 409,
    SACK2 = 410,
    SACK3 = 411,
    SACK_PERMITTED = 412,
    TIMESTAMP = 413,
    KIND = 414,
    COUNT = 415,
    LEFT = 416,
    RIGHT = 417,
    TSVAL = 418,
    TSECR = 419,
    DCCP = 420,
    SCTP = 421,
    VTAG = 422,
    RT = 423,
    RT0 = 424,
    RT2 = 425,
    SEG_LEFT = 426,
    ADDR = 427,
    HBH = 428,
    FRAG = 429,
    RESERVED2 = 430,
    MORE_FRAGMENTS = 431,
    DST = 432,
    MH = 433,
    META = 434,
    MARK = 435,
    IIF = 436,
    IIFNAME = 437,
    IIFTYPE = 438,
    OIF = 439,
    OIFNAME = 440,
    OIFTYPE = 441,
    SKUID = 442,
    SKGID = 443,
    NFTRACE = 444,
    RTCLASSID = 445,
    IBRIPORT = 446,
    OBRIPORT = 447,
    PKTTYPE = 448,
    CPU = 449,
    IIFGROUP = 450,
    OIFGROUP = 451,
    CGROUP = 452,
    CLASSID = 453,
    NEXTHOP = 454,
    CT = 455,
    L3PROTOCOL = 456,
    PROTO_SRC = 457,
    PROTO_DST = 458,
    ZONE = 459,
    DIRECTION = 460,
    EVENT = 461,
    EXPIRATION = 462,
    HELPER = 463,
    LABEL = 464,
    STATE = 465,
    STATUS = 466,
    ORIGINAL = 467,
    REPLY = 468,
    COUNTER = 469,
    NAME = 470,
    PACKETS = 471,
    BYTES = 472,
    AVGPKT = 473,
    COUNTERS = 474,
    QUOTAS = 475,
    LIMITS = 476,
    HELPERS = 477,
    LOG = 478,
    PREFIX = 479,
    GROUP = 480,
    SNAPLEN = 481,
    QUEUE_THRESHOLD = 482,
    LEVEL = 483,
    LIMIT = 484,
    RATE = 485,
    BURST = 486,
    OVER = 487,
    UNTIL = 488,
    QUOTA = 489,
    USED = 490,
    NANOSECOND = 491,
    MICROSECOND = 492,
    MILLISECOND = 493,
    SECOND = 494,
    MINUTE = 495,
    HOUR = 496,
    DAY = 497,
    WEEK = 498,
    _REJECT = 499,
    WITH = 500,
    ICMPX = 501,
    SNAT = 502,
    DNAT = 503,
    MASQUERADE = 504,
    REDIRECT = 505,
    RANDOM = 506,
    FULLY_RANDOM = 507,
    PERSISTENT = 508,
    QUEUE = 509,
    QUEUENUM = 510,
    BYPASS = 511,
    FANOUT = 512,
    DUP = 513,
    FWD = 514,
    NUMGEN = 515,
    INC = 516,
    MOD = 517,
    OFFSET = 518,
    JHASH = 519,
    SYMHASH = 520,
    SEED = 521,
    POSITION = 522,
    COMMENT = 523,
    XML = 524,
    JSON = 525,
    VM = 526,
    NOTRACK = 527,
    EXISTS = 528,
    MISSING = 529,
    EXTHDR = 530
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
#define HANDLE 299
#define RULESET 300
#define TRACE 301
#define INET 302
#define NETDEV 303
#define ADD 304
#define UPDATE 305
#define REPLACE 306
#define CREATE 307
#define INSERT 308
#define DELETE 309
#define LIST 310
#define RESET 311
#define FLUSH 312
#define RENAME 313
#define DESCRIBE 314
#define IMPORT 315
#define EXPORT 316
#define MONITOR 317
#define ALL 318
#define ACCEPT 319
#define DROP 320
#define CONTINUE 321
#define JUMP 322
#define GOTO 323
#define RETURN 324
#define TO 325
#define CONSTANT 326
#define INTERVAL 327
#define AUTOMERGE 328
#define TIMEOUT 329
#define GC_INTERVAL 330
#define ELEMENTS 331
#define POLICY 332
#define MEMORY 333
#define PERFORMANCE 334
#define SIZE 335
#define FLOW 336
#define METER 337
#define METERS 338
#define NUM 339
#define STRING 340
#define QUOTED_STRING 341
#define ASTERISK_STRING 342
#define LL_HDR 343
#define NETWORK_HDR 344
#define TRANSPORT_HDR 345
#define BRIDGE 346
#define ETHER 347
#define SADDR 348
#define DADDR 349
#define TYPE 350
#define VLAN 351
#define ID 352
#define CFI 353
#define PCP 354
#define ARP 355
#define HTYPE 356
#define PTYPE 357
#define HLEN 358
#define PLEN 359
#define OPERATION 360
#define IP 361
#define HDRVERSION 362
#define HDRLENGTH 363
#define DSCP 364
#define ECN 365
#define LENGTH 366
#define FRAG_OFF 367
#define TTL 368
#define PROTOCOL 369
#define CHECKSUM 370
#define ICMP 371
#define CODE 372
#define SEQUENCE 373
#define GATEWAY 374
#define MTU 375
#define OPTIONS 376
#define IP6 377
#define PRIORITY 378
#define FLOWLABEL 379
#define NEXTHDR 380
#define HOPLIMIT 381
#define ICMP6 382
#define PPTR 383
#define MAXDELAY 384
#define AH 385
#define RESERVED 386
#define SPI 387
#define ESP 388
#define COMP 389
#define FLAGS 390
#define CPI 391
#define UDP 392
#define SPORT 393
#define DPORT 394
#define UDPLITE 395
#define CSUMCOV 396
#define TCP 397
#define ACKSEQ 398
#define DOFF 399
#define WINDOW 400
#define URGPTR 401
#define OPTION 402
#define ECHO 403
#define EOL 404
#define MAXSEG 405
#define NOOP 406
#define SACK 407
#define SACK0 408
#define SACK1 409
#define SACK2 410
#define SACK3 411
#define SACK_PERMITTED 412
#define TIMESTAMP 413
#define KIND 414
#define COUNT 415
#define LEFT 416
#define RIGHT 417
#define TSVAL 418
#define TSECR 419
#define DCCP 420
#define SCTP 421
#define VTAG 422
#define RT 423
#define RT0 424
#define RT2 425
#define SEG_LEFT 426
#define ADDR 427
#define HBH 428
#define FRAG 429
#define RESERVED2 430
#define MORE_FRAGMENTS 431
#define DST 432
#define MH 433
#define META 434
#define MARK 435
#define IIF 436
#define IIFNAME 437
#define IIFTYPE 438
#define OIF 439
#define OIFNAME 440
#define OIFTYPE 441
#define SKUID 442
#define SKGID 443
#define NFTRACE 444
#define RTCLASSID 445
#define IBRIPORT 446
#define OBRIPORT 447
#define PKTTYPE 448
#define CPU 449
#define IIFGROUP 450
#define OIFGROUP 451
#define CGROUP 452
#define CLASSID 453
#define NEXTHOP 454
#define CT 455
#define L3PROTOCOL 456
#define PROTO_SRC 457
#define PROTO_DST 458
#define ZONE 459
#define DIRECTION 460
#define EVENT 461
#define EXPIRATION 462
#define HELPER 463
#define LABEL 464
#define STATE 465
#define STATUS 466
#define ORIGINAL 467
#define REPLY 468
#define COUNTER 469
#define NAME 470
#define PACKETS 471
#define BYTES 472
#define AVGPKT 473
#define COUNTERS 474
#define QUOTAS 475
#define LIMITS 476
#define HELPERS 477
#define LOG 478
#define PREFIX 479
#define GROUP 480
#define SNAPLEN 481
#define QUEUE_THRESHOLD 482
#define LEVEL 483
#define LIMIT 484
#define RATE 485
#define BURST 486
#define OVER 487
#define UNTIL 488
#define QUOTA 489
#define USED 490
#define NANOSECOND 491
#define MICROSECOND 492
#define MILLISECOND 493
#define SECOND 494
#define MINUTE 495
#define HOUR 496
#define DAY 497
#define WEEK 498
#define _REJECT 499
#define WITH 500
#define ICMPX 501
#define SNAT 502
#define DNAT 503
#define MASQUERADE 504
#define REDIRECT 505
#define RANDOM 506
#define FULLY_RANDOM 507
#define PERSISTENT 508
#define QUEUE 509
#define QUEUENUM 510
#define BYPASS 511
#define FANOUT 512
#define DUP 513
#define FWD 514
#define NUMGEN 515
#define INC 516
#define MOD 517
#define OFFSET 518
#define JHASH 519
#define SYMHASH 520
#define SEED 521
#define POSITION 522
#define COMMENT 523
#define XML 524
#define JSON 525
#define VM 526
#define NOTRACK 527
#define EXISTS 528
#define MISSING 529
#define EXTHDR 530

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 135 "parser_bison.y" /* yacc.c:1909  */

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
	struct counter		*counter;
	struct quota		*quota;
	struct ct		*ct;
	struct limit		*limit;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	const struct exthdr_desc *exthdr_desc;

#line 630 "parser_bison.h" /* yacc.c:1909  */
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
