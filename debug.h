#ifndef DEBUG_H
#define DEBUG_H 1

#include "print.h"


#define debug(s)             if(debug_enable) print(s)
#define debug_hex(c)         if(debug_enable) phex(c)
#define debug_hex16(i)       if(debug_enable) phex(i)
#define debug_bin(c)         if(debug_enable) pbin(c)
#define debug_bin_reverse(c) if(debug_enable) pbin_reverse(c)


bool debug_enable;
bool debug_matrix;
bool debug_keyboard;
bool debug_mouse;

#endif
