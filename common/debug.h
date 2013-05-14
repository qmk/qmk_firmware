/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DEBUG_H
#define DEBUG_H 1

#include "print.h"
#include "debug_config.h"


#ifndef NO_DEBUG

#define dprint(s)           do { if (debug_enable) print(s); } while (0)
#define dprintln()          do { if (debug_enable) print_crlf(); } while (0)
#define dprintf(fmt, ...)   do { if (debug_enable) __xprintf(PSTR(fmt), ##__VA_ARGS__); } while (0)
#define dmsg(s)             dprintf("%s at %s: %S\n", __FILE__, __LINE__, PSTR(s))

/* DO NOT USE these anymore */
#define debug(s)                  do { if (debug_enable) print(s); } while (0)
#define debugln(s)                do { if (debug_enable) print_crlf(); } while (0)
#define debug_S(s)                do { if (debug_enable) print_S(s); } while (0)
#define debug_P(s)                do { if (debug_enable) print_P(s); } while (0)
#define debug_msg(s)              do { \
    if (debug_enable) { \
        print(__FILE__); print(" at "); print_dec(__LINE__); print(" in "); print(": "); print(s); \
    } \
} while (0)
#define debug_dec(data)           do { if (debug_enable) print_dec(data); } while (0)
#define debug_decs(data)          do { if (debug_enable) print_decs(data); } while (0)
#define debug_hex4(data)          do { if (debug_enable) print_hex4(data); } while (0)
#define debug_hex8(data)          do { if (debug_enable) print_hex8(data); } while (0)
#define debug_hex16(data)         do { if (debug_enable) print_hex16(data); } while (0)
#define debug_hex32(data)         do { if (debug_enable) print_hex32(data); } while (0)
#define debug_bin8(data)          do { if (debug_enable) print_bin8(data); } while (0)
#define debug_bin16(data)         do { if (debug_enable) print_bin16(data); } while (0)
#define debug_bin32(data)         do { if (debug_enable) print_bin32(data); } while (0)
#define debug_bin_reverse8(data)  do { if (debug_enable) print_bin_reverse8(data); } while (0)
#define debug_bin_reverse16(data) do { if (debug_enable) print_bin_reverse16(data); } while (0)
#define debug_bin_reverse32(data) do { if (debug_enable) print_bin_reverse32(data); } while (0)
#define debug_hex(data)           debug_hex8(data)
#define debug_bin(data)           debug_bin8(data)
#define debug_bin_reverse(data)   debug_bin8(data)

#else
#include "nodebug.h"
#endif

#endif
