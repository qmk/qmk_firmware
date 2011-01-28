#ifndef PRINT_H__
#define PRINT_H__ 1

#include <stdbool.h>
#include <avr/pgmspace.h>


extern bool print_enable;

// this macro allows you to write print("some text") and
// the string is automatically placed into flash memory :)
#define print(s) print_P(PSTR(s))

void print_P(const char *s);
void phex(unsigned char c);
void phex16(unsigned int i);
void pbin(unsigned char c);
void pbin_reverse(unsigned char c);

#endif
