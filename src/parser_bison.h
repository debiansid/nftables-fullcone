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
    TADDR = 413,                   /* "taddr"  */
    AH = 414,                      /* "ah"  */
    RESERVED = 415,                /* "reserved"  */
    SPI = 416,                     /* "spi"  */
    ESP = 417,                     /* "esp"  */
    COMP = 418,                    /* "comp"  */
    FLAGS = 419,                   /* "flags"  */
    CPI = 420,                     /* "cpi"  */
    PORT = 421,                    /* "port"  */
    UDP = 422,                     /* "udp"  */
    SPORT = 423,                   /* "sport"  */
    DPORT = 424,                   /* "dport"  */
    UDPLITE = 425,                 /* "udplite"  */
    CSUMCOV = 426,                 /* "csumcov"  */
    TCP = 427,                     /* "tcp"  */
    ACKSEQ = 428,                  /* "ackseq"  */
    DOFF = 429,                    /* "doff"  */
    WINDOW = 430,                  /* "window"  */
    URGPTR = 431,                  /* "urgptr"  */
    OPTION = 432,                  /* "option"  */
    ECHO = 433,                    /* "echo"  */
    EOL = 434,                     /* "eol"  */
    MPTCP = 435,                   /* "mptcp"  */
    NOP = 436,                     /* "nop"  */
    SACK = 437,                    /* "sack"  */
    SACK0 = 438,                   /* "sack0"  */
    SACK1 = 439,                   /* "sack1"  */
    SACK2 = 440,                   /* "sack2"  */
    SACK3 = 441,                   /* "sack3"  */
    SACK_PERM = 442,               /* "sack-permitted"  */
    FASTOPEN = 443,                /* "fastopen"  */
    MD5SIG = 444,                  /* "md5sig"  */
    TIMESTAMP = 445,               /* "timestamp"  */
    COUNT = 446,                   /* "count"  */
    LEFT = 447,                    /* "left"  */
    RIGHT = 448,                   /* "right"  */
    TSVAL = 449,                   /* "tsval"  */
    TSECR = 450,                   /* "tsecr"  */
    SUBTYPE = 451,                 /* "subtype"  */
    DCCP = 452,                    /* "dccp"  */
    VXLAN = 453,                   /* "vxlan"  */
    VNI = 454,                     /* "vni"  */
    GRE = 455,                     /* "gre"  */
    GRETAP = 456,                  /* "gretap"  */
    GENEVE = 457,                  /* "geneve"  */
    SCTP = 458,                    /* "sctp"  */
    CHUNK = 459,                   /* "chunk"  */
    DATA = 460,                    /* "data"  */
    INIT = 461,                    /* "init"  */
    INIT_ACK = 462,                /* "init-ack"  */
    HEARTBEAT = 463,               /* "heartbeat"  */
    HEARTBEAT_ACK = 464,           /* "heartbeat-ack"  */
    ABORT = 465,                   /* "abort"  */
    SHUTDOWN = 466,                /* "shutdown"  */
    SHUTDOWN_ACK = 467,            /* "shutdown-ack"  */
    ERROR = 468,                   /* "error"  */
    COOKIE_ECHO = 469,             /* "cookie-echo"  */
    COOKIE_ACK = 470,              /* "cookie-ack"  */
    ECNE = 471,                    /* "ecne"  */
    CWR = 472,                     /* "cwr"  */
    SHUTDOWN_COMPLETE = 473,       /* "shutdown-complete"  */
    ASCONF_ACK = 474,              /* "asconf-ack"  */
    FORWARD_TSN = 475,             /* "forward-tsn"  */
    ASCONF = 476,                  /* "asconf"  */
    TSN = 477,                     /* "tsn"  */
    STREAM = 478,                  /* "stream"  */
    SSN = 479,                     /* "ssn"  */
    PPID = 480,                    /* "ppid"  */
    INIT_TAG = 481,                /* "init-tag"  */
    A_RWND = 482,                  /* "a-rwnd"  */
    NUM_OSTREAMS = 483,            /* "num-outbound-streams"  */
    NUM_ISTREAMS = 484,            /* "num-inbound-streams"  */
    INIT_TSN = 485,                /* "initial-tsn"  */
    CUM_TSN_ACK = 486,             /* "cum-tsn-ack"  */
    NUM_GACK_BLOCKS = 487,         /* "num-gap-ack-blocks"  */
    NUM_DUP_TSNS = 488,            /* "num-dup-tsns"  */
    LOWEST_TSN = 489,              /* "lowest-tsn"  */
    SEQNO = 490,                   /* "seqno"  */
    NEW_CUM_TSN = 491,             /* "new-cum-tsn"  */
    VTAG = 492,                    /* "vtag"  */
    RT = 493,                      /* "rt"  */
    RT0 = 494,                     /* "rt0"  */
    RT2 = 495,                     /* "rt2"  */
    RT4 = 496,                     /* "srh"  */
    SEG_LEFT = 497,                /* "seg-left"  */
    ADDR = 498,                    /* "addr"  */
    LAST_ENT = 499,                /* "last-entry"  */
    TAG = 500,                     /* "tag"  */
    SID = 501,                     /* "sid"  */
    HBH = 502,                     /* "hbh"  */
    FRAG = 503,                    /* "frag"  */
    RESERVED2 = 504,               /* "reserved2"  */
    MORE_FRAGMENTS = 505,          /* "more-fragments"  */
    DST = 506,                     /* "dst"  */
    MH = 507,                      /* "mh"  */
    META = 508,                    /* "meta"  */
    MARK = 509,                    /* "mark"  */
    IIF = 510,                     /* "iif"  */
    IIFNAME = 511,                 /* "iifname"  */
    IIFTYPE = 512,                 /* "iiftype"  */
    OIF = 513,                     /* "oif"  */
    OIFNAME = 514,                 /* "oifname"  */
    OIFTYPE = 515,                 /* "oiftype"  */
    SKUID = 516,                   /* "skuid"  */
    SKGID = 517,                   /* "skgid"  */
    NFTRACE = 518,                 /* "nftrace"  */
    RTCLASSID = 519,               /* "rtclassid"  */
    IBRIPORT = 520,                /* "ibriport"  */
    OBRIPORT = 521,                /* "obriport"  */
    IBRIDGENAME = 522,             /* "ibrname"  */
    OBRIDGENAME = 523,             /* "obrname"  */
    PKTTYPE = 524,                 /* "pkttype"  */
    CPU = 525,                     /* "cpu"  */
    IIFGROUP = 526,                /* "iifgroup"  */
    OIFGROUP = 527,                /* "oifgroup"  */
    CGROUP = 528,                  /* "cgroup"  */
    TIME = 529,                    /* "time"  */
    CLASSID = 530,                 /* "classid"  */
    NEXTHOP = 531,                 /* "nexthop"  */
    CT = 532,                      /* "ct"  */
    L3PROTOCOL = 533,              /* "l3proto"  */
    PROTO_SRC = 534,               /* "proto-src"  */
    PROTO_DST = 535,               /* "proto-dst"  */
    ZONE = 536,                    /* "zone"  */
    DIRECTION = 537,               /* "direction"  */
    EVENT = 538,                   /* "event"  */
    EXPECTATION = 539,             /* "expectation"  */
    EXPIRATION = 540,              /* "expiration"  */
    HELPER = 541,                  /* "helper"  */
    LABEL = 542,                   /* "label"  */
    STATE = 543,                   /* "state"  */
    STATUS = 544,                  /* "status"  */
    ORIGINAL = 545,                /* "original"  */
    REPLY = 546,                   /* "reply"  */
    COUNTER = 547,                 /* "counter"  */
    NAME = 548,                    /* "name"  */
    PACKETS = 549,                 /* "packets"  */
    BYTES = 550,                   /* "bytes"  */
    AVGPKT = 551,                  /* "avgpkt"  */
    LAST = 552,                    /* "last"  */
    NEVER = 553,                   /* "never"  */
    COUNTERS = 554,                /* "counters"  */
    QUOTAS = 555,                  /* "quotas"  */
    LIMITS = 556,                  /* "limits"  */
    SYNPROXYS = 557,               /* "synproxys"  */
    HELPERS = 558,                 /* "helpers"  */
    LOG = 559,                     /* "log"  */
    PREFIX = 560,                  /* "prefix"  */
    GROUP = 561,                   /* "group"  */
    SNAPLEN = 562,                 /* "snaplen"  */
    QUEUE_THRESHOLD = 563,         /* "queue-threshold"  */
    LEVEL = 564,                   /* "level"  */
    LIMIT = 565,                   /* "limit"  */
    RATE = 566,                    /* "rate"  */
    BURST = 567,                   /* "burst"  */
    OVER = 568,                    /* "over"  */
    UNTIL = 569,                   /* "until"  */
    QUOTA = 570,                   /* "quota"  */
    USED = 571,                    /* "used"  */
    SECMARK = 572,                 /* "secmark"  */
    SECMARKS = 573,                /* "secmarks"  */
    SECOND = 574,                  /* "second"  */
    MINUTE = 575,                  /* "minute"  */
    HOUR = 576,                    /* "hour"  */
    DAY = 577,                     /* "day"  */
    WEEK = 578,                    /* "week"  */
    _REJECT = 579,                 /* "reject"  */
    WITH = 580,                    /* "with"  */
    ICMPX = 581,                   /* "icmpx"  */
    SNAT = 582,                    /* "snat"  */
    DNAT = 583,                    /* "dnat"  */
    MASQUERADE = 584,              /* "masquerade"  */
    REDIRECT = 585,                /* "redirect"  */
    RANDOM = 586,                  /* "random"  */
    FULLY_RANDOM = 587,            /* "fully-random"  */
    PERSISTENT = 588,              /* "persistent"  */
    QUEUE = 589,                   /* "queue"  */
    QUEUENUM = 590,                /* "num"  */
    BYPASS = 591,                  /* "bypass"  */
    FANOUT = 592,                  /* "fanout"  */
    DUP = 593,                     /* "dup"  */
    FWD = 594,                     /* "fwd"  */
    NUMGEN = 595,                  /* "numgen"  */
    INC = 596,                     /* "inc"  */
    MOD = 597,                     /* "mod"  */
    OFFSET = 598,                  /* "offset"  */
    JHASH = 599,                   /* "jhash"  */
    SYMHASH = 600,                 /* "symhash"  */
    SEED = 601,                    /* "seed"  */
    POSITION = 602,                /* "position"  */
    INDEX = 603,                   /* "index"  */
    COMMENT = 604,                 /* "comment"  */
    XML = 605,                     /* "xml"  */
    JSON = 606,                    /* "json"  */
    VM = 607,                      /* "vm"  */
    NOTRACK = 608,                 /* "notrack"  */
    EXISTS = 609,                  /* "exists"  */
    MISSING = 610,                 /* "missing"  */
    EXTHDR = 611,                  /* "exthdr"  */
    IPSEC = 612,                   /* "ipsec"  */
    REQID = 613,                   /* "reqid"  */
    SPNUM = 614,                   /* "spnum"  */
    IN = 615,                      /* "in"  */
    OUT = 616,                     /* "out"  */
    XT = 617                       /* "xt"  */
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
#define TADDR 413
#define AH 414
#define RESERVED 415
#define SPI 416
#define ESP 417
#define COMP 418
#define FLAGS 419
#define CPI 420
#define PORT 421
#define UDP 422
#define SPORT 423
#define DPORT 424
#define UDPLITE 425
#define CSUMCOV 426
#define TCP 427
#define ACKSEQ 428
#define DOFF 429
#define WINDOW 430
#define URGPTR 431
#define OPTION 432
#define ECHO 433
#define EOL 434
#define MPTCP 435
#define NOP 436
#define SACK 437
#define SACK0 438
#define SACK1 439
#define SACK2 440
#define SACK3 441
#define SACK_PERM 442
#define FASTOPEN 443
#define MD5SIG 444
#define TIMESTAMP 445
#define COUNT 446
#define LEFT 447
#define RIGHT 448
#define TSVAL 449
#define TSECR 450
#define SUBTYPE 451
#define DCCP 452
#define VXLAN 453
#define VNI 454
#define GRE 455
#define GRETAP 456
#define GENEVE 457
#define SCTP 458
#define CHUNK 459
#define DATA 460
#define INIT 461
#define INIT_ACK 462
#define HEARTBEAT 463
#define HEARTBEAT_ACK 464
#define ABORT 465
#define SHUTDOWN 466
#define SHUTDOWN_ACK 467
#define ERROR 468
#define COOKIE_ECHO 469
#define COOKIE_ACK 470
#define ECNE 471
#define CWR 472
#define SHUTDOWN_COMPLETE 473
#define ASCONF_ACK 474
#define FORWARD_TSN 475
#define ASCONF 476
#define TSN 477
#define STREAM 478
#define SSN 479
#define PPID 480
#define INIT_TAG 481
#define A_RWND 482
#define NUM_OSTREAMS 483
#define NUM_ISTREAMS 484
#define INIT_TSN 485
#define CUM_TSN_ACK 486
#define NUM_GACK_BLOCKS 487
#define NUM_DUP_TSNS 488
#define LOWEST_TSN 489
#define SEQNO 490
#define NEW_CUM_TSN 491
#define VTAG 492
#define RT 493
#define RT0 494
#define RT2 495
#define RT4 496
#define SEG_LEFT 497
#define ADDR 498
#define LAST_ENT 499
#define TAG 500
#define SID 501
#define HBH 502
#define FRAG 503
#define RESERVED2 504
#define MORE_FRAGMENTS 505
#define DST 506
#define MH 507
#define META 508
#define MARK 509
#define IIF 510
#define IIFNAME 511
#define IIFTYPE 512
#define OIF 513
#define OIFNAME 514
#define OIFTYPE 515
#define SKUID 516
#define SKGID 517
#define NFTRACE 518
#define RTCLASSID 519
#define IBRIPORT 520
#define OBRIPORT 521
#define IBRIDGENAME 522
#define OBRIDGENAME 523
#define PKTTYPE 524
#define CPU 525
#define IIFGROUP 526
#define OIFGROUP 527
#define CGROUP 528
#define TIME 529
#define CLASSID 530
#define NEXTHOP 531
#define CT 532
#define L3PROTOCOL 533
#define PROTO_SRC 534
#define PROTO_DST 535
#define ZONE 536
#define DIRECTION 537
#define EVENT 538
#define EXPECTATION 539
#define EXPIRATION 540
#define HELPER 541
#define LABEL 542
#define STATE 543
#define STATUS 544
#define ORIGINAL 545
#define REPLY 546
#define COUNTER 547
#define NAME 548
#define PACKETS 549
#define BYTES 550
#define AVGPKT 551
#define LAST 552
#define NEVER 553
#define COUNTERS 554
#define QUOTAS 555
#define LIMITS 556
#define SYNPROXYS 557
#define HELPERS 558
#define LOG 559
#define PREFIX 560
#define GROUP 561
#define SNAPLEN 562
#define QUEUE_THRESHOLD 563
#define LEVEL 564
#define LIMIT 565
#define RATE 566
#define BURST 567
#define OVER 568
#define UNTIL 569
#define QUOTA 570
#define USED 571
#define SECMARK 572
#define SECMARKS 573
#define SECOND 574
#define MINUTE 575
#define HOUR 576
#define DAY 577
#define WEEK 578
#define _REJECT 579
#define WITH 580
#define ICMPX 581
#define SNAT 582
#define DNAT 583
#define MASQUERADE 584
#define REDIRECT 585
#define RANDOM 586
#define FULLY_RANDOM 587
#define PERSISTENT 588
#define QUEUE 589
#define QUEUENUM 590
#define BYPASS 591
#define FANOUT 592
#define DUP 593
#define FWD 594
#define NUMGEN 595
#define INC 596
#define MOD 597
#define OFFSET 598
#define JHASH 599
#define SYMHASH 600
#define SEED 601
#define POSITION 602
#define INDEX 603
#define COMMENT 604
#define XML 605
#define JSON 606
#define VM 607
#define NOTRACK 608
#define EXISTS 609
#define MISSING 610
#define EXTHDR 611
#define IPSEC 612
#define REQID 613
#define SPNUM 614
#define IN 615
#define OUT 616
#define XT 617

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 205 "parser_bison.y"

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

#line 820 "parser_bison.h"

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
