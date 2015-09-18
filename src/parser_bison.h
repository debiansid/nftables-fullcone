/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     HANDLE = 294,
     RULESET = 295,
     INET = 296,
     NETDEV = 297,
     ADD = 298,
     UPDATE = 299,
     CREATE = 300,
     INSERT = 301,
     DELETE = 302,
     LIST = 303,
     FLUSH = 304,
     RENAME = 305,
     DESCRIBE = 306,
     EXPORT = 307,
     MONITOR = 308,
     ACCEPT = 309,
     DROP = 310,
     CONTINUE = 311,
     JUMP = 312,
     GOTO = 313,
     RETURN = 314,
     TO = 315,
     CONSTANT = 316,
     INTERVAL = 317,
     TIMEOUT = 318,
     GC_INTERVAL = 319,
     ELEMENTS = 320,
     POLICY = 321,
     MEMORY = 322,
     PERFORMANCE = 323,
     SIZE = 324,
     NUM = 325,
     STRING = 326,
     QUOTED_STRING = 327,
     LL_HDR = 328,
     NETWORK_HDR = 329,
     TRANSPORT_HDR = 330,
     BRIDGE = 331,
     ETHER = 332,
     SADDR = 333,
     DADDR = 334,
     TYPE = 335,
     VLAN = 336,
     ID = 337,
     CFI = 338,
     PCP = 339,
     ARP = 340,
     HTYPE = 341,
     PTYPE = 342,
     HLEN = 343,
     PLEN = 344,
     OPERATION = 345,
     IP = 346,
     HDRVERSION = 347,
     HDRLENGTH = 348,
     TOS = 349,
     LENGTH = 350,
     FRAG_OFF = 351,
     TTL = 352,
     PROTOCOL = 353,
     CHECKSUM = 354,
     ICMP = 355,
     CODE = 356,
     SEQUENCE = 357,
     GATEWAY = 358,
     MTU = 359,
     IP6 = 360,
     PRIORITY = 361,
     FLOWLABEL = 362,
     NEXTHDR = 363,
     HOPLIMIT = 364,
     ICMP6 = 365,
     PPTR = 366,
     MAXDELAY = 367,
     AH = 368,
     RESERVED = 369,
     SPI = 370,
     ESP = 371,
     COMP = 372,
     FLAGS = 373,
     CPI = 374,
     UDP = 375,
     SPORT = 376,
     DPORT = 377,
     UDPLITE = 378,
     CSUMCOV = 379,
     TCP = 380,
     ACKSEQ = 381,
     DOFF = 382,
     WINDOW = 383,
     URGPTR = 384,
     DCCP = 385,
     SCTP = 386,
     VTAG = 387,
     RT = 388,
     RT0 = 389,
     RT2 = 390,
     SEG_LEFT = 391,
     ADDR = 392,
     HBH = 393,
     FRAG = 394,
     RESERVED2 = 395,
     MORE_FRAGMENTS = 396,
     DST = 397,
     MH = 398,
     META = 399,
     NFPROTO = 400,
     L4PROTO = 401,
     MARK = 402,
     IIF = 403,
     IIFNAME = 404,
     IIFTYPE = 405,
     OIF = 406,
     OIFNAME = 407,
     OIFTYPE = 408,
     SKUID = 409,
     SKGID = 410,
     NFTRACE = 411,
     RTCLASSID = 412,
     IBRIPORT = 413,
     OBRIPORT = 414,
     PKTTYPE = 415,
     CPU = 416,
     IIFGROUP = 417,
     OIFGROUP = 418,
     CGROUP = 419,
     CT = 420,
     DIRECTION = 421,
     STATE = 422,
     STATUS = 423,
     EXPIRATION = 424,
     HELPER = 425,
     L3PROTOCOL = 426,
     PROTO_SRC = 427,
     PROTO_DST = 428,
     LABEL = 429,
     COUNTER = 430,
     PACKETS = 431,
     BYTES = 432,
     LOG = 433,
     PREFIX = 434,
     GROUP = 435,
     SNAPLEN = 436,
     QUEUE_THRESHOLD = 437,
     LEVEL = 438,
     LEVEL_EMERG = 439,
     LEVEL_ALERT = 440,
     LEVEL_CRIT = 441,
     LEVEL_ERR = 442,
     LEVEL_WARN = 443,
     LEVEL_NOTICE = 444,
     LEVEL_INFO = 445,
     LEVEL_DEBUG = 446,
     LIMIT = 447,
     RATE = 448,
     NANOSECOND = 449,
     MICROSECOND = 450,
     MILLISECOND = 451,
     SECOND = 452,
     MINUTE = 453,
     HOUR = 454,
     DAY = 455,
     WEEK = 456,
     _REJECT = 457,
     RESET = 458,
     WITH = 459,
     ICMPX = 460,
     SNAT = 461,
     DNAT = 462,
     MASQUERADE = 463,
     REDIRECT = 464,
     RANDOM = 465,
     FULLY_RANDOM = 466,
     PERSISTENT = 467,
     QUEUE = 468,
     QUEUENUM = 469,
     BYPASS = 470,
     FANOUT = 471,
     POSITION = 472,
     COMMENT = 473,
     XML = 474,
     JSON = 475
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
#define HANDLE 294
#define RULESET 295
#define INET 296
#define NETDEV 297
#define ADD 298
#define UPDATE 299
#define CREATE 300
#define INSERT 301
#define DELETE 302
#define LIST 303
#define FLUSH 304
#define RENAME 305
#define DESCRIBE 306
#define EXPORT 307
#define MONITOR 308
#define ACCEPT 309
#define DROP 310
#define CONTINUE 311
#define JUMP 312
#define GOTO 313
#define RETURN 314
#define TO 315
#define CONSTANT 316
#define INTERVAL 317
#define TIMEOUT 318
#define GC_INTERVAL 319
#define ELEMENTS 320
#define POLICY 321
#define MEMORY 322
#define PERFORMANCE 323
#define SIZE 324
#define NUM 325
#define STRING 326
#define QUOTED_STRING 327
#define LL_HDR 328
#define NETWORK_HDR 329
#define TRANSPORT_HDR 330
#define BRIDGE 331
#define ETHER 332
#define SADDR 333
#define DADDR 334
#define TYPE 335
#define VLAN 336
#define ID 337
#define CFI 338
#define PCP 339
#define ARP 340
#define HTYPE 341
#define PTYPE 342
#define HLEN 343
#define PLEN 344
#define OPERATION 345
#define IP 346
#define HDRVERSION 347
#define HDRLENGTH 348
#define TOS 349
#define LENGTH 350
#define FRAG_OFF 351
#define TTL 352
#define PROTOCOL 353
#define CHECKSUM 354
#define ICMP 355
#define CODE 356
#define SEQUENCE 357
#define GATEWAY 358
#define MTU 359
#define IP6 360
#define PRIORITY 361
#define FLOWLABEL 362
#define NEXTHDR 363
#define HOPLIMIT 364
#define ICMP6 365
#define PPTR 366
#define MAXDELAY 367
#define AH 368
#define RESERVED 369
#define SPI 370
#define ESP 371
#define COMP 372
#define FLAGS 373
#define CPI 374
#define UDP 375
#define SPORT 376
#define DPORT 377
#define UDPLITE 378
#define CSUMCOV 379
#define TCP 380
#define ACKSEQ 381
#define DOFF 382
#define WINDOW 383
#define URGPTR 384
#define DCCP 385
#define SCTP 386
#define VTAG 387
#define RT 388
#define RT0 389
#define RT2 390
#define SEG_LEFT 391
#define ADDR 392
#define HBH 393
#define FRAG 394
#define RESERVED2 395
#define MORE_FRAGMENTS 396
#define DST 397
#define MH 398
#define META 399
#define NFPROTO 400
#define L4PROTO 401
#define MARK 402
#define IIF 403
#define IIFNAME 404
#define IIFTYPE 405
#define OIF 406
#define OIFNAME 407
#define OIFTYPE 408
#define SKUID 409
#define SKGID 410
#define NFTRACE 411
#define RTCLASSID 412
#define IBRIPORT 413
#define OBRIPORT 414
#define PKTTYPE 415
#define CPU 416
#define IIFGROUP 417
#define OIFGROUP 418
#define CGROUP 419
#define CT 420
#define DIRECTION 421
#define STATE 422
#define STATUS 423
#define EXPIRATION 424
#define HELPER 425
#define L3PROTOCOL 426
#define PROTO_SRC 427
#define PROTO_DST 428
#define LABEL 429
#define COUNTER 430
#define PACKETS 431
#define BYTES 432
#define LOG 433
#define PREFIX 434
#define GROUP 435
#define SNAPLEN 436
#define QUEUE_THRESHOLD 437
#define LEVEL 438
#define LEVEL_EMERG 439
#define LEVEL_ALERT 440
#define LEVEL_CRIT 441
#define LEVEL_ERR 442
#define LEVEL_WARN 443
#define LEVEL_NOTICE 444
#define LEVEL_INFO 445
#define LEVEL_DEBUG 446
#define LIMIT 447
#define RATE 448
#define NANOSECOND 449
#define MICROSECOND 450
#define MILLISECOND 451
#define SECOND 452
#define MINUTE 453
#define HOUR 454
#define DAY 455
#define WEEK 456
#define _REJECT 457
#define RESET 458
#define WITH 459
#define ICMPX 460
#define SNAT 461
#define DNAT 462
#define MASQUERADE 463
#define REDIRECT 464
#define RANDOM 465
#define FULLY_RANDOM 466
#define PERSISTENT 467
#define QUEUE 468
#define QUEUENUM 469
#define BYPASS 470
#define FANOUT 471
#define POSITION 472
#define COMMENT 473
#define XML 474
#define JSON 475




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 122 "parser_bison.y"

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



/* Line 2068 of yacc.c  */
#line 510 "parser_bison.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



