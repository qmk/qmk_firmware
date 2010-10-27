#ifndef UTIL_H
#define UTIL_H 1

#include <stdint.h>

// convert to L string
#define LSTR(s) XLSTR(s)
#define XLSTR(s) L ## #s
// convert to string
#define STR(s) XSTR(s)
#define XSTR(s) #s


int bitpop(uint8_t bits);
int biton(uint8_t bits);

#endif
