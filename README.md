ipxor
------
use libnetfilter_queue to xor-mask ip packets

(There's an XOR target in iptables before, but I can't find it anymore, so I
write this little tool.)

### Usage

First, create a new chain IPXOR
```bash
iptables -t raw -N IPXOR
iptables -t raw -I IPXOR -j NFQUEUE --queue-bypass --queue-num [qnum]
```
Then, add your desired rules to IPXOR target
```bash
iptables -t raw -I PREROUTING [filter] -j IPXOR
iptables -t raw -I OUTPUT [filter] -j IPXOR
```
Run ipxor and packets will be masked by key
```bash
ipxor [qnum] [key]
```

### Dependencies

 * [libnetfilter_queue](http://www.netfilter.org/projects/libnetfilter_queue) for receiving / injecting packets

### TODO

 * take ip options into account (the header size is fixed for now)
