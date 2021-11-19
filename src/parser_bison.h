/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_NFT_PARSER_BISON_H_INCLUDED
# define YY_NFT_PARSER_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int nft_debug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    TOKEN_EOF = 0,                 /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    JUNK = 258,                    /* "junk"  */
    NEWLINE = 259,                 /* "newline"  */
    COLON = 260,                   /* "colon"  */
    SEMICOLON = 261,               /* "semicolon"  */
    COMMA = 262,                   /* "comma"  */
    DOT = 263,                     /* "."  */
    EQ = 264,                      /* "=="  */
    NEQ = 265,                     /* "!="  */
    LT = 266,                      /* "<"  */
    GT = 267,                      /* ">"  */
    GTE = 268,                     /* ">="  */
    LTE = 269,                     /* "<="  */
    LSHIFT = 270,                  /* "<<"  */
    RSHIFT = 271,                  /* ">>"  */
    AMPERSAND = 272,               /* "&"  */
    CARET = 273,                   /* "^"  */
    NOT = 274,                     /* "!"  */
    SLASH = 275,                   /* "/"  */
    ASTERISK = 276,                /* "*"  */
    DASH = 277,                    /* "-"  */
    AT = 278,                      /* "@"  */
    VMAP = 279,                    /* "vmap"  */
    PLUS = 280,                    /* "+"  */
    INCLUDE = 281,                 /* "include"  */
    DEFINE = 282,                  /* "define"  */
    REDEFINE = 283,                /* "redefine"  */
    UNDEFINE = 284,                /* "undefine"  */
    FIB = 285,                     /* "fib"  */
    SOCKET = 286,                  /* "socket"  */
    TRANSPARENT = 287,             /* "transparent"  */
    WILDCARD = 288,                /* "wildcard"  */
    CGROUPV2 = 289,                /* "cgroupv2"  */
    TPROXY = 290,                  /* "tproxy"  */
    OSF = 291,                     /* "osf"  */
    SYNPROXY = 292,                /* "synproxy"  */
    MSS = 293,                     /* "mss"  */
    WSCALE = 294,                  /* "wscale"  */
    TYPEOF = 295,                  /* "typeof"  */
    HOOK = 296,                    /* "hook"  */
    HOOKS = 297,                   /* "hooks"  */
    DEVICE = 298,                  /* "device"  */
    DEVICES = 299,                 /* "devices"  */
    TABLE = 300,                   /* "table"  */
    TABLES = 301,                  /* "tables"  */
    CHAIN = 302,                   /* "chain"  */
    CHAINS = 303,                  /* "chains"  */
    RULE = 304,                    /* "rule"  */
    RULES = 305,                   /* "rules"  */
    SETS = 306,                    /* "sets"  */
    SET = 307,                     /* "set"  */
    ELEMENT = 308,                 /* "element"  */
    MAP = 309,                     /* "map"  */
    MAPS = 310,                    /* "maps"  */
    FLOWTABLE = 311,               /* "flowtable"  */
    HANDLE = 312,                  /* "handle"  */
    RULESET = 313,                 /* "ruleset"  */
    TRACE = 314,                   /* "trace"  */
    INET = 315,                    /* "inet"  */
    NETDEV = 316,                  /* "netdev"  */
    ADD = 317,                     /* "add"  */
    UPDATE = 318,                  /* "update"  */
    REPLACE = 319,                 /* "replace"  */
    CREATE = 320,                  /* "create"  */
    INSERT = 321,                  /* "insert"  */
    DELETE = 322,                  /* "delete"  */
    GET = 323,                     /* "get"  */
    LIST = 324,                    /* "list"  */
    RESET = 325,                   /* "reset"  */
    FLUSH = 326,                   /* "flush"  */
    RENAME = 327,                  /* "rename"  */
    DESCRIBE = 328,                /* "describe"  */
    IMPORT = 329,                  /* "import"  */
    EXPORT = 330,                  /* "export"  */
    MONITOR = 331,                 /* "monitor"  */
    ALL = 332,                     /* "all"  */
    ACCEPT = 333,                  /* "accept"  */
    DROP = 334,                    /* "drop"  */
    CONTINUE = 335,                /* "continue"  */
    JUMP = 336,                    /* "jump"  */
    GOTO = 337,                    /* "goto"  */
    RETURN = 338,                  /* "return"  */
    TO = 339,                      /* "to"  */
    CONSTANT = 340,                /* "constant"  */
    INTERVAL = 341,                /* "interval"  */
    DYNAMIC = 342,                 /* "dynamic"  */
    AUTOMERGE = 343,               /* "auto-merge"  */
    TIMEOUT = 344,                 /* "timeout"  */
    GC_INTERVAL = 345,             /* "gc-interval"  */
    ELEMENTS = 346,                /* "elements"  */
    EXPIRES = 347,                 /* "expires"  */
    POLICY = 348,                  /* "policy"  */
    MEMORY = 349,                  /* "memory"  */
    PERFORMANCE = 350,             /* "performance"  */
    SIZE = 351,                    /* "size"  */
    FLOW = 352,                    /* "flow"  */
    OFFLOAD = 353,                 /* "offload"  */
    METER = 354,                   /* "meter"  */
    METERS = 355,                  /* "meters"  */
    FLOWTABLES = 356,              /* "flowtables"  */
    NUM = 357,                     /* "number"  */
    STRING = 358,                  /* "string"  */
    QUOTED_STRING = 359,           /* "quoted string"  */
    ASTERISK_STRING = 360,         /* "string with a trailing asterisk"  */
    LL_HDR = 361,                  /* "ll"  */
    NETWORK_HDR = 362,             /* "nh"  */
    TRANSPORT_HDR = 363,           /* "th"  */
    BRIDGE = 364,                  /* "bridge"  */
    ETHER = 365,                   /* "ether"  */
    SADDR = 366,                   /* "saddr"  */
    DADDR = 367,                   /* "daddr"  */
    TYPE = 368,                    /* "type"  */
    VLAN = 369,                    /* "vlan"  */
    ID = 370,                      /* "id"  */
    CFI = 371,                     /* "cfi"  */
    DEI = 372,                     /* "dei"  */
    PCP = 373,                     /* "pcp"  */
    ARP = 374,                     /* "arp"  */
    HTYPE = 375,                   /* "htype"  */
    PTYPE = 376,                   /* "ptype"  */
    HLEN = 377,                    /* "hlen"  */
    PLEN = 378,                    /* "plen"  */
    OPERATION = 379,               /* "operation"  */
    IP = 380,                      /* "ip"  */
    HDRVERSION = 381,              /* "version"  */
    HDRLENGTH = 382,               /* "hdrlength"  */
    DSCP = 383,                    /* "dscp"  */
    ECN = 384,                     /* "ecn"  */
    LENGTH = 385,                  /* "length"  */
    FRAG_OFF = 386,                /* "frag-off"  */
    TTL = 387,                     /* "ttl"  */
    PROTOCOL = 388,                /* "protocol"  */
    CHECKSUM = 389,                /* "checksum"  */
    PTR = 390,                     /* "ptr"  */
    VALUE = 391,                   /* "value"  */
    LSRR = 392,                    /* "lsrr"  */
    RR = 393,                      /* "rr"  */
    SSRR = 394,                    /* "ssrr"  */
    RA = 395,                      /* "ra"  */
    ICMP = 396,                    /* "icmp"  */
    CODE = 397,                    /* "code"  */
    SEQUENCE = 398,                /* "seq"  */
    GATEWAY = 399,                 /* "gateway"  */
    MTU = 400,                     /* "mtu"  */
    IGMP = 401,                    /* "igmp"  */
    MRT = 402,                     /* "mrt"  */
    OPTIONS = 403,                 /* "options"  */
    IP6 = 404,                     /* "ip6"  */
    PRIORITY = 405,                /* "priority"  */
    FLOWLABEL = 406,               /* "flowlabel"  */
    NEXTHDR = 407,                 /* "nexthdr"  */
    HOPLIMIT = 408,                /* "hoplimit"  */
    ICMP6 = 409,                   /* "icmpv6"  */
    PPTR = 410,                    /* "param-problem"  */
    MAXDELAY = 411,                /* "max-delay"  */
    AH = 412,                      /* "ah"  */
    RESERVED = 413,                /* "reserved"  */
    SPI = 414,                     /* "spi"  */
    ESP = 415,                     /* "esp"  */
    COMP = 416,                    /* "comp"  */
    FLAGS = 417,                   /* "flags"  */
    CPI = 418,                     /* "cpi"  */
    PORT = 419,                    /* "port"  */
    UDP = 420,                     /* "udp"  */
    SPORT = 421,                   /* "sport"  */
    DPORT = 422,                   /* "dport"  */
    UDPLITE = 423,                 /* "udplite"  */
    CSUMCOV = 424,                 /* "csumcov"  */
    TCP = 425,                     /* "tcp"  */
    ACKSEQ = 426,                  /* "ackseq"  */
    DOFF = 427,                    /* "doff"  */
    WINDOW = 428,                  /* "window"  */
    URGPTR = 429,                  /* "urgptr"  */
    OPTION = 430,                  /* "option"  */
    ECHO = 431,                    /* "echo"  */
    EOL = 432,                     /* "eol"  */
    NOP = 433,                     /* "nop"  */
    SACK = 434,                    /* "sack"  */
    SACK0 = 435,                   /* "sack0"  */
    SACK1 = 436,                   /* "sack1"  */
    SACK2 = 437,                   /* "sack2"  */
    SACK3 = 438,                   /* "sack3"  */
    SACK_PERM = 439,               /* "sack-permitted"  */
    TIMESTAMP = 440,               /* "timestamp"  */
    KIND = 441,                    /* "kind"  */
    COUNT = 442,                   /* "count"  */
    LEFT = 443,                    /* "left"  */
    RIGHT = 444,                   /* "right"  */
    TSVAL = 445,                   /* "tsval"  */
    TSECR = 446,                   /* "tsecr"  */
    DCCP = 447,                    /* "dccp"  */
    SCTP = 448,                    /* "sctp"  */
    CHUNK = 449,                   /* "chunk"  */
    DATA = 450,                    /* "data"  */
    INIT = 451,                    /* "init"  */
    INIT_ACK = 452,                /* "init-ack"  */
    HEARTBEAT = 453,               /* "heartbeat"  */
    HEARTBEAT_ACK = 454,           /* "heartbeat-ack"  */
    ABORT = 455,                   /* "abort"  */
    SHUTDOWN = 456,                /* "shutdown"  */
    SHUTDOWN_ACK = 457,            /* "shutdown-ack"  */
    ERROR = 458,                   /* "error"  */
    COOKIE_ECHO = 459,             /* "cookie-echo"  */
    COOKIE_ACK = 460,              /* "cookie-ack"  */
    ECNE = 461,                    /* "ecne"  */
    CWR = 462,                     /* "cwr"  */
    SHUTDOWN_COMPLETE = 463,       /* "shutdown-complete"  */
    ASCONF_ACK = 464,              /* "asconf-ack"  */
    FORWARD_TSN = 465,             /* "forward-tsn"  */
    ASCONF = 466,                  /* "asconf"  */
    TSN = 467,                     /* "tsn"  */
    STREAM = 468,                  /* "stream"  */
    SSN = 469,                     /* "ssn"  */
    PPID = 470,                    /* "ppid"  */
    INIT_TAG = 471,                /* "init-tag"  */
    A_RWND = 472,                  /* "a-rwnd"  */
    NUM_OSTREAMS = 473,            /* "num-outbound-streams"  */
    NUM_ISTREAMS = 474,            /* "num-inbound-streams"  */
    INIT_TSN = 475,                /* "initial-tsn"  */
    CUM_TSN_ACK = 476,             /* "cum-tsn-ack"  */
    NUM_GACK_BLOCKS = 477,         /* "num-gap-ack-blocks"  */
    NUM_DUP_TSNS = 478,            /* "num-dup-tsns"  */
    LOWEST_TSN = 479,              /* "lowest-tsn"  */
    SEQNO = 480,                   /* "seqno"  */
    NEW_CUM_TSN = 481,             /* "new-cum-tsn"  */
    VTAG = 482,                    /* "vtag"  */
    RT = 483,                      /* "rt"  */
    RT0 = 484,                     /* "rt0"  */
    RT2 = 485,                     /* "rt2"  */
    RT4 = 486,                     /* "srh"  */
    SEG_LEFT = 487,                /* "seg-left"  */
    ADDR = 488,                    /* "addr"  */
    LAST_ENT = 489,                /* "last-entry"  */
    TAG = 490,                     /* "tag"  */
    SID = 491,                     /* "sid"  */
    HBH = 492,                     /* "hbh"  */
    FRAG = 493,                    /* "frag"  */
    RESERVED2 = 494,               /* "reserved2"  */
    MORE_FRAGMENTS = 495,          /* "more-fragments"  */
    DST = 496,                     /* "dst"  */
    MH = 497,                      /* "mh"  */
    META = 498,                    /* "meta"  */
    MARK = 499,                    /* "mark"  */
    IIF = 500,                     /* "iif"  */
    IIFNAME = 501,                 /* "iifname"  */
    IIFTYPE = 502,                 /* "iiftype"  */
    OIF = 503,                     /* "oif"  */
    OIFNAME = 504,                 /* "oifname"  */
    OIFTYPE = 505,                 /* "oiftype"  */
    SKUID = 506,                   /* "skuid"  */
    SKGID = 507,                   /* "skgid"  */
    NFTRACE = 508,                 /* "nftrace"  */
    RTCLASSID = 509,               /* "rtclassid"  */
    IBRIPORT = 510,                /* "ibriport"  */
    OBRIPORT = 511,                /* "obriport"  */
    IBRIDGENAME = 512,             /* "ibrname"  */
    OBRIDGENAME = 513,             /* "obrname"  */
    PKTTYPE = 514,                 /* "pkttype"  */
    CPU = 515,                     /* "cpu"  */
    IIFGROUP = 516,                /* "iifgroup"  */
    OIFGROUP = 517,                /* "oifgroup"  */
    CGROUP = 518,                  /* "cgroup"  */
    TIME = 519,                    /* "time"  */
    CLASSID = 520,                 /* "classid"  */
    NEXTHOP = 521,                 /* "nexthop"  */
    CT = 522,                      /* "ct"  */
    L3PROTOCOL = 523,              /* "l3proto"  */
    PROTO_SRC = 524,               /* "proto-src"  */
    PROTO_DST = 525,               /* "proto-dst"  */
    ZONE = 526,                    /* "zone"  */
    DIRECTION = 527,               /* "direction"  */
    EVENT = 528,                   /* "event"  */
    EXPECTATION = 529,             /* "expectation"  */
    EXPIRATION = 530,              /* "expiration"  */
    HELPER = 531,                  /* "helper"  */
    LABEL = 532,                   /* "label"  */
    STATE = 533,                   /* "state"  */
    STATUS = 534,                  /* "status"  */
    ORIGINAL = 535,                /* "original"  */
    REPLY = 536,                   /* "reply"  */
    COUNTER = 537,                 /* "counter"  */
    NAME = 538,                    /* "name"  */
    PACKETS = 539,                 /* "packets"  */
    BYTES = 540,                   /* "bytes"  */
    AVGPKT = 541,                  /* "avgpkt"  */
    COUNTERS = 542,                /* "counters"  */
    QUOTAS = 543,                  /* "quotas"  */
    LIMITS = 544,                  /* "limits"  */
    SYNPROXYS = 545,               /* "synproxys"  */
    HELPERS = 546,                 /* "helpers"  */
    LOG = 547,                     /* "log"  */
    PREFIX = 548,                  /* "prefix"  */
    GROUP = 549,                   /* "group"  */
    SNAPLEN = 550,                 /* "snaplen"  */
    QUEUE_THRESHOLD = 551,         /* "queue-threshold"  */
    LEVEL = 552,                   /* "level"  */
    LIMIT = 553,                   /* "limit"  */
    RATE = 554,                    /* "rate"  */
    BURST = 555,                   /* "burst"  */
    OVER = 556,                    /* "over"  */
    UNTIL = 557,                   /* "until"  */
    QUOTA = 558,                   /* "quota"  */
    USED = 559,                    /* "used"  */
    SECMARK = 560,                 /* "secmark"  */
    SECMARKS = 561,                /* "secmarks"  */
    SECOND = 562,                  /* "second"  */
    MINUTE = 563,                  /* "minute"  */
    HOUR = 564,                    /* "hour"  */
    DAY = 565,                     /* "day"  */
    WEEK = 566,                    /* "week"  */
    _REJECT = 567,                 /* "reject"  */
    WITH = 568,                    /* "with"  */
    ICMPX = 569,                   /* "icmpx"  */
    SNAT = 570,                    /* "snat"  */
    DNAT = 571,                    /* "dnat"  */
    MASQUERADE = 572,              /* "masquerade"  */
    REDIRECT = 573,                /* "redirect"  */
    RANDOM = 574,                  /* "random"  */
    FULLY_RANDOM = 575,            /* "fully-random"  */
    PERSISTENT = 576,              /* "persistent"  */
    QUEUE = 577,                   /* "queue"  */
    QUEUENUM = 578,                /* "num"  */
    BYPASS = 579,                  /* "bypass"  */
    FANOUT = 580,                  /* "fanout"  */
    DUP = 581,                     /* "dup"  */
    FWD = 582,                     /* "fwd"  */
    NUMGEN = 583,                  /* "numgen"  */
    INC = 584,                     /* "inc"  */
    MOD = 585,                     /* "mod"  */
    OFFSET = 586,                  /* "offset"  */
    JHASH = 587,                   /* "jhash"  */
    SYMHASH = 588,                 /* "symhash"  */
    SEED = 589,                    /* "seed"  */
    POSITION = 590,                /* "position"  */
    INDEX = 591,                   /* "index"  */
    COMMENT = 592,                 /* "comment"  */
    XML = 593,                     /* "xml"  */
    JSON = 594,                    /* "json"  */
    VM = 595,                      /* "vm"  */
    NOTRACK = 596,                 /* "notrack"  */
    EXISTS = 597,                  /* "exists"  */
    MISSING = 598,                 /* "missing"  */
    EXTHDR = 599,                  /* "exthdr"  */
    IPSEC = 600,                   /* "ipsec"  */
    REQID = 601,                   /* "reqid"  */
    SPNUM = 602,                   /* "spnum"  */
    IN = 603,                      /* "in"  */
    OUT = 604                      /* "out"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define TOKEN_EOF 0
#define YYerror 256
#define YYUNDEF 257
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
#define CGROUPV2 289
#define TPROXY 290
#define OSF 291
#define SYNPROXY 292
#define MSS 293
#define WSCALE 294
#define TYPEOF 295
#define HOOK 296
#define HOOKS 297
#define DEVICE 298
#define DEVICES 299
#define TABLE 300
#define TABLES 301
#define CHAIN 302
#define CHAINS 303
#define RULE 304
#define RULES 305
#define SETS 306
#define SET 307
#define ELEMENT 308
#define MAP 309
#define MAPS 310
#define FLOWTABLE 311
#define HANDLE 312
#define RULESET 313
#define TRACE 314
#define INET 315
#define NETDEV 316
#define ADD 317
#define UPDATE 318
#define REPLACE 319
#define CREATE 320
#define INSERT 321
#define DELETE 322
#define GET 323
#define LIST 324
#define RESET 325
#define FLUSH 326
#define RENAME 327
#define DESCRIBE 328
#define IMPORT 329
#define EXPORT 330
#define MONITOR 331
#define ALL 332
#define ACCEPT 333
#define DROP 334
#define CONTINUE 335
#define JUMP 336
#define GOTO 337
#define RETURN 338
#define TO 339
#define CONSTANT 340
#define INTERVAL 341
#define DYNAMIC 342
#define AUTOMERGE 343
#define TIMEOUT 344
#define GC_INTERVAL 345
#define ELEMENTS 346
#define EXPIRES 347
#define POLICY 348
#define MEMORY 349
#define PERFORMANCE 350
#define SIZE 351
#define FLOW 352
#define OFFLOAD 353
#define METER 354
#define METERS 355
#define FLOWTABLES 356
#define NUM 357
#define STRING 358
#define QUOTED_STRING 359
#define ASTERISK_STRING 360
#define LL_HDR 361
#define NETWORK_HDR 362
#define TRANSPORT_HDR 363
#define BRIDGE 364
#define ETHER 365
#define SADDR 366
#define DADDR 367
#define TYPE 368
#define VLAN 369
#define ID 370
#define CFI 371
#define DEI 372
#define PCP 373
#define ARP 374
#define HTYPE 375
#define PTYPE 376
#define HLEN 377
#define PLEN 378
#define OPERATION 379
#define IP 380
#define HDRVERSION 381
#define HDRLENGTH 382
#define DSCP 383
#define ECN 384
#define LENGTH 385
#define FRAG_OFF 386
#define TTL 387
#define PROTOCOL 388
#define CHECKSUM 389
#define PTR 390
#define VALUE 391
#define LSRR 392
#define RR 393
#define SSRR 394
#define RA 395
#define ICMP 396
#define CODE 397
#define SEQUENCE 398
#define GATEWAY 399
#define MTU 400
#define IGMP 401
#define MRT 402
#define OPTIONS 403
#define IP6 404
#define PRIORITY 405
#define FLOWLABEL 406
#define NEXTHDR 407
#define HOPLIMIT 408
#define ICMP6 409
#define PPTR 410
#define MAXDELAY 411
#define AH 412
#define RESERVED 413
#define SPI 414
#define ESP 415
#define COMP 416
#define FLAGS 417
#define CPI 418
#define PORT 419
#define UDP 420
#define SPORT 421
#define DPORT 422
#define UDPLITE 423
#define CSUMCOV 424
#define TCP 425
#define ACKSEQ 426
#define DOFF 427
#define WINDOW 428
#define URGPTR 429
#define OPTION 430
#define ECHO 431
#define EOL 432
#define NOP 433
#define SACK 434
#define SACK0 435
#define SACK1 436
#define SACK2 437
#define SACK3 438
#define SACK_PERM 439
#define TIMESTAMP 440
#define KIND 441
#define COUNT 442
#define LEFT 443
#define RIGHT 444
#define TSVAL 445
#define TSECR 446
#define DCCP 447
#define SCTP 448
#define CHUNK 449
#define DATA 450
#define INIT 451
#define INIT_ACK 452
#define HEARTBEAT 453
#define HEARTBEAT_ACK 454
#define ABORT 455
#define SHUTDOWN 456
#define SHUTDOWN_ACK 457
#define ERROR 458
#define COOKIE_ECHO 459
#define COOKIE_ACK 460
#define ECNE 461
#define CWR 462
#define SHUTDOWN_COMPLETE 463
#define ASCONF_ACK 464
#define FORWARD_TSN 465
#define ASCONF 466
#define TSN 467
#define STREAM 468
#define SSN 469
#define PPID 470
#define INIT_TAG 471
#define A_RWND 472
#define NUM_OSTREAMS 473
#define NUM_ISTREAMS 474
#define INIT_TSN 475
#define CUM_TSN_ACK 476
#define NUM_GACK_BLOCKS 477
#define NUM_DUP_TSNS 478
#define LOWEST_TSN 479
#define SEQNO 480
#define NEW_CUM_TSN 481
#define VTAG 482
#define RT 483
#define RT0 484
#define RT2 485
#define RT4 486
#define SEG_LEFT 487
#define ADDR 488
#define LAST_ENT 489
#define TAG 490
#define SID 491
#define HBH 492
#define FRAG 493
#define RESERVED2 494
#define MORE_FRAGMENTS 495
#define DST 496
#define MH 497
#define META 498
#define MARK 499
#define IIF 500
#define IIFNAME 501
#define IIFTYPE 502
#define OIF 503
#define OIFNAME 504
#define OIFTYPE 505
#define SKUID 506
#define SKGID 507
#define NFTRACE 508
#define RTCLASSID 509
#define IBRIPORT 510
#define OBRIPORT 511
#define IBRIDGENAME 512
#define OBRIDGENAME 513
#define PKTTYPE 514
#define CPU 515
#define IIFGROUP 516
#define OIFGROUP 517
#define CGROUP 518
#define TIME 519
#define CLASSID 520
#define NEXTHOP 521
#define CT 522
#define L3PROTOCOL 523
#define PROTO_SRC 524
#define PROTO_DST 525
#define ZONE 526
#define DIRECTION 527
#define EVENT 528
#define EXPECTATION 529
#define EXPIRATION 530
#define HELPER 531
#define LABEL 532
#define STATE 533
#define STATUS 534
#define ORIGINAL 535
#define REPLY 536
#define COUNTER 537
#define NAME 538
#define PACKETS 539
#define BYTES 540
#define AVGPKT 541
#define COUNTERS 542
#define QUOTAS 543
#define LIMITS 544
#define SYNPROXYS 545
#define HELPERS 546
#define LOG 547
#define PREFIX 548
#define GROUP 549
#define SNAPLEN 550
#define QUEUE_THRESHOLD 551
#define LEVEL 552
#define LIMIT 553
#define RATE 554
#define BURST 555
#define OVER 556
#define UNTIL 557
#define QUOTA 558
#define USED 559
#define SECMARK 560
#define SECMARKS 561
#define SECOND 562
#define MINUTE 563
#define HOUR 564
#define DAY 565
#define WEEK 566
#define _REJECT 567
#define WITH 568
#define ICMPX 569
#define SNAT 570
#define DNAT 571
#define MASQUERADE 572
#define REDIRECT 573
#define RANDOM 574
#define FULLY_RANDOM 575
#define PERSISTENT 576
#define QUEUE 577
#define QUEUENUM 578
#define BYPASS 579
#define FANOUT 580
#define DUP 581
#define FWD 582
#define NUMGEN 583
#define INC 584
#define MOD 585
#define OFFSET 586
#define JHASH 587
#define SYMHASH 588
#define SEED 589
#define POSITION 590
#define INDEX 591
#define COMMENT 592
#define XML 593
#define JSON 594
#define VM 595
#define NOTRACK 596
#define EXISTS 597
#define MISSING 598
#define EXTHDR 599
#define IPSEC 600
#define REQID 601
#define SPNUM 602
#define IN 603
#define OUT 604

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 167 "parser_bison.y"

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
	struct limit_rate	limit_rate;

#line 790 "parser_bison.h"

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
