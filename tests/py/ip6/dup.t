:input;type filter hook input priority 0

*ip6;test-ip6;input

dup to abcd::1;ok
dup to abcd::1 device eth0;ok
dup to ip6 saddr map { abcd::1 : cafe::cafe } device eth0;ok
