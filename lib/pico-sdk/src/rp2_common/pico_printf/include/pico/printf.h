///////////////////////////////////////////////////////////////////////////////
// \author (c) Marco Paland (info@paland.com)
//             2014-2019, PALANDesign Hannover, Germany
//
// \license The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// \brief Tiny printf, sprintf and snprintf implementation, optimized for speed on
//        embedded systems with a very limited resources.
//        Use this instead of bloated standard/newlib printf.
//        These routines are thread safe and reentrant.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PICO_PRINTF_H
#define _PICO_PRINTF_H

/** \file printf.h
 *  \defgroup pico_printf pico_printf
 *
 * Compact replacement for printf by Marco Paland (info@paland.com)
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "pico.h"
#include <stdio.h>
#include <stdarg.h>

// PICO_CONFIG: PICO_PRINTF_ALWAYS_INCLUDED, Whether to always include printf code even if only called weakly (by panic), type=bool, default=1 in debug build 0 otherwise, group=pico_printf
#ifndef PICO_PRINTF_ALWAYS_INCLUDED
#ifndef NDEBUG
#define PICO_PRINTF_ALWAYS_INCLUDED 1
#else
#define PICO_PRINTF_ALWAYS_INCLUDED 0
#endif
#endif

#if LIB_PICO_PRINTF_PICO
// weak raw printf may be a puts if printf has not been called,
// so that we can support gc of printf when it isn't called
//
// it is called raw to distinguish it from the regular printf which
// is in stdio.c and does mutex protection
#if !PICO_PRINTF_ALWAYS_INCLUDED
bool __printflike(1, 0) weak_raw_printf(const char *fmt, ...);
bool weak_raw_vprintf(const char *fmt, va_list args);
#else
#define weak_raw_printf(...) ({printf(__VA_ARGS__); true;})
#define weak_raw_vprintf(fmt,va) ({vprintf(fmt,va); true;})
#endif

/**
 * printf with output function
 * You may use this as dynamic alternative to printf() with its fixed _putchar() output
 * \param out An output function which takes one character and an argument pointer
 * \param arg An argument pointer for user data passed to output function
 * \param format A string that specifies the format of the output
 * \return The number of characters that are sent to the output function, not counting the terminating null character
 */
int vfctprintf(void (*out)(char character, void *arg), void *arg, const char *format, va_list va);

#else

#define weak_raw_printf(...) ({printf(__VA_ARGS__); true;})
#define weak_raw_vprintf(fmt,va) ({vprintf(fmt,va); true;})

#endif

#ifdef __cplusplus
}
#endif

#endif  // _PRINTF_H_
