:output;type filter hook output priority 0

*ip6;test-ip6;output

reject;ok
reject with icmpv6 type no-route;ok
reject with icmpv6 type admin-prohibited;ok
reject with icmpv6 type addr-unreachable;ok
reject with icmpv6 type port-unreachable;ok;reject
reject with icmpv6 type policy-fail;ok
reject with icmpv6 type reject-route;ok
reject with tcp reset;ok;ip6 nexthdr 6 reject with tcp reset

reject with icmpv6 type host-unreachable;fail
reject with icmp type host-unreachable;fail
