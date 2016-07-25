#include "nfq.hpp"
#include <stdlib.h>
#include <string.h>

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

uint32_t ipxor(uint8_t* &data, size_t &size)
{
	switch (ver(data[0])) {
	case 4:
                mask(data + 20, size - 20);
		return NF_ACCEPT;
	case 6:
                mask(data + 40, size - 40);
		return NF_ACCEPT;
	}
	return NF_DROP;
}

int main(int argc, char* argv[])
{
        key = argv[2];
        klen = strlen(key);

        int qnum = atoi(argv[1]);
        NFQ(qnum, ipxor).run();

        return 0;
}
