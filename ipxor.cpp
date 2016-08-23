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

int offset = 0;
uint32_t ipxor(uint8_t* &data, size_t &size)
{
	switch (ver(data[0])) {
	case 4:
                mask(data + 20 + offset, size - 20 - offset);
		return NF_ACCEPT;
	case 6:
                mask(data + 40 + offset, size - 40 - offset);
		return NF_ACCEPT;
	}
	return NF_DROP;
}

int main(int argc, char* argv[])
{
	if (argc > 3)
		offset = atoi(argv[3]);

        key = argv[2];
        klen = strlen(key);

        int qnum = atoi(argv[1]);
        NFQ(qnum, ipxor).run();

        return 0;
}
