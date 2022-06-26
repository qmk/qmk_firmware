/*---------------------------------------------------------------------------
   Extended itoa, puts and printf                    (C)ChaN, 2011
-----------------------------------------------------------------------------*/

#pragma once

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void (*xfunc_out)(uint8_t);
#define xdev_out(func) xfunc_out = (void (*)(uint8_t))(func)

/* This is a pointer to user defined output function. It must be initialized
   before using this modle.
*/

void xputc(char chr);

/* This is a stub function to forward outputs to user defined output function.
   All outputs from this module are output via this function.
*/

/*-----------------------------------------------------------------------------*/
void xputs(const char *string_p);

/*  The string placed in the ROM is forwarded to xputc() directly.
 */

/*-----------------------------------------------------------------------------*/
void xitoa(long value, char radix, char width);

/* Extended itoa().

      value  radix  width   output
        100     10      6   "   100"
        100     10     -6   "000100"
        100     10      0   "100"
 4294967295     10      0   "4294967295"
 4294967295    -10      0   "-1"
     655360     16     -8   "000A0000"
       1024     16      0   "400"
       0x55      2     -8   "01010101"
*/

/*-----------------------------------------------------------------------------*/
#define xprintf(format, ...) __xprintf(PSTR(format), ##__VA_ARGS__)
#define xsprintf(str, format, ...) __xsprintf(str, PSTR(format), ##__VA_ARGS__)
#define xfprintf(func, format, ...) __xfprintf(func, PSTR(format), ##__VA_ARGS__)

void __xprintf(const char *format_p, ...); /* Send formatted string to the registered device */
// void __xsprintf(char*, const char *format_p, ...);	/* Put formatted string to the memory */
// void __xfprintf(void(*func)(uint8_t), const char *format_p, ...); /* Send formatted string to the specified device */

/* Format string is placed in the ROM. The format flags is similar to printf().

   %[flag][width][size]type

   flag
     A '0' means filled with '0' when output is shorter than width.
     ' ' is used in default. This is effective only numeral type.
   width
     Minimum width in decimal number. This is effective only numeral type.
     Default width is zero.
   size
     A 'l' means the argument is long(32bit). Default is short(16bit).
     This is effective only numeral type.
   type
     'c' : Character, argument is the value
     's' : String placed on the RAM, argument is the pointer
     'S' : String placed on the ROM, argument is the pointer
     'd' : Signed decimal, argument is the value
     'u' : Unsigned decimal, argument is the value
     'X' : Hexdecimal, argument is the value
     'b' : Binary, argument is the value
     '%' : '%'

*/

/*-----------------------------------------------------------------------------*/
char xatoi(char **str, long *ret);

/* Get value of the numeral string.

  str
    Pointer to pointer to source string

    "0b11001010" binary
    "0377" octal
    "0xff800" hexdecimal
    "1250000" decimal
    "-25000" decimal

  ret
    Pointer to return value
*/

#ifdef __cplusplus
}
#endif
