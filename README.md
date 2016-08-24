ipxor
------
use libnetfilter_queue to xor-mask ip packets

### Usage

```bash
iptables -t [table] -N IPXOR
iptables -t [table] -I IPXOR -j NFQUEUE --queue-bypass --queue-num [qnum]
iptables -t [tanle] -I [chain] [filter] -j IPXOR

ipxor [qnum] [key] [offset]
```
Packets captured by [filter] will be directed to IPXOR.
Data starting from [offset] will be masked by [key]

### Dependencies

 * [libnetfilter_queue](http://www.netfilter.org/projects/libnetfilter_queue) for receiving / injecting packets
