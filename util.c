#include "util.h"

// bit population
int bitpop(uint8_t bits)
{
    int c;
    for (c = 0; bits; c++)
        bits &= bits -1;
    return c;
}

// most significant on-bit
int biton(uint8_t bits)
{
    int n = 0;
    if (bits >> 4) { bits >>= 4; n += 4;}
    if (bits >> 2) { bits >>= 2; n += 2;}
    if (bits >> 1) { bits >>= 1; n += 1;}
    return n;
}
