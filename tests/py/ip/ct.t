:output;type filter hook output priority 0

*ip;test-ip4;output

ct original ip saddr 192.168.0.1;ok
ct reply ip saddr 192.168.0.1;ok
ct original ip daddr 192.168.0.1;ok
ct reply ip daddr 192.168.0.1;ok

# same, but with a netmask
ct original ip saddr 192.168.1.0/24;ok
ct reply ip saddr 192.168.1.0/24;ok
ct original ip daddr 192.168.1.0/24;ok
ct reply ip daddr 192.168.1.0/24;ok

ct l3proto ipv4;ok
ct l3proto foobar;fail

ct protocol 6 ct original proto-dst 22;ok
ct original protocol 17 ct reply proto-src 53;ok;ct protocol 17 ct reply proto-src 53

# wrong address family
ct reply ip daddr dead::beef;fail

meta mark set ct original daddr map { 1.1.1.1 : 0x00000011 };fail
meta mark set ct original ip daddr map { 1.1.1.1 : 0x00000011 };ok
