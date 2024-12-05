/* Copyright 2012 Jun Wako <wakojun@gmail.com> */
/* Very basic print functions, intended to be used with usb_debug_only.c
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2008 PJRC.COM, LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "sendchar.h"
#include "progmem.h"

void print_set_sendchar(sendchar_func_t func);

/**
 * @brief This macro suppress format warnings for the function that is passed
 * in. The main use-case is that `b` format specifier for printing binary
 * numbers is not in the official C standard. Inclusion is planned for the
 * upcoming C2X C standard, but until then GCC will always output a warning for
 * a unknown format specifier.
 */
#define IGNORE_FORMAT_WARNING(func)                                \
    do {                                                           \
        _Pragma("GCC diagnostic push");                            \
        _Pragma("GCC diagnostic ignored \"-Wformat\"");            \
        _Pragma("GCC diagnostic ignored \"-Wformat-extra-args\""); \
        func;                                                      \
        _Pragma("GCC diagnostic pop");                             \
    } while (0)

#ifndef NO_PRINT
#    if __has_include_next("_print.h")
#        include_next "_print.h" /* Include the platforms print.h */
#    else
#        include "printf.h" // // Fall back to lib/printf/printf.h
#        define xprintf printf
#    endif
#else
// Remove print defines
#    undef xprintf
#    define xprintf(fmt, ...)
#endif

// Resolve before USER_PRINT can remove
#define uprintf xprintf

#ifdef USER_PRINT
// Remove normal print defines
#    undef xprintf
#    define xprintf(fmt, ...)
#endif

#define print(s) xprintf(s)
#define println(s) xprintf(s "\r\n")

#define print_dec(i) xprintf("%u", i)
#define print_decs(i) xprintf("%d", i)
/* hex */
#define print_hex4(i) xprintf("%X", i)
#define print_hex8(i) xprintf("%02X", i)
#define print_hex16(i) xprintf("%04X", i)
#define print_hex32(i) xprintf("%08lX", i)
/* binary */
#define print_bin4(i) IGNORE_FORMAT_WARNING(xprintf("%04b", i))
#define print_bin8(i) IGNORE_FORMAT_WARNING(xprintf("%08b", i))
#define print_bin16(i) IGNORE_FORMAT_WARNING(xprintf("%016b", i))
#define print_bin32(i) IGNORE_FORMAT_WARNING(xprintf("%032lb", i))
#define print_bin_reverse8(i) IGNORE_FORMAT_WARNING(xprintf("%08b", bitrev(i)))
#define print_bin_reverse16(i) IGNORE_FORMAT_WARNING(xprintf("%016b", bitrev16(i)))
#define print_bin_reverse32(i) IGNORE_FORMAT_WARNING(xprintf("%032lb", bitrev32(i)))
/* print value utility */
#define print_val_dec(v) xprintf(#v ": %u\n", v)
#define print_val_decs(v) xprintf(#v ": %d\n", v)
#define print_val_hex8(v) xprintf(#v ": %X\n", v)
#define print_val_hex16(v) xprintf(#v ": %02X\n", v)
#define print_val_hex32(v) xprintf(#v ": %04lX\n", v)
#define print_val_bin8(v) IGNORE_FORMAT_WARNING(xprintf(#v ": %08b\n", v))
#define print_val_bin16(v) IGNORE_FORMAT_WARNING(xprintf(#v ": %016b\n", v))
#define print_val_bin32(v) IGNORE_FORMAT_WARNING(xprintf(#v ": %032lb\n", v))
#define print_val_bin_reverse8(v) IGNORE_FORMAT_WARNING(xprintf(#v ": %08b\n", bitrev(v)))
#define print_val_bin_reverse16(v) IGNORE_FORMAT_WARNING(xprintf(#v ": %016b\n", bitrev16(v)))
#define print_val_bin_reverse32(v) IGNORE_FORMAT_WARNING(xprintf(#v ": %032lb\n", bitrev32(v)))

// User print disables the normal print messages in the body of QMK/TMK code and
// is meant as a lightweight alternative to NOPRINT. Use it when you only want to do
// a spot of debugging but lack flash resources for allowing all of the codebase to
// print (and store their wasteful strings).
//
// !!! DO NOT USE USER PRINT CALLS IN THE BODY OF QMK/TMK !!!

#define uprint(s) uprintf(s)
#define uprintln(s) uprintf(s "\r\n")

/* decimal */
#define uprint_dec(i) uprintf("%u", i)
#define uprint_decs(i) uprintf("%d", i)
/* hex */
#define uprint_hex4(i) uprintf("%X", i)
#define uprint_hex8(i) uprintf("%02X", i)
#define uprint_hex16(i) uprintf("%04X", i)
#define uprint_hex32(i) uprintf("%08lX", i)
/* binary */
#define uprint_bin4(i) IGNORE_FORMAT_WARNING(uprintf("%04b", i))
#define uprint_bin8(i) IGNORE_FORMAT_WARNING(uprintf("%08b", i))
#define uprint_bin16(i) IGNORE_FORMAT_WARNING(uprintf("%016b", i))
#define uprint_bin32(i) IGNORE_FORMAT_WARNING(uprintf("%032lb", i))
#define uprint_bin_reverse8(i) IGNORE_FORMAT_WARNING(uprintf("%08b", bitrev(i)))
#define uprint_bin_reverse16(i) IGNORE_FORMAT_WARNING(uprintf("%016b", bitrev16(i)))
#define uprint_bin_reverse32(i) IGNORE_FORMAT_WARNING(uprintf("%032lb", bitrev32(i)))
/* print value utility */
#define uprint_val_dec(v) uprintf(#v ": %u\n", v)
#define uprint_val_decs(v) uprintf(#v ": %d\n", v)
#define uprint_val_hex8(v) uprintf(#v ": %X\n", v)
#define uprint_val_hex16(v) uprintf(#v ": %02X\n", v)
#define uprint_val_hex32(v) uprintf(#v ": %04lX\n", v)
#define uprint_val_bin8(v) IGNORE_FORMAT_WARNING(uprintf(#v ": %08b\n", v))
#define uprint_val_bin16(v) IGNORE_FORMAT_WARNING(uprintf(#v ": %016b\n", v))
#define uprint_val_bin32(v) IGNORE_FORMAT_WARNING(uprintf(#v ": %032lb\n", v))
#define uprint_val_bin_reverse8(v) IGNORE_FORMAT_WARNING(uprintf(#v ": %08b\n", bitrev(v)))
#define uprint_val_bin_reverse16(v) IGNORE_FORMAT_WARNING(uprintf(#v ": %016b\n", bitrev16(v)))
#define uprint_val_bin_reverse32(v) IGNORE_FORMAT_WARNING(uprintf(#v ": %032lb\n", bitrev32(v)))
