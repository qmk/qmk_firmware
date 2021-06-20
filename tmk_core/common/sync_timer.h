/*
Copyright (C) 2020 Ryan Caltabiano <https://github.com/XScorpion2>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

If you happen to meet one of the copyright holders in a bar you are obligated
to buy them one pint of beer.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <stdint.h>
#include "timer.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(SPLIT_KEYBOARD) || defined(SERIAL_LINK_ENABLE)) && !defined(DISABLE_SYNC_TIMER)
void     sync_timer_init(void);
void     sync_timer_update(uint32_t time);
uint16_t sync_timer_read(void);
uint32_t sync_timer_read32(void);
uint16_t sync_timer_elapsed(uint16_t last);
uint32_t sync_timer_elapsed32(uint32_t last);
#else
#    define sync_timer_init()
#    define sync_timer_clear()
#    define sync_timer_update(t)
#    define sync_timer_read() timer_read()
#    define sync_timer_read32() timer_read32()
#    define sync_timer_elapsed(t) timer_elapsed(t)
#    define sync_timer_elapsed32(t) timer_elapsed32(t)
#endif

#ifdef __cplusplus
}
#endif
