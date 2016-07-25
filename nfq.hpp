#ifndef NFQ_H
#define NFQ_H

#include <netinet/in.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <stdexcept>

#define NFQ_BUFSIZ 16384

#define call(expr, act) if ((expr) < 0) {throw std::runtime_error(act);}

typedef uint32_t (*handler_t)(uint8_t* &data, size_t &size);

struct NFQ {
        nfq_handle* h;
        nfq_q_handle* qh;
        bool stop;
        NFQ(int qnum, handler_t foo);
        void run();
};

#endif
