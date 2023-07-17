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
    DESTROY = 331,                 /* "destroy"  */
    MONITOR = 332,                 /* "monitor"  */
    ALL = 333,                     /* "all"  */
    ACCEPT = 334,                  /* "accept"  */
    DROP = 335,                    /* "drop"  */
    CONTINUE = 336,                /* "continue"  */
    JUMP = 337,                    /* "jump"  */
    GOTO = 338,                    /* "goto"  */
    RETURN = 339,                  /* "return"  */
    TO = 340,                      /* "to"  */
    CONSTANT = 341,                /* "constant"  */
    INTERVAL = 342,                /* "interval"  */
    DYNAMIC = 343,                 /* "dynamic"  */
    AUTOMERGE = 344,               /* "auto-merge"  */
    TIMEOUT = 345,                 /* "timeout"  */
    GC_INTERVAL = 346,             /* "gc-interval"  */
    ELEMENTS = 347,                /* "elements"  */
    EXPIRES = 348,                 /* "expires"  */
    POLICY = 349,                  /* "policy"  */
    MEMORY = 350,                  /* "memory"  */
    PERFORMANCE = 351,             /* "performance"  */
    SIZE = 352,                    /* "size"  */
    FLOW = 353,                    /* "flow"  */
    OFFLOAD = 354,                 /* "offload"  */
    METER = 355,                   /* "meter"  */
    METERS = 356,                  /* "meters"  */
    FLOWTABLES = 357,              /* "flowtables"  */
    NUM = 358,                     /* "number"  */
    STRING = 359,                  /* "string"  */
    QUOTED_STRING = 360,           /* "quoted string"  */
    ASTERISK_STRING = 361,         /* "string with a trailing asterisk"  */
    LL_HDR = 362,                  /* "ll"  */
    NETWORK_HDR = 363,             /* "nh"  */
    TRANSPORT_HDR = 364,           /* "th"  */
    BRIDGE = 365,                  /* "bridge"  */
    ETHER = 366,                   /* "ether"  */
    SADDR = 367,                   /* "saddr"  */
    DADDR = 368,                   /* "daddr"  */
    TYPE = 369,                    /* "type"  */
    VLAN = 370,                    /* "vlan"  */
    ID = 371,                      /* "id"  */
    CFI = 372,                     /* "cfi"  */
    DEI = 373,                     /* "dei"  */
    PCP = 374,                     /* "pcp"  */
    ARP = 375,                     /* "arp"  */
    HTYPE = 376,                   /* "htype"  */
    PTYPE = 377,                   /* "ptype"  */
    HLEN = 378,                    /* "hlen"  */
    PLEN = 379,                    /* "plen"  */
    OPERATION = 380,               /* "operation"  */
    IP = 381,                      /* "ip"  */
    HDRVERSION = 382,              /* "version"  */
    HDRLENGTH = 383,               /* "hdrlength"  */
    DSCP = 384,                    /* "dscp"  */
    ECN = 385,                     /* "ecn"  */
    LENGTH = 386,                  /* "length"  */
    FRAG_OFF = 387,                /* "frag-off"  */
    TTL = 388,                     /* "ttl"  */
    PROTOCOL = 389,                /* "protocol"  */
    CHECKSUM = 390,                /* "checksum"  */
    PTR = 391,                     /* "ptr"  */
    VALUE = 392,                   /* "value"  */
    LSRR = 393,                    /* "lsrr"  */
    RR = 394,                      /* "rr"  */
    SSRR = 395,                    /* "ssrr"  */
    RA = 396,                      /* "ra"  */
    ICMP = 397,                    /* "icmp"  */
    CODE = 398,                    /* "code"  */
    SEQUENCE = 399,                /* "seq"  */
    GATEWAY = 400,                 /* "gateway"  */
    MTU = 401,                     /* "mtu"  */
    IGMP = 402,                    /* "igmp"  */
    MRT = 403,                     /* "mrt"  */
    OPTIONS = 404,                 /* "options"  */
    IP6 = 405,                     /* "ip6"  */
    PRIORITY = 406,                /* "priority"  */
    FLOWLABEL = 407,               /* "flowlabel"  */
    NEXTHDR = 408,                 /* "nexthdr"  */
    HOPLIMIT = 409,                /* "hoplimit"  */
    ICMP6 = 410,                   /* "icmpv6"  */
    PPTR = 411,                    /* "param-problem"  */
    MAXDELAY = 412,                /* "max-delay"  */
    AH = 413,                      /* "ah"  */
    RESERVED = 414,                /* "reserved"  */
    SPI = 415,                     /* "spi"  */
    ESP = 416,                     /* "esp"  */
    COMP = 417,                    /* "comp"  */
    FLAGS = 418,                   /* "flags"  */
    CPI = 419,                     /* "cpi"  */
    PORT = 420,                    /* "port"  */
    UDP = 421,                     /* "udp"  */
    SPORT = 422,                   /* "sport"  */
    DPORT = 423,                   /* "dport"  */
    UDPLITE = 424,                 /* "udplite"  */
    CSUMCOV = 425,                 /* "csumcov"  */
    TCP = 426,                     /* "tcp"  */
    ACKSEQ = 427,                  /* "ackseq"  */
    DOFF = 428,                    /* "doff"  */
    WINDOW = 429,                  /* "window"  */
    URGPTR = 430,                  /* "urgptr"  */
    OPTION = 431,                  /* "option"  */
    ECHO = 432,                    /* "echo"  */
    EOL = 433,                     /* "eol"  */
    MPTCP = 434,                   /* "mptcp"  */
    NOP = 435,                     /* "nop"  */
    SACK = 436,                    /* "sack"  */
    SACK0 = 437,                   /* "sack0"  */
    SACK1 = 438,                   /* "sack1"  */
    SACK2 = 439,                   /* "sack2"  */
    SACK3 = 440,                   /* "sack3"  */
    SACK_PERM = 441,               /* "sack-permitted"  */
    FASTOPEN = 442,                /* "fastopen"  */
    MD5SIG = 443,                  /* "md5sig"  */
    TIMESTAMP = 444,               /* "timestamp"  */
    COUNT = 445,                   /* "count"  */
    LEFT = 446,                    /* "left"  */
    RIGHT = 447,                   /* "right"  */
    TSVAL = 448,                   /* "tsval"  */
    TSECR = 449,                   /* "tsecr"  */
    SUBTYPE = 450,                 /* "subtype"  */
    DCCP = 451,                    /* "dccp"  */
    VXLAN = 452,                   /* "vxlan"  */
    VNI = 453,                     /* "vni"  */
    GRE = 454,                     /* "gre"  */
    GRETAP = 455,                  /* "gretap"  */
    GENEVE = 456,                  /* "geneve"  */
    SCTP = 457,                    /* "sctp"  */
    CHUNK = 458,                   /* "chunk"  */
    DATA = 459,                    /* "data"  */
    INIT = 460,                    /* "init"  */
    INIT_ACK = 461,                /* "init-ack"  */
    HEARTBEAT = 462,               /* "heartbeat"  */
    HEARTBEAT_ACK = 463,           /* "heartbeat-ack"  */
    ABORT = 464,                   /* "abort"  */
    SHUTDOWN = 465,                /* "shutdown"  */
    SHUTDOWN_ACK = 466,            /* "shutdown-ack"  */
    ERROR = 467,                   /* "error"  */
    COOKIE_ECHO = 468,             /* "cookie-echo"  */
    COOKIE_ACK = 469,              /* "cookie-ack"  */
    ECNE = 470,                    /* "ecne"  */
    CWR = 471,                     /* "cwr"  */
    SHUTDOWN_COMPLETE = 472,       /* "shutdown-complete"  */
    ASCONF_ACK = 473,              /* "asconf-ack"  */
    FORWARD_TSN = 474,             /* "forward-tsn"  */
    ASCONF = 475,                  /* "asconf"  */
    TSN = 476,                     /* "tsn"  */
    STREAM = 477,                  /* "stream"  */
    SSN = 478,                     /* "ssn"  */
    PPID = 479,                    /* "ppid"  */
    INIT_TAG = 480,                /* "init-tag"  */
    A_RWND = 481,                  /* "a-rwnd"  */
    NUM_OSTREAMS = 482,            /* "num-outbound-streams"  */
    NUM_ISTREAMS = 483,            /* "num-inbound-streams"  */
    INIT_TSN = 484,                /* "initial-tsn"  */
    CUM_TSN_ACK = 485,             /* "cum-tsn-ack"  */
    NUM_GACK_BLOCKS = 486,         /* "num-gap-ack-blocks"  */
    NUM_DUP_TSNS = 487,            /* "num-dup-tsns"  */
    LOWEST_TSN = 488,              /* "lowest-tsn"  */
    SEQNO = 489,                   /* "seqno"  */
    NEW_CUM_TSN = 490,             /* "new-cum-tsn"  */
    VTAG = 491,                    /* "vtag"  */
    RT = 492,                      /* "rt"  */
    RT0 = 493,                     /* "rt0"  */
    RT2 = 494,                     /* "rt2"  */
    RT4 = 495,                     /* "srh"  */
    SEG_LEFT = 496,                /* "seg-left"  */
    ADDR = 497,                    /* "addr"  */
    LAST_ENT = 498,                /* "last-entry"  */
    TAG = 499,                     /* "tag"  */
    SID = 500,                     /* "sid"  */
    HBH = 501,                     /* "hbh"  */
    FRAG = 502,                    /* "frag"  */
    RESERVED2 = 503,               /* "reserved2"  */
    MORE_FRAGMENTS = 504,          /* "more-fragments"  */
    DST = 505,                     /* "dst"  */
    MH = 506,                      /* "mh"  */
    META = 507,                    /* "meta"  */
    MARK = 508,                    /* "mark"  */
    IIF = 509,                     /* "iif"  */
    IIFNAME = 510,                 /* "iifname"  */
    IIFTYPE = 511,                 /* "iiftype"  */
    OIF = 512,                     /* "oif"  */
    OIFNAME = 513,                 /* "oifname"  */
    OIFTYPE = 514,                 /* "oiftype"  */
    SKUID = 515,                   /* "skuid"  */
    SKGID = 516,                   /* "skgid"  */
    NFTRACE = 517,                 /* "nftrace"  */
    RTCLASSID = 518,               /* "rtclassid"  */
    IBRIPORT = 519,                /* "ibriport"  */
    OBRIPORT = 520,                /* "obriport"  */
    IBRIDGENAME = 521,             /* "ibrname"  */
    OBRIDGENAME = 522,             /* "obrname"  */
    PKTTYPE = 523,                 /* "pkttype"  */
    CPU = 524,                     /* "cpu"  */
    IIFGROUP = 525,                /* "iifgroup"  */
    OIFGROUP = 526,                /* "oifgroup"  */
    CGROUP = 527,                  /* "cgroup"  */
    TIME = 528,                    /* "time"  */
    CLASSID = 529,                 /* "classid"  */
    NEXTHOP = 530,                 /* "nexthop"  */
    CT = 531,                      /* "ct"  */
    L3PROTOCOL = 532,              /* "l3proto"  */
    PROTO_SRC = 533,               /* "proto-src"  */
    PROTO_DST = 534,               /* "proto-dst"  */
    ZONE = 535,                    /* "zone"  */
    DIRECTION = 536,               /* "direction"  */
    EVENT = 537,                   /* "event"  */
    EXPECTATION = 538,             /* "expectation"  */
    EXPIRATION = 539,              /* "expiration"  */
    HELPER = 540,                  /* "helper"  */
    LABEL = 541,                   /* "label"  */
    STATE = 542,                   /* "state"  */
    STATUS = 543,                  /* "status"  */
    ORIGINAL = 544,                /* "original"  */
    REPLY = 545,                   /* "reply"  */
    COUNTER = 546,                 /* "counter"  */
    NAME = 547,                    /* "name"  */
    PACKETS = 548,                 /* "packets"  */
    BYTES = 549,                   /* "bytes"  */
    AVGPKT = 550,                  /* "avgpkt"  */
    LAST = 551,                    /* "last"  */
    NEVER = 552,                   /* "never"  */
    COUNTERS = 553,                /* "counters"  */
    QUOTAS = 554,                  /* "quotas"  */
    LIMITS = 555,                  /* "limits"  */
    SYNPROXYS = 556,               /* "synproxys"  */
    HELPERS = 557,                 /* "helpers"  */
    LOG = 558,                     /* "log"  */
    PREFIX = 559,                  /* "prefix"  */
    GROUP = 560,                   /* "group"  */
    SNAPLEN = 561,                 /* "snaplen"  */
    QUEUE_THRESHOLD = 562,         /* "queue-threshold"  */
    LEVEL = 563,                   /* "level"  */
    LIMIT = 564,                   /* "limit"  */
    RATE = 565,                    /* "rate"  */
    BURST = 566,                   /* "burst"  */
    OVER = 567,                    /* "over"  */
    UNTIL = 568,                   /* "until"  */
    QUOTA = 569,                   /* "quota"  */
    USED = 570,                    /* "used"  */
    SECMARK = 571,                 /* "secmark"  */
    SECMARKS = 572,                /* "secmarks"  */
    SECOND = 573,                  /* "second"  */
    MINUTE = 574,                  /* "minute"  */
    HOUR = 575,                    /* "hour"  */
    DAY = 576,                     /* "day"  */
    WEEK = 577,                    /* "week"  */
    _REJECT = 578,                 /* "reject"  */
    WITH = 579,                    /* "with"  */
    ICMPX = 580,                   /* "icmpx"  */
    SNAT = 581,                    /* "snat"  */
    DNAT = 582,                    /* "dnat"  */
    MASQUERADE = 583,              /* "masquerade"  */
    REDIRECT = 584,                /* "redirect"  */
    RANDOM = 585,                  /* "random"  */
    FULLY_RANDOM = 586,            /* "fully-random"  */
    PERSISTENT = 587,              /* "persistent"  */
    QUEUE = 588,                   /* "queue"  */
    QUEUENUM = 589,                /* "num"  */
    BYPASS = 590,                  /* "bypass"  */
    FANOUT = 591,                  /* "fanout"  */
    DUP = 592,                     /* "dup"  */
    FWD = 593,                     /* "fwd"  */
    NUMGEN = 594,                  /* "numgen"  */
    INC = 595,                     /* "inc"  */
    MOD = 596,                     /* "mod"  */
    OFFSET = 597,                  /* "offset"  */
    JHASH = 598,                   /* "jhash"  */
    SYMHASH = 599,                 /* "symhash"  */
    SEED = 600,                    /* "seed"  */
    POSITION = 601,                /* "position"  */
    INDEX = 602,                   /* "index"  */
    COMMENT = 603,                 /* "comment"  */
    XML = 604,                     /* "xml"  */
    JSON = 605,                    /* "json"  */
    VM = 606,                      /* "vm"  */
    NOTRACK = 607,                 /* "notrack"  */
    EXISTS = 608,                  /* "exists"  */
    MISSING = 609,                 /* "missing"  */
    EXTHDR = 610,                  /* "exthdr"  */
    IPSEC = 611,                   /* "ipsec"  */
    REQID = 612,                   /* "reqid"  */
    SPNUM = 613,                   /* "spnum"  */
    IN = 614,                      /* "in"  */
    OUT = 615,                     /* "out"  */
    XT = 616                       /* "xt"  */
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
#define DESTROY 331
#define MONITOR 332
#define ALL 333
#define ACCEPT 334
#define DROP 335
#define CONTINUE 336
#define JUMP 337
#define GOTO 338
#define RETURN 339
#define TO 340
#define CONSTANT 341
#define INTERVAL 342
#define DYNAMIC 343
#define AUTOMERGE 344
#define TIMEOUT 345
#define GC_INTERVAL 346
#define ELEMENTS 347
#define EXPIRES 348
#define POLICY 349
#define MEMORY 350
#define PERFORMANCE 351
#define SIZE 352
#define FLOW 353
#define OFFLOAD 354
#define METER 355
#define METERS 356
#define FLOWTABLES 357
#define NUM 358
#define STRING 359
#define QUOTED_STRING 360
#define ASTERISK_STRING 361
#define LL_HDR 362
#define NETWORK_HDR 363
#define TRANSPORT_HDR 364
#define BRIDGE 365
#define ETHER 366
#define SADDR 367
#define DADDR 368
#define TYPE 369
#define VLAN 370
#define ID 371
#define CFI 372
#define DEI 373
#define PCP 374
#define ARP 375
#define HTYPE 376
#define PTYPE 377
#define HLEN 378
#define PLEN 379
#define OPERATION 380
#define IP 381
#define HDRVERSION 382
#define HDRLENGTH 383
#define DSCP 384
#define ECN 385
#define LENGTH 386
#define FRAG_OFF 387
#define TTL 388
#define PROTOCOL 389
#define CHECKSUM 390
#define PTR 391
#define VALUE 392
#define LSRR 393
#define RR 394
#define SSRR 395
#define RA 396
#define ICMP 397
#define CODE 398
#define SEQUENCE 399
#define GATEWAY 400
#define MTU 401
#define IGMP 402
#define MRT 403
#define OPTIONS 404
#define IP6 405
#define PRIORITY 406
#define FLOWLABEL 407
#define NEXTHDR 408
#define HOPLIMIT 409
#define ICMP6 410
#define PPTR 411
#define MAXDELAY 412
#define AH 413
#define RESERVED 414
#define SPI 415
#define ESP 416
#define COMP 417
#define FLAGS 418
#define CPI 419
#define PORT 420
#define UDP 421
#define SPORT 422
#define DPORT 423
#define UDPLITE 424
#define CSUMCOV 425
#define TCP 426
#define ACKSEQ 427
#define DOFF 428
#define WINDOW 429
#define URGPTR 430
#define OPTION 431
#define ECHO 432
#define EOL 433
#define MPTCP 434
#define NOP 435
#define SACK 436
#define SACK0 437
#define SACK1 438
#define SACK2 439
#define SACK3 440
#define SACK_PERM 441
#define FASTOPEN 442
#define MD5SIG 443
#define TIMESTAMP 444
#define COUNT 445
#define LEFT 446
#define RIGHT 447
#define TSVAL 448
#define TSECR 449
#define SUBTYPE 450
#define DCCP 451
#define VXLAN 452
#define VNI 453
#define GRE 454
#define GRETAP 455
#define GENEVE 456
#define SCTP 457
#define CHUNK 458
#define DATA 459
#define INIT 460
#define INIT_ACK 461
#define HEARTBEAT 462
#define HEARTBEAT_ACK 463
#define ABORT 464
#define SHUTDOWN 465
#define SHUTDOWN_ACK 466
#define ERROR 467
#define COOKIE_ECHO 468
#define COOKIE_ACK 469
#define ECNE 470
#define CWR 471
#define SHUTDOWN_COMPLETE 472
#define ASCONF_ACK 473
#define FORWARD_TSN 474
#define ASCONF 475
#define TSN 476
#define STREAM 477
#define SSN 478
#define PPID 479
#define INIT_TAG 480
#define A_RWND 481
#define NUM_OSTREAMS 482
#define NUM_ISTREAMS 483
#define INIT_TSN 484
#define CUM_TSN_ACK 485
#define NUM_GACK_BLOCKS 486
#define NUM_DUP_TSNS 487
#define LOWEST_TSN 488
#define SEQNO 489
#define NEW_CUM_TSN 490
#define VTAG 491
#define RT 492
#define RT0 493
#define RT2 494
#define RT4 495
#define SEG_LEFT 496
#define ADDR 497
#define LAST_ENT 498
#define TAG 499
#define SID 500
#define HBH 501
#define FRAG 502
#define RESERVED2 503
#define MORE_FRAGMENTS 504
#define DST 505
#define MH 506
#define META 507
#define MARK 508
#define IIF 509
#define IIFNAME 510
#define IIFTYPE 511
#define OIF 512
#define OIFNAME 513
#define OIFTYPE 514
#define SKUID 515
#define SKGID 516
#define NFTRACE 517
#define RTCLASSID 518
#define IBRIPORT 519
#define OBRIPORT 520
#define IBRIDGENAME 521
#define OBRIDGENAME 522
#define PKTTYPE 523
#define CPU 524
#define IIFGROUP 525
#define OIFGROUP 526
#define CGROUP 527
#define TIME 528
#define CLASSID 529
#define NEXTHOP 530
#define CT 531
#define L3PROTOCOL 532
#define PROTO_SRC 533
#define PROTO_DST 534
#define ZONE 535
#define DIRECTION 536
#define EVENT 537
#define EXPECTATION 538
#define EXPIRATION 539
#define HELPER 540
#define LABEL 541
#define STATE 542
#define STATUS 543
#define ORIGINAL 544
#define REPLY 545
#define COUNTER 546
#define NAME 547
#define PACKETS 548
#define BYTES 549
#define AVGPKT 550
#define LAST 551
#define NEVER 552
#define COUNTERS 553
#define QUOTAS 554
#define LIMITS 555
#define SYNPROXYS 556
#define HELPERS 557
#define LOG 558
#define PREFIX 559
#define GROUP 560
#define SNAPLEN 561
#define QUEUE_THRESHOLD 562
#define LEVEL 563
#define LIMIT 564
#define RATE 565
#define BURST 566
#define OVER 567
#define UNTIL 568
#define QUOTA 569
#define USED 570
#define SECMARK 571
#define SECMARKS 572
#define SECOND 573
#define MINUTE 574
#define HOUR 575
#define DAY 576
#define WEEK 577
#define _REJECT 578
#define WITH 579
#define ICMPX 580
#define SNAT 581
#define DNAT 582
#define MASQUERADE 583
#define REDIRECT 584
#define RANDOM 585
#define FULLY_RANDOM 586
#define PERSISTENT 587
#define QUEUE 588
#define QUEUENUM 589
#define BYPASS 590
#define FANOUT 591
#define DUP 592
#define FWD 593
#define NUMGEN 594
#define INC 595
#define MOD 596
#define OFFSET 597
#define JHASH 598
#define SYMHASH 599
#define SEED 600
#define POSITION 601
#define INDEX 602
#define COMMENT 603
#define XML 604
#define JSON 605
#define VM 606
#define NOTRACK 607
#define EXISTS 608
#define MISSING 609
#define EXTHDR 610
#define IPSEC 611
#define REQID 612
#define SPNUM 613
#define IN 614
#define OUT 615
#define XT 616

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 204 "parser_bison.y"

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
	struct tcp_kind_field {
		uint16_t kind; /* must allow > 255 for SACK1, 2.. hack */
		uint8_t field;
	} tcp_kind_field;

#line 818 "parser_bison.h"

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
