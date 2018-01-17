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
    FIB = 283,
    HOOK = 284,
    DEVICE = 285,
    TABLE = 286,
    TABLES = 287,
    CHAIN = 288,
    CHAINS = 289,
    RULE = 290,
    RULES = 291,
    SETS = 292,
    SET = 293,
    ELEMENT = 294,
    MAP = 295,
    MAPS = 296,
    HANDLE = 297,
    RULESET = 298,
    TRACE = 299,
    INET = 300,
    NETDEV = 301,
    ADD = 302,
    UPDATE = 303,
    REPLACE = 304,
    CREATE = 305,
    INSERT = 306,
    DELETE = 307,
    LIST = 308,
    RESET = 309,
    FLUSH = 310,
    RENAME = 311,
    DESCRIBE = 312,
    EXPORT = 313,
    MONITOR = 314,
    ALL = 315,
    ACCEPT = 316,
    DROP = 317,
    CONTINUE = 318,
    JUMP = 319,
    GOTO = 320,
    RETURN = 321,
    TO = 322,
    CONSTANT = 323,
    INTERVAL = 324,
    TIMEOUT = 325,
    GC_INTERVAL = 326,
    ELEMENTS = 327,
    POLICY = 328,
    MEMORY = 329,
    PERFORMANCE = 330,
    SIZE = 331,
    FLOW = 332,
    METER = 333,
    METERS = 334,
    NUM = 335,
    STRING = 336,
    QUOTED_STRING = 337,
    ASTERISK_STRING = 338,
    LL_HDR = 339,
    NETWORK_HDR = 340,
    TRANSPORT_HDR = 341,
    BRIDGE = 342,
    ETHER = 343,
    SADDR = 344,
    DADDR = 345,
    TYPE = 346,
    VLAN = 347,
    ID = 348,
    CFI = 349,
    PCP = 350,
    ARP = 351,
    HTYPE = 352,
    PTYPE = 353,
    HLEN = 354,
    PLEN = 355,
    OPERATION = 356,
    IP = 357,
    HDRVERSION = 358,
    HDRLENGTH = 359,
    DSCP = 360,
    ECN = 361,
    LENGTH = 362,
    FRAG_OFF = 363,
    TTL = 364,
    PROTOCOL = 365,
    CHECKSUM = 366,
    ICMP = 367,
    CODE = 368,
    SEQUENCE = 369,
    GATEWAY = 370,
    MTU = 371,
    OPTIONS = 372,
    IP6 = 373,
    PRIORITY = 374,
    FLOWLABEL = 375,
    NEXTHDR = 376,
    HOPLIMIT = 377,
    ICMP6 = 378,
    PPTR = 379,
    MAXDELAY = 380,
    AH = 381,
    RESERVED = 382,
    SPI = 383,
    ESP = 384,
    COMP = 385,
    FLAGS = 386,
    CPI = 387,
    UDP = 388,
    SPORT = 389,
    DPORT = 390,
    UDPLITE = 391,
    CSUMCOV = 392,
    TCP = 393,
    ACKSEQ = 394,
    DOFF = 395,
    WINDOW = 396,
    URGPTR = 397,
    OPTION = 398,
    ECHO = 399,
    EOL = 400,
    MAXSEG = 401,
    NOOP = 402,
    SACK = 403,
    SACK0 = 404,
    SACK1 = 405,
    SACK2 = 406,
    SACK3 = 407,
    SACK_PERMITTED = 408,
    TIMESTAMP = 409,
    KIND = 410,
    COUNT = 411,
    LEFT = 412,
    RIGHT = 413,
    TSVAL = 414,
    TSECR = 415,
    DCCP = 416,
    SCTP = 417,
    VTAG = 418,
    RT = 419,
    RT0 = 420,
    RT2 = 421,
    SEG_LEFT = 422,
    ADDR = 423,
    HBH = 424,
    FRAG = 425,
    RESERVED2 = 426,
    MORE_FRAGMENTS = 427,
    DST = 428,
    MH = 429,
    META = 430,
    MARK = 431,
    IIF = 432,
    IIFNAME = 433,
    IIFTYPE = 434,
    OIF = 435,
    OIFNAME = 436,
    OIFTYPE = 437,
    SKUID = 438,
    SKGID = 439,
    NFTRACE = 440,
    RTCLASSID = 441,
    IBRIPORT = 442,
    OBRIPORT = 443,
    PKTTYPE = 444,
    CPU = 445,
    IIFGROUP = 446,
    OIFGROUP = 447,
    CGROUP = 448,
    CLASSID = 449,
    NEXTHOP = 450,
    CT = 451,
    L3PROTOCOL = 452,
    PROTO_SRC = 453,
    PROTO_DST = 454,
    ZONE = 455,
    DIRECTION = 456,
    EVENT = 457,
    EXPIRATION = 458,
    HELPER = 459,
    LABEL = 460,
    STATE = 461,
    STATUS = 462,
    ORIGINAL = 463,
    REPLY = 464,
    COUNTER = 465,
    NAME = 466,
    PACKETS = 467,
    BYTES = 468,
    AVGPKT = 469,
    COUNTERS = 470,
    QUOTAS = 471,
    LIMITS = 472,
    HELPERS = 473,
    LOG = 474,
    PREFIX = 475,
    GROUP = 476,
    SNAPLEN = 477,
    QUEUE_THRESHOLD = 478,
    LEVEL = 479,
    LIMIT = 480,
    RATE = 481,
    BURST = 482,
    OVER = 483,
    UNTIL = 484,
    QUOTA = 485,
    USED = 486,
    NANOSECOND = 487,
    MICROSECOND = 488,
    MILLISECOND = 489,
    SECOND = 490,
    MINUTE = 491,
    HOUR = 492,
    DAY = 493,
    WEEK = 494,
    _REJECT = 495,
    WITH = 496,
    ICMPX = 497,
    SNAT = 498,
    DNAT = 499,
    MASQUERADE = 500,
    REDIRECT = 501,
    RANDOM = 502,
    FULLY_RANDOM = 503,
    PERSISTENT = 504,
    QUEUE = 505,
    QUEUENUM = 506,
    BYPASS = 507,
    FANOUT = 508,
    DUP = 509,
    FWD = 510,
    NUMGEN = 511,
    INC = 512,
    MOD = 513,
    OFFSET = 514,
    JHASH = 515,
    SYMHASH = 516,
    SEED = 517,
    POSITION = 518,
    COMMENT = 519,
    XML = 520,
    JSON = 521,
    NOTRACK = 522,
    EXISTS = 523,
    MISSING = 524,
    EXTHDR = 525
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
#define FIB 283
#define HOOK 284
#define DEVICE 285
#define TABLE 286
#define TABLES 287
#define CHAIN 288
#define CHAINS 289
#define RULE 290
#define RULES 291
#define SETS 292
#define SET 293
#define ELEMENT 294
#define MAP 295
#define MAPS 296
#define HANDLE 297
#define RULESET 298
#define TRACE 299
#define INET 300
#define NETDEV 301
#define ADD 302
#define UPDATE 303
#define REPLACE 304
#define CREATE 305
#define INSERT 306
#define DELETE 307
#define LIST 308
#define RESET 309
#define FLUSH 310
#define RENAME 311
#define DESCRIBE 312
#define EXPORT 313
#define MONITOR 314
#define ALL 315
#define ACCEPT 316
#define DROP 317
#define CONTINUE 318
#define JUMP 319
#define GOTO 320
#define RETURN 321
#define TO 322
#define CONSTANT 323
#define INTERVAL 324
#define TIMEOUT 325
#define GC_INTERVAL 326
#define ELEMENTS 327
#define POLICY 328
#define MEMORY 329
#define PERFORMANCE 330
#define SIZE 331
#define FLOW 332
#define METER 333
#define METERS 334
#define NUM 335
#define STRING 336
#define QUOTED_STRING 337
#define ASTERISK_STRING 338
#define LL_HDR 339
#define NETWORK_HDR 340
#define TRANSPORT_HDR 341
#define BRIDGE 342
#define ETHER 343
#define SADDR 344
#define DADDR 345
#define TYPE 346
#define VLAN 347
#define ID 348
#define CFI 349
#define PCP 350
#define ARP 351
#define HTYPE 352
#define PTYPE 353
#define HLEN 354
#define PLEN 355
#define OPERATION 356
#define IP 357
#define HDRVERSION 358
#define HDRLENGTH 359
#define DSCP 360
#define ECN 361
#define LENGTH 362
#define FRAG_OFF 363
#define TTL 364
#define PROTOCOL 365
#define CHECKSUM 366
#define ICMP 367
#define CODE 368
#define SEQUENCE 369
#define GATEWAY 370
#define MTU 371
#define OPTIONS 372
#define IP6 373
#define PRIORITY 374
#define FLOWLABEL 375
#define NEXTHDR 376
#define HOPLIMIT 377
#define ICMP6 378
#define PPTR 379
#define MAXDELAY 380
#define AH 381
#define RESERVED 382
#define SPI 383
#define ESP 384
#define COMP 385
#define FLAGS 386
#define CPI 387
#define UDP 388
#define SPORT 389
#define DPORT 390
#define UDPLITE 391
#define CSUMCOV 392
#define TCP 393
#define ACKSEQ 394
#define DOFF 395
#define WINDOW 396
#define URGPTR 397
#define OPTION 398
#define ECHO 399
#define EOL 400
#define MAXSEG 401
#define NOOP 402
#define SACK 403
#define SACK0 404
#define SACK1 405
#define SACK2 406
#define SACK3 407
#define SACK_PERMITTED 408
#define TIMESTAMP 409
#define KIND 410
#define COUNT 411
#define LEFT 412
#define RIGHT 413
#define TSVAL 414
#define TSECR 415
#define DCCP 416
#define SCTP 417
#define VTAG 418
#define RT 419
#define RT0 420
#define RT2 421
#define SEG_LEFT 422
#define ADDR 423
#define HBH 424
#define FRAG 425
#define RESERVED2 426
#define MORE_FRAGMENTS 427
#define DST 428
#define MH 429
#define META 430
#define MARK 431
#define IIF 432
#define IIFNAME 433
#define IIFTYPE 434
#define OIF 435
#define OIFNAME 436
#define OIFTYPE 437
#define SKUID 438
#define SKGID 439
#define NFTRACE 440
#define RTCLASSID 441
#define IBRIPORT 442
#define OBRIPORT 443
#define PKTTYPE 444
#define CPU 445
#define IIFGROUP 446
#define OIFGROUP 447
#define CGROUP 448
#define CLASSID 449
#define NEXTHOP 450
#define CT 451
#define L3PROTOCOL 452
#define PROTO_SRC 453
#define PROTO_DST 454
#define ZONE 455
#define DIRECTION 456
#define EVENT 457
#define EXPIRATION 458
#define HELPER 459
#define LABEL 460
#define STATE 461
#define STATUS 462
#define ORIGINAL 463
#define REPLY 464
#define COUNTER 465
#define NAME 466
#define PACKETS 467
#define BYTES 468
#define AVGPKT 469
#define COUNTERS 470
#define QUOTAS 471
#define LIMITS 472
#define HELPERS 473
#define LOG 474
#define PREFIX 475
#define GROUP 476
#define SNAPLEN 477
#define QUEUE_THRESHOLD 478
#define LEVEL 479
#define LIMIT 480
#define RATE 481
#define BURST 482
#define OVER 483
#define UNTIL 484
#define QUOTA 485
#define USED 486
#define NANOSECOND 487
#define MICROSECOND 488
#define MILLISECOND 489
#define SECOND 490
#define MINUTE 491
#define HOUR 492
#define DAY 493
#define WEEK 494
#define _REJECT 495
#define WITH 496
#define ICMPX 497
#define SNAT 498
#define DNAT 499
#define MASQUERADE 500
#define REDIRECT 501
#define RANDOM 502
#define FULLY_RANDOM 503
#define PERSISTENT 504
#define QUEUE 505
#define QUEUENUM 506
#define BYPASS 507
#define FANOUT 508
#define DUP 509
#define FWD 510
#define NUMGEN 511
#define INC 512
#define MOD 513
#define OFFSET 514
#define JHASH 515
#define SYMHASH 516
#define SEED 517
#define POSITION 518
#define COMMENT 519
#define XML 520
#define JSON 521
#define NOTRACK 522
#define EXISTS 523
#define MISSING 524
#define EXTHDR 525

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
	struct counter		*counter;
	struct quota		*quota;
	struct ct		*ct;
	struct limit		*limit;
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;
	const struct exthdr_desc *exthdr_desc;

#line 620 "parser_bison.h" /* yacc.c:1909  */
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
