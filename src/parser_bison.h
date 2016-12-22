/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    INET = 299,
    NETDEV = 300,
    ADD = 301,
    UPDATE = 302,
    REPLACE = 303,
    CREATE = 304,
    INSERT = 305,
    DELETE = 306,
    LIST = 307,
    FLUSH = 308,
    RENAME = 309,
    DESCRIBE = 310,
    EXPORT = 311,
    MONITOR = 312,
    ALL = 313,
    ACCEPT = 314,
    DROP = 315,
    CONTINUE = 316,
    JUMP = 317,
    GOTO = 318,
    RETURN = 319,
    TO = 320,
    CONSTANT = 321,
    INTERVAL = 322,
    TIMEOUT = 323,
    GC_INTERVAL = 324,
    ELEMENTS = 325,
    POLICY = 326,
    MEMORY = 327,
    PERFORMANCE = 328,
    SIZE = 329,
    FLOW = 330,
    NUM = 331,
    STRING = 332,
    QUOTED_STRING = 333,
    ASTERISK_STRING = 334,
    LL_HDR = 335,
    NETWORK_HDR = 336,
    TRANSPORT_HDR = 337,
    BRIDGE = 338,
    ETHER = 339,
    SADDR = 340,
    DADDR = 341,
    TYPE = 342,
    VLAN = 343,
    ID = 344,
    CFI = 345,
    PCP = 346,
    ARP = 347,
    HTYPE = 348,
    PTYPE = 349,
    HLEN = 350,
    PLEN = 351,
    OPERATION = 352,
    IP = 353,
    HDRVERSION = 354,
    HDRLENGTH = 355,
    DSCP = 356,
    ECN = 357,
    LENGTH = 358,
    FRAG_OFF = 359,
    TTL = 360,
    PROTOCOL = 361,
    CHECKSUM = 362,
    ICMP = 363,
    CODE = 364,
    SEQUENCE = 365,
    GATEWAY = 366,
    MTU = 367,
    OPTIONS = 368,
    IP6 = 369,
    PRIORITY = 370,
    FLOWLABEL = 371,
    NEXTHDR = 372,
    HOPLIMIT = 373,
    ICMP6 = 374,
    PPTR = 375,
    MAXDELAY = 376,
    AH = 377,
    RESERVED = 378,
    SPI = 379,
    ESP = 380,
    COMP = 381,
    FLAGS = 382,
    CPI = 383,
    UDP = 384,
    SPORT = 385,
    DPORT = 386,
    UDPLITE = 387,
    CSUMCOV = 388,
    TCP = 389,
    ACKSEQ = 390,
    DOFF = 391,
    WINDOW = 392,
    URGPTR = 393,
    DCCP = 394,
    SCTP = 395,
    VTAG = 396,
    RT = 397,
    RT0 = 398,
    RT2 = 399,
    SEG_LEFT = 400,
    ADDR = 401,
    HBH = 402,
    FRAG = 403,
    RESERVED2 = 404,
    MORE_FRAGMENTS = 405,
    DST = 406,
    MH = 407,
    META = 408,
    MARK = 409,
    IIF = 410,
    IIFNAME = 411,
    IIFTYPE = 412,
    OIF = 413,
    OIFNAME = 414,
    OIFTYPE = 415,
    SKUID = 416,
    SKGID = 417,
    NFTRACE = 418,
    RTCLASSID = 419,
    IBRIPORT = 420,
    OBRIPORT = 421,
    PKTTYPE = 422,
    CPU = 423,
    IIFGROUP = 424,
    OIFGROUP = 425,
    CGROUP = 426,
    CLASSID = 427,
    NEXTHOP = 428,
    CT = 429,
    DIRECTION = 430,
    STATE = 431,
    STATUS = 432,
    EXPIRATION = 433,
    HELPER = 434,
    L3PROTOCOL = 435,
    PROTO_SRC = 436,
    PROTO_DST = 437,
    LABEL = 438,
    COUNTER = 439,
    PACKETS = 440,
    BYTES = 441,
    LOG = 442,
    PREFIX = 443,
    GROUP = 444,
    SNAPLEN = 445,
    QUEUE_THRESHOLD = 446,
    LEVEL = 447,
    LIMIT = 448,
    RATE = 449,
    BURST = 450,
    OVER = 451,
    UNTIL = 452,
    QUOTA = 453,
    NANOSECOND = 454,
    MICROSECOND = 455,
    MILLISECOND = 456,
    SECOND = 457,
    MINUTE = 458,
    HOUR = 459,
    DAY = 460,
    WEEK = 461,
    _REJECT = 462,
    WITH = 463,
    ICMPX = 464,
    SNAT = 465,
    DNAT = 466,
    MASQUERADE = 467,
    REDIRECT = 468,
    RANDOM = 469,
    FULLY_RANDOM = 470,
    PERSISTENT = 471,
    QUEUE = 472,
    QUEUENUM = 473,
    BYPASS = 474,
    FANOUT = 475,
    DUP = 476,
    FWD = 477,
    NUMGEN = 478,
    INC = 479,
    MOD = 480,
    OFFSET = 481,
    JHASH = 482,
    SEED = 483,
    POSITION = 484,
    COMMENT = 485,
    XML = 486,
    JSON = 487,
    NOTRACK = 488
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
#define INET 299
#define NETDEV 300
#define ADD 301
#define UPDATE 302
#define REPLACE 303
#define CREATE 304
#define INSERT 305
#define DELETE 306
#define LIST 307
#define FLUSH 308
#define RENAME 309
#define DESCRIBE 310
#define EXPORT 311
#define MONITOR 312
#define ALL 313
#define ACCEPT 314
#define DROP 315
#define CONTINUE 316
#define JUMP 317
#define GOTO 318
#define RETURN 319
#define TO 320
#define CONSTANT 321
#define INTERVAL 322
#define TIMEOUT 323
#define GC_INTERVAL 324
#define ELEMENTS 325
#define POLICY 326
#define MEMORY 327
#define PERFORMANCE 328
#define SIZE 329
#define FLOW 330
#define NUM 331
#define STRING 332
#define QUOTED_STRING 333
#define ASTERISK_STRING 334
#define LL_HDR 335
#define NETWORK_HDR 336
#define TRANSPORT_HDR 337
#define BRIDGE 338
#define ETHER 339
#define SADDR 340
#define DADDR 341
#define TYPE 342
#define VLAN 343
#define ID 344
#define CFI 345
#define PCP 346
#define ARP 347
#define HTYPE 348
#define PTYPE 349
#define HLEN 350
#define PLEN 351
#define OPERATION 352
#define IP 353
#define HDRVERSION 354
#define HDRLENGTH 355
#define DSCP 356
#define ECN 357
#define LENGTH 358
#define FRAG_OFF 359
#define TTL 360
#define PROTOCOL 361
#define CHECKSUM 362
#define ICMP 363
#define CODE 364
#define SEQUENCE 365
#define GATEWAY 366
#define MTU 367
#define OPTIONS 368
#define IP6 369
#define PRIORITY 370
#define FLOWLABEL 371
#define NEXTHDR 372
#define HOPLIMIT 373
#define ICMP6 374
#define PPTR 375
#define MAXDELAY 376
#define AH 377
#define RESERVED 378
#define SPI 379
#define ESP 380
#define COMP 381
#define FLAGS 382
#define CPI 383
#define UDP 384
#define SPORT 385
#define DPORT 386
#define UDPLITE 387
#define CSUMCOV 388
#define TCP 389
#define ACKSEQ 390
#define DOFF 391
#define WINDOW 392
#define URGPTR 393
#define DCCP 394
#define SCTP 395
#define VTAG 396
#define RT 397
#define RT0 398
#define RT2 399
#define SEG_LEFT 400
#define ADDR 401
#define HBH 402
#define FRAG 403
#define RESERVED2 404
#define MORE_FRAGMENTS 405
#define DST 406
#define MH 407
#define META 408
#define MARK 409
#define IIF 410
#define IIFNAME 411
#define IIFTYPE 412
#define OIF 413
#define OIFNAME 414
#define OIFTYPE 415
#define SKUID 416
#define SKGID 417
#define NFTRACE 418
#define RTCLASSID 419
#define IBRIPORT 420
#define OBRIPORT 421
#define PKTTYPE 422
#define CPU 423
#define IIFGROUP 424
#define OIFGROUP 425
#define CGROUP 426
#define CLASSID 427
#define NEXTHOP 428
#define CT 429
#define DIRECTION 430
#define STATE 431
#define STATUS 432
#define EXPIRATION 433
#define HELPER 434
#define L3PROTOCOL 435
#define PROTO_SRC 436
#define PROTO_DST 437
#define LABEL 438
#define COUNTER 439
#define PACKETS 440
#define BYTES 441
#define LOG 442
#define PREFIX 443
#define GROUP 444
#define SNAPLEN 445
#define QUEUE_THRESHOLD 446
#define LEVEL 447
#define LIMIT 448
#define RATE 449
#define BURST 450
#define OVER 451
#define UNTIL 452
#define QUOTA 453
#define NANOSECOND 454
#define MICROSECOND 455
#define MILLISECOND 456
#define SECOND 457
#define MINUTE 458
#define HOUR 459
#define DAY 460
#define WEEK 461
#define _REJECT 462
#define WITH 463
#define ICMPX 464
#define SNAT 465
#define DNAT 466
#define MASQUERADE 467
#define REDIRECT 468
#define RANDOM 469
#define FULLY_RANDOM 470
#define PERSISTENT 471
#define QUEUE 472
#define QUEUENUM 473
#define BYPASS 474
#define FANOUT 475
#define DUP 476
#define FWD 477
#define NUMGEN 478
#define INC 479
#define MOD 480
#define OFFSET 481
#define JHASH 482
#define SEED 483
#define POSITION 484
#define COMMENT 485
#define XML 486
#define JSON 487
#define NOTRACK 488

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 123 "parser_bison.y" /* yacc.c:1909  */

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
	const struct datatype	*datatype;
	struct handle_spec	handle_spec;
	struct position_spec	position_spec;

#line 540 "parser_bison.h" /* yacc.c:1909  */
};
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



int nft_parse (void *scanner, struct parser_state *state);

#endif /* !YY_NFT_PARSER_BISON_H_INCLUDED  */
