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

#ifndef PRINT_H__
#define PRINT_H__ 1

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>


// this macro allows you to write print("some text") and
// the string is automatically placed into flash memory :)
// TODO: avoid collision with arduino/Print.h
#ifndef __cplusplus
#define print(s)                print_P(PSTR(s))
#endif
#define println(s)              print_P(PSTR(s "\n"))

/* for old name */
#define pdec(data)              print_dec(data)
#define pdec16(data)            print_dec(data)
#define phex(data)              print_hex8(data)
#define phex16(data)            print_hex16(data)
#define pbin(data)              print_bin8(data)
#define pbin16(data)            print_bin16(data)
#define pbin_reverse(data)      print_bin_reverse8(data)
#define pbin_reverse16(data)    print_bin_reverse16(data)

/* print value utility */
#define print_val_dec(v)           do { print_P(PSTR(#v ": ")); print_dec(v);  print_P(PSTR("\n")); } while (0)
#define print_val_decs(v)          do { print_P(PSTR(#v ": ")); print_decs(v);  print_P(PSTR("\n")); } while (0)
#define print_val_hex8(v)          do { print_P(PSTR(#v ": ")); print_hex8(v);  print_P(PSTR("\n")); } while (0)
#define print_val_hex16(v)         do { print_P(PSTR(#v ": ")); print_hex16(v); print_P(PSTR("\n")); } while (0)
#define print_val_hex32(v)         do { print_P(PSTR(#v ": ")); print_hex32(v); print_P(PSTR("\n")); } while (0)
#define print_val_bin8(v)          do { print_P(PSTR(#v ": ")); print_bin8(v);  print_P(PSTR("\n")); } while (0)
#define print_val_bin16(v)         do { print_P(PSTR(#v ": ")); print_bin16(v); print_P(PSTR("\n")); } while (0)
#define print_val_bin32(v)         do { print_P(PSTR(#v ": ")); print_bin32(v); print_P(PSTR("\n")); } while (0)
#define print_val_bin_reverse8(v)  do { print_P(PSTR(#v ": ")); print_bin_reverse8(v);  print_P(PSTR("\n")); } while (0)
#define print_val_bin_reverse16(v) do { print_P(PSTR(#v ": ")); print_bin_reverse16(v); print_P(PSTR("\n")); } while (0)
#define print_val_bin_reverse32(v) do { print_P(PSTR(#v ": ")); print_bin_reverse32(v); print_P(PSTR("\n")); } while (0)



#ifndef NO_PRINT

#ifdef __cplusplus
extern "C" {
#endif
/* function pointer of sendchar to be used by print utility */
void print_set_sendchar(int8_t (*print_sendchar_func)(uint8_t));

/* print string stored in data memory(SRAM) */
void print_S(const char *s);
/* print string stored in program memory(FLASH) */
void print_P(const char *s);

void print_CRLF(void);

/* decimal */
void print_dec(uint16_t data);
void print_decs(int16_t data);

/* hex */
void print_hex4(uint8_t data);
void print_hex8(uint8_t data);
void print_hex16(uint16_t data);
void print_hex32(uint32_t data);

/* binary */
void print_bin4(uint8_t data);
void print_bin8(uint8_t data);
void print_bin16(uint16_t data);
void print_bin32(uint32_t data);
void print_bin_reverse8(uint8_t data);
void print_bin_reverse16(uint16_t data);
void print_bin_reverse32(uint32_t data);
#ifdef __cplusplus
}
#endif

#else

#define print_set_sendchar(func)
#define print_S(s)
#define print_P(s)
#define print_CRLF()
#define print_dec(data)
#define print_decs(data)
#define print_hex4(data)
#define print_hex8(data)
#define print_hex16(data)
#define print_hex32(data)
#define print_bin4(data)
#define print_bin8(data)
#define print_bin16(data)
#define print_bin32(data)
#define print_bin_reverse8(data)
#define print_bin_reverse16(data)
#define print_bin_reverse32(data)

#endif


#endif
