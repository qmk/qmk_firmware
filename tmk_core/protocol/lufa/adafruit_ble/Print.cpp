/*
  Modified from the original Print.h which was released under
  the BSD License (below).

  Copyright (c) 2020 Joshua Rubin
  Copyright (c) 2008 David A. Mellis
  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <math.h>
#include "Print.h"

// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */
size_t Print::write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    while (size--) {
        if (write(*buffer++))
            n++;
        else
            break;
    }
    return n;
}

size_t Print::pprint(const __FlashStringHelper *ifsh) {
    PGM_P  p = reinterpret_cast<PGM_P>(ifsh);
    size_t n = 0;
    while (1) {
        unsigned char c = pgm_read_byte(p++);
        if (c == 0) break;
        if (write(c))
            n++;
        else
            break;
    }
    return n;
}

size_t Print::pprint(const char str[]) { return write(str); }

size_t Print::pprint(char c) { return write(c); }

size_t Print::pprint(unsigned char b, int base) { return pprint((unsigned long)b, base); }

size_t Print::pprint(int n, int base) { return pprint((long)n, base); }

size_t Print::pprint(unsigned int n, int base) { return pprint((unsigned long)n, base); }

size_t Print::pprint(long n, int base) {
    if (base == 0) {
        return write(n);
    } else if (base == 10) {
        if (n < 0) {
            int t = pprint('-');
            n     = -n;
            return printNumber(n, 10) + t;
        }
        return printNumber(n, 10);
    } else {
        return printNumber(n, base);
    }
}

size_t Print::pprint(unsigned long n, int base) {
    if (base == 0)
        return write(n);
    else
        return printNumber(n, base);
}

size_t Print::pprint(double n, int digits) { return printFloat(n, digits); }

size_t Print::pprintln(const __FlashStringHelper *ifsh) {
    size_t n = pprint(ifsh);
    n += pprintln();
    return n;
}

size_t Print::pprintln(void) { return write("\r\n"); }

size_t Print::pprintln(const char c[]) {
    size_t n = pprint(c);
    n += pprintln();
    return n;
}

size_t Print::pprintln(char c) {
    size_t n = pprint(c);
    n += pprintln();
    return n;
}

size_t Print::pprintln(unsigned char b, int base) {
    size_t n = pprint(b, base);
    n += pprintln();
    return n;
}

size_t Print::pprintln(int num, int base) {
    size_t n = pprint(num, base);
    n += pprintln();
    return n;
}

size_t Print::pprintln(unsigned int num, int base) {
    size_t n = pprint(num, base);
    n += pprintln();
    return n;
}

size_t Print::pprintln(long num, int base) {
    size_t n = pprint(num, base);
    n += pprintln();
    return n;
}

size_t Print::pprintln(unsigned long num, int base) {
    size_t n = pprint(num, base);
    n += pprintln();
    return n;
}

size_t Print::pprintln(double num, int digits) {
    size_t n = pprint(num, digits);
    n += pprintln();
    return n;
}

// Private Methods /////////////////////////////////////////////////////////////

size_t Print::printNumber(unsigned long n, uint8_t base) {
    char  buf[8 * sizeof(long) + 1];  // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    // prevent crash if called with base == 1
    if (base < 2) base = 10;

    do {
        char c = n % base;
        n /= base;

        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while (n);

    return write(str);
}

size_t Print::printFloat(double number, uint8_t digits) {
    size_t n = 0;

    if (isnan(number)) return pprint("nan");
    if (isinf(number)) return pprint("inf");
    if (number > 4294967040.0) return pprint("ovf");   // constant determined empirically
    if (number < -4294967040.0) return pprint("ovf");  // constant determined empirically

    // Handle negative numbers
    if (number < 0.0) {
        n += pprint('-');
        number = -number;
    }

    // Round correctly so that pprint(1.999, 2) prints as "2.00"
    double rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i) rounding /= 10.0;

    number += rounding;

    // Extract the integer part of the number and print it
    unsigned long int_part  = (unsigned long)number;
    double        remainder = number - (double)int_part;
    n += pprint(int_part);

    // Print the decimal point, but only if there are digits beyond
    if (digits > 0) {
        n += pprint('.');
    }

    // Extract digits from the remainder one at a time
    while (digits-- > 0) {
        remainder *= 10.0;
        unsigned int toPrint = (unsigned int)(remainder);
        n += pprint(toPrint);
        remainder -= toPrint;
    }

    return n;
}
