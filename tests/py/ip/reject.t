:output;type filter hook output priority 0

*ip;test-ip4;output

reject;ok
reject with icmp type host-unreachable;ok
reject with icmp type net-unreachable;ok
reject with icmp type prot-unreachable;ok
reject with icmp type port-unreachable;ok;reject
reject with icmp type net-prohibited;ok
reject with icmp type host-prohibited;ok
reject with icmp type admin-prohibited;ok
mark 0x80000000 reject with tcp reset;ok;meta mark 0x80000000 reject with tcp reset

reject with icmp type no-route;fail
reject with icmpv6 type no-route;fail
