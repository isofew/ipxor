#include "nfq.hpp"

int callback(nfq_q_handle* qh, nfgenmsg* nfmsg, nfq_data* nfad, void* handler)
{
        uint8_t* data;
        size_t size = nfq_get_payload(nfad, &data);

        uint32_t verdict = ((handler_t)handler)(data, size);

        nfqnl_msg_packet_hdr *ph = nfq_get_msg_packet_hdr(nfad);
        return nfq_set_verdict(qh, ntohl(ph->packet_id), verdict, size, data);
}

NFQ::NFQ(int qnum, handler_t handler)
{
        call(h = nfq_open(), "open nfqueue handle");
        call(nfq_unbind_pf(h, AF_INET), "unbind existing nfqueue handler");
        call(nfq_bind_pf(h, AF_INET), "bind handler");
        call(qh = nfq_create_queue(h, qnum, &callback, (void*)handler), "create queue");
        call(nfq_set_mode(qh, NFQNL_COPY_PACKET, 65535), "set copy_packet");
}

void NFQ::run()
{
        char buf[NFQ_BUFSIZ] __attribute__ ((aligned));
        int fd = nfq_fd(h), n;

        stop = false;
        while ((n = recv(fd, buf, sizeof(buf), 0)) > 0 && !stop)
                nfq_handle_packet(h, buf, n);

        nfq_destroy_queue(qh);
        nfq_close(h);
}
