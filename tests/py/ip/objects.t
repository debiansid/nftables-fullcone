:output;type filter hook output priority 0

*ip;test-ip4;output

# counter
%cnt1 type counter;ok
%cnt2 type counter;ok

ip saddr 192.168.1.3 counter name "cnt2";ok
ip saddr 192.168.1.3 counter name "cnt3";fail
counter name tcp dport map {443 : "cnt1", 80 : "cnt2", 22 : "cnt1"};ok

# quota
%qt1 type quota 25 mbytes;ok
%qt2 type quota over 1 kbytes;ok

ip saddr 192.168.1.3 quota name "qt1";ok
ip saddr 192.168.1.3 quota name "qt3";fail
quota name tcp dport map {443 : "qt1", 80 : "qt2", 22 : "qt1"};ok

# ct helper
%cthelp1 type ct helper { type \"ftp\" protocol tcp\; };ok
%cthelp2 type ct helper { type \"ftp\" protocol tcp\; l3proto ip6\; };fail

ct helper set "cthelp1";ok
ct helper set tcp dport map {21 : "cthelp1", 2121 : "cthelp1" };ok

# limit
%lim1 type limit rate 400/minute;ok
%lim2 type limit rate over 1024 bytes/second burst 512 bytes;ok

ip saddr 192.168.1.3 limit name "lim1";ok
ip saddr 192.168.1.3 limit name "lim3";fail
limit name tcp dport map {443 : "lim1", 80 : "lim2", 22 : "lim1"};ok
