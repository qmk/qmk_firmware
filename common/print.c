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

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "print.h"
#define sendchar(c)    do { if (print_enable && print_sendchar_func) (print_sendchar_func)(c); } while (0)


int8_t (*print_sendchar_func)(uint8_t) = NULL;
bool print_enable = false;

/* print string stored in data memory(SRAM)
 *     print_P("hello world");
 * This consumes precious SRAM memory space for string.
 */
void print_S(const char *s)
{
    uint8_t c;
    while (1) {
        c = *s++;
        if (!c) break;
        if (c == '\n') sendchar('\r');
        sendchar(c);
    }
}

/* print string stored in program memory(FLASH)
 *     print_P(PSTR("hello world");
 * This consumes relatively abundant FLASH memory area not SRAM.
 */
void print_P(const char *s)
{
    uint8_t c;
    while (1) {
        c = pgm_read_byte(s++);
        if (!c) break;
        if (c == '\n') sendchar('\r');
        sendchar(c);
    }
}

static inline
void print_hex4(uint8_t data)
{
    sendchar(data + ((data < 10) ? '0' : 'A' - 10));
}

void print_hex8(uint8_t data)
{
    print_hex4(data>>4);
    print_hex4(data&0x0F);
}

void print_hex16(uint16_t data)
{
    print_hex8(data>>8);
    print_hex8(data);
}

void print_hex32(uint32_t data)
{
    print_hex16(data>>16);
    print_hex16(data);
}

void print_dec8(uint8_t data)
{
    if (data/100) sendchar('0' + (data/100));
    if (data/100 || data%100/10) sendchar('0' + (data%100/10));
    sendchar('0' + (data%10));
}

void print_dec16(uint16_t data)
{
    // TODO
}

void print_dec32(uint32_t data)
{
    // TODO
}

void print_bin(uint8_t data)
{
    for (int i = 7; i >= 0; i--) {
        sendchar((data & (1<<i)) ? '1' : '0');
    }
}

void print_bin16(uint16_t data)
{
    print_bin8(data>>8);
    print_bin8(data);
}

void print_bin32(uint32_t data)
{
    print_bin8(data>>24);
    print_bin8(data>>16);
    print_bin8(data>>8);
    print_bin8(data);
}

void print_bin_reverse8(uint8_t data)
{
    for (int i = 0; i < 8; i++) {
        sendchar((data & (1<<i)) ? '1' : '0');
    }
}

void print_bin_reverse16(uint16_t data)
{
    print_bin_reverse8(data);
    print_bin_reverse8(data>>8);
}

void print_bin_reverse32(uint32_t data)
{
    print_bin_reverse8(data);
    print_bin_reverse8(data>>8);
    print_bin_reverse8(data>>16);
    print_bin_reverse8(data>>24);
}
