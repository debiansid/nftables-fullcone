:prerouting;type nat hook prerouting priority 0

*ip6;test-ip6;prerouting

tcp dport 80-90 dnat to [2001:838:35f:1::]-[2001:838:35f:2::]:80-100;ok
tcp dport 80-90 dnat to [2001:838:35f:1::]-[2001:838:35f:2::]:100;ok;tcp dport 80-90 dnat to [2001:838:35f:1::]-[2001:838:35f:2::]:100
tcp dport 80-90 dnat to [2001:838:35f:1::]:80;ok
