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
    INCLUDE = 280,
    DEFINE = 281,
    HOOK = 282,
    DEVICE = 283,
    TABLE = 284,
    TABLES = 285,
    CHAIN = 286,
    CHAINS = 287,
    RULE = 288,
    RULES = 289,
    SETS = 290,
    SET = 291,
    ELEMENT = 292,
    MAP = 293,
    MAPS = 294,
    HANDLE = 295,
    RULESET = 296,
    INET = 297,
    NETDEV = 298,
    ADD = 299,
    UPDATE = 300,
    REPLACE = 301,
    CREATE = 302,
    INSERT = 303,
    DELETE = 304,
    LIST = 305,
    FLUSH = 306,
    RENAME = 307,
    DESCRIBE = 308,
    EXPORT = 309,
    MONITOR = 310,
    ACCEPT = 311,
    DROP = 312,
    CONTINUE = 313,
    JUMP = 314,
    GOTO = 315,
    RETURN = 316,
    TO = 317,
    CONSTANT = 318,
    INTERVAL = 319,
    TIMEOUT = 320,
    GC_INTERVAL = 321,
    ELEMENTS = 322,
    POLICY = 323,
    MEMORY = 324,
    PERFORMANCE = 325,
    SIZE = 326,
    FLOW = 327,
    NUM = 328,
    STRING = 329,
    QUOTED_STRING = 330,
    ASTERISK_STRING = 331,
    LL_HDR = 332,
    NETWORK_HDR = 333,
    TRANSPORT_HDR = 334,
    BRIDGE = 335,
    ETHER = 336,
    SADDR = 337,
    DADDR = 338,
    TYPE = 339,
    VLAN = 340,
    ID = 341,
    CFI = 342,
    PCP = 343,
    ARP = 344,
    HTYPE = 345,
    PTYPE = 346,
    HLEN = 347,
    PLEN = 348,
    OPERATION = 349,
    IP = 350,
    HDRVERSION = 351,
    HDRLENGTH = 352,
    DSCP = 353,
    ECN = 354,
    LENGTH = 355,
    FRAG_OFF = 356,
    TTL = 357,
    PROTOCOL = 358,
    CHECKSUM = 359,
    ICMP = 360,
    CODE = 361,
    SEQUENCE = 362,
    GATEWAY = 363,
    MTU = 364,
    IP6 = 365,
    PRIORITY = 366,
    FLOWLABEL = 367,
    NEXTHDR = 368,
    HOPLIMIT = 369,
    ICMP6 = 370,
    PPTR = 371,
    MAXDELAY = 372,
    AH = 373,
    RESERVED = 374,
    SPI = 375,
    ESP = 376,
    COMP = 377,
    FLAGS = 378,
    CPI = 379,
    UDP = 380,
    SPORT = 381,
    DPORT = 382,
    UDPLITE = 383,
    CSUMCOV = 384,
    TCP = 385,
    ACKSEQ = 386,
    DOFF = 387,
    WINDOW = 388,
    URGPTR = 389,
    DCCP = 390,
    SCTP = 391,
    VTAG = 392,
    RT = 393,
    RT0 = 394,
    RT2 = 395,
    SEG_LEFT = 396,
    ADDR = 397,
    HBH = 398,
    FRAG = 399,
    RESERVED2 = 400,
    MORE_FRAGMENTS = 401,
    DST = 402,
    MH = 403,
    META = 404,
    NFPROTO = 405,
    L4PROTO = 406,
    MARK = 407,
    IIF = 408,
    IIFNAME = 409,
    IIFTYPE = 410,
    OIF = 411,
    OIFNAME = 412,
    OIFTYPE = 413,
    SKUID = 414,
    SKGID = 415,
    NFTRACE = 416,
    RTCLASSID = 417,
    IBRIPORT = 418,
    OBRIPORT = 419,
    PKTTYPE = 420,
    CPU = 421,
    IIFGROUP = 422,
    OIFGROUP = 423,
    CGROUP = 424,
    CT = 425,
    DIRECTION = 426,
    STATE = 427,
    STATUS = 428,
    EXPIRATION = 429,
    HELPER = 430,
    L3PROTOCOL = 431,
    PROTO_SRC = 432,
    PROTO_DST = 433,
    LABEL = 434,
    COUNTER = 435,
    PACKETS = 436,
    BYTES = 437,
    LOG = 438,
    PREFIX = 439,
    GROUP = 440,
    SNAPLEN = 441,
    QUEUE_THRESHOLD = 442,
    LEVEL = 443,
    LEVEL_EMERG = 444,
    LEVEL_ALERT = 445,
    LEVEL_CRIT = 446,
    LEVEL_ERR = 447,
    LEVEL_WARN = 448,
    LEVEL_NOTICE = 449,
    LEVEL_INFO = 450,
    LEVEL_DEBUG = 451,
    LIMIT = 452,
    RATE = 453,
    BURST = 454,
    OVER = 455,
    UNTIL = 456,
    NANOSECOND = 457,
    MICROSECOND = 458,
    MILLISECOND = 459,
    SECOND = 460,
    MINUTE = 461,
    HOUR = 462,
    DAY = 463,
    WEEK = 464,
    _REJECT = 465,
    WITH = 466,
    ICMPX = 467,
    SNAT = 468,
    DNAT = 469,
    MASQUERADE = 470,
    REDIRECT = 471,
    RANDOM = 472,
    FULLY_RANDOM = 473,
    PERSISTENT = 474,
    QUEUE = 475,
    QUEUENUM = 476,
    BYPASS = 477,
    FANOUT = 478,
    DUP = 479,
    FWD = 480,
    POSITION = 481,
    COMMENT = 482,
    XML = 483,
    JSON = 484
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
#define HOOK 282
#define DEVICE 283
#define TABLE 284
#define TABLES 285
#define CHAIN 286
#define CHAINS 287
#define RULE 288
#define RULES 289
#define SETS 290
#define SET 291
#define ELEMENT 292
#define MAP 293
#define MAPS 294
#define HANDLE 295
#define RULESET 296
#define INET 297
#define NETDEV 298
#define ADD 299
#define UPDATE 300
#define REPLACE 301
#define CREATE 302
#define INSERT 303
#define DELETE 304
#define LIST 305
#define FLUSH 306
#define RENAME 307
#define DESCRIBE 308
#define EXPORT 309
#define MONITOR 310
#define ACCEPT 311
#define DROP 312
#define CONTINUE 313
#define JUMP 314
#define GOTO 315
#define RETURN 316
#define TO 317
#define CONSTANT 318
#define INTERVAL 319
#define TIMEOUT 320
#define GC_INTERVAL 321
#define ELEMENTS 322
#define POLICY 323
#define MEMORY 324
#define PERFORMANCE 325
#define SIZE 326
#define FLOW 327
#define NUM 328
#define STRING 329
#define QUOTED_STRING 330
#define ASTERISK_STRING 331
#define LL_HDR 332
#define NETWORK_HDR 333
#define TRANSPORT_HDR 334
#define BRIDGE 335
#define ETHER 336
#define SADDR 337
#define DADDR 338
#define TYPE 339
#define VLAN 340
#define ID 341
#define CFI 342
#define PCP 343
#define ARP 344
#define HTYPE 345
#define PTYPE 346
#define HLEN 347
#define PLEN 348
#define OPERATION 349
#define IP 350
#define HDRVERSION 351
#define HDRLENGTH 352
#define DSCP 353
#define ECN 354
#define LENGTH 355
#define FRAG_OFF 356
#define TTL 357
#define PROTOCOL 358
#define CHECKSUM 359
#define ICMP 360
#define CODE 361
#define SEQUENCE 362
#define GATEWAY 363
#define MTU 364
#define IP6 365
#define PRIORITY 366
#define FLOWLABEL 367
#define NEXTHDR 368
#define HOPLIMIT 369
#define ICMP6 370
#define PPTR 371
#define MAXDELAY 372
#define AH 373
#define RESERVED 374
#define SPI 375
#define ESP 376
#define COMP 377
#define FLAGS 378
#define CPI 379
#define UDP 380
#define SPORT 381
#define DPORT 382
#define UDPLITE 383
#define CSUMCOV 384
#define TCP 385
#define ACKSEQ 386
#define DOFF 387
#define WINDOW 388
#define URGPTR 389
#define DCCP 390
#define SCTP 391
#define VTAG 392
#define RT 393
#define RT0 394
#define RT2 395
#define SEG_LEFT 396
#define ADDR 397
#define HBH 398
#define FRAG 399
#define RESERVED2 400
#define MORE_FRAGMENTS 401
#define DST 402
#define MH 403
#define META 404
#define NFPROTO 405
#define L4PROTO 406
#define MARK 407
#define IIF 408
#define IIFNAME 409
#define IIFTYPE 410
#define OIF 411
#define OIFNAME 412
#define OIFTYPE 413
#define SKUID 414
#define SKGID 415
#define NFTRACE 416
#define RTCLASSID 417
#define IBRIPORT 418
#define OBRIPORT 419
#define PKTTYPE 420
#define CPU 421
#define IIFGROUP 422
#define OIFGROUP 423
#define CGROUP 424
#define CT 425
#define DIRECTION 426
#define STATE 427
#define STATUS 428
#define EXPIRATION 429
#define HELPER 430
#define L3PROTOCOL 431
#define PROTO_SRC 432
#define PROTO_DST 433
#define LABEL 434
#define COUNTER 435
#define PACKETS 436
#define BYTES 437
#define LOG 438
#define PREFIX 439
#define GROUP 440
#define SNAPLEN 441
#define QUEUE_THRESHOLD 442
#define LEVEL 443
#define LEVEL_EMERG 444
#define LEVEL_ALERT 445
#define LEVEL_CRIT 446
#define LEVEL_ERR 447
#define LEVEL_WARN 448
#define LEVEL_NOTICE 449
#define LEVEL_INFO 450
#define LEVEL_DEBUG 451
#define LIMIT 452
#define RATE 453
#define BURST 454
#define OVER 455
#define UNTIL 456
#define NANOSECOND 457
#define MICROSECOND 458
#define MILLISECOND 459
#define SECOND 460
#define MINUTE 461
#define HOUR 462
#define DAY 463
#define WEEK 464
#define _REJECT 465
#define WITH 466
#define ICMPX 467
#define SNAT 468
#define DNAT 469
#define MASQUERADE 470
#define REDIRECT 471
#define RANDOM 472
#define FULLY_RANDOM 473
#define PERSISTENT 474
#define QUEUE 475
#define QUEUENUM 476
#define BYPASS 477
#define FANOUT 478
#define DUP 479
#define FWD 480
#define POSITION 481
#define COMMENT 482
#define XML 483
#define JSON 484

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 122 "parser_bison.y" /* yacc.c:1909  */

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

#line 532 "parser_bison.h" /* yacc.c:1909  */
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
