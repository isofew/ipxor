#include "nfq.hpp"
#include <stdlib.h>
#include <string.h>
#include <tins/tins.h>
using namespace Tins;

char* key;
size_t klen;

void mask(uint8_t* data, size_t size)
{
        for (size_t i = 0, j = 0; i < size; ++i, ++j) {
                if (j == klen) j = 0;
                data[i] ^= key[j];
        }
}

inline uint8_t ver(uint8_t b) {
        return (b & 0xf0) >> 4;
}

int offset;
uint32_t ipxor(uint8_t* &data, size_t &size)
{
        mask(data + offset, size - offset);
        // re-calculate checksums
        auto vec = IP(data, size).serialize();
        memcpy(data, vec.data(), size);
        return NF_ACCEPT;
}

int main(int argc, char* argv[])
{
        offset = atoi(argv[3]);

        key = argv[2];
        klen = strlen(key);

        int qnum = atoi(argv[1]);
        NFQ(qnum, ipxor).run();

        return 0;
}
