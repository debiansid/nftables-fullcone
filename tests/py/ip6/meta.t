:input;type filter hook input priority 0

*ip6;test-ip6;input

icmpv6 type nd-router-advert;ok
meta l4proto ipv6-icmp icmpv6 type nd-router-advert;ok;icmpv6 type nd-router-advert

meta l4proto icmp icmp type echo-request;ok;icmp type echo-request
meta l4proto 1 icmp type echo-request;ok;icmp type echo-request
icmp type echo-request;ok

meta sdif "lo" accept;ok
meta sdifname != "vrf1" accept;ok
