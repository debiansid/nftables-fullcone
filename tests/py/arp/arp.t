# filter chains available are: input, output, forward
:input;type filter hook input priority 0
:ingress;type filter hook ingress device lo priority 0

*arp;test-arp;input
*netdev;test-netdev;ingress

arp htype 1;ok
arp htype != 1;ok
arp htype 22;ok
arp htype != 233;ok
arp htype 33-45;ok
arp htype != 33-45;ok
arp htype { 33, 55, 67, 88};ok
arp htype != { 33, 55, 67, 88};ok
arp htype { 33-55};ok
arp htype != { 33-55};ok

arp ptype 0x0800;ok;arp ptype ip

arp hlen 22;ok
arp hlen != 233;ok
arp hlen 33-45;ok
arp hlen != 33-45;ok
arp hlen { 33, 55, 67, 88};ok
arp hlen != { 33, 55, 67, 88};ok
arp hlen { 33-55};ok
arp hlen != { 33-55};ok

arp plen 22;ok
arp plen != 233;ok
arp plen 33-45;ok
arp plen != 33-45;ok
arp plen { 33, 55, 67, 88};ok
arp plen != { 33, 55, 67, 88};ok
arp plen { 33-55};ok
arp plen != {33-55};ok

arp operation {nak, inreply, inrequest, rreply, rrequest, reply, request};ok
arp operation != {nak, inreply, inrequest, rreply, rrequest, reply, request};ok
arp operation request;ok
arp operation reply;ok
arp operation rrequest;ok
arp operation rreply;ok
arp operation inrequest;ok
arp operation inreply;ok
arp operation nak;ok
arp operation reply;ok
arp operation != request;ok
arp operation != reply;ok
arp operation != rrequest;ok
arp operation != rreply;ok
arp operation != inrequest;ok
arp operation != inreply;ok
arp operation != nak;ok
arp operation != reply;ok

meta iifname \"invalid\" arp ptype 0x0800 arp htype 1 arp hlen 6 arp plen 4 @nh,192,32 0xc0a88f10 @nh,144,48 set 0x112233445566;ok;iifname "invalid" arp htype 1 arp ptype ip arp hlen 6 arp plen 4 @nh,192,32 3232272144 @nh,144,48 set 18838586676582
