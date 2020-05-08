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

#pragma once

#include <stdio.h>  // for size_t
#include <string.h>
#include <avr/pgmspace.h>

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN  // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
#    undef BIN
#endif
#define BIN 2

class __FlashStringHelper;
#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))

class Print {
   private:
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);

   public:
    Print() {}

    virtual size_t write(uint8_t) = 0;
    size_t         write(const char *str) {
        if (str == NULL) return 0;
        return write((const uint8_t *)str, strlen(str));
    }
    virtual size_t write(const uint8_t *buffer, size_t size);
    size_t         write(const char *buffer, size_t size) { return write((const uint8_t *)buffer, size); }

    // default to zero, meaning "a single write may block"
    // should be overriden by subclasses with buffering
    virtual int availableForWrite() { return 0; }

    size_t pprint(const __FlashStringHelper *);
    size_t pprint(const char[]);
    size_t pprint(char);
    size_t pprint(unsigned char, int = DEC);
    size_t pprint(int, int = DEC);
    size_t pprint(unsigned int, int = DEC);
    size_t pprint(long, int = DEC);
    size_t pprint(unsigned long, int = DEC);
    size_t pprint(double, int = 2);

    size_t pprintln(const __FlashStringHelper *);
    size_t pprintln(const char[]);
    size_t pprintln(char);
    size_t pprintln(unsigned char, int = DEC);
    size_t pprintln(int, int = DEC);
    size_t pprintln(unsigned int, int = DEC);
    size_t pprintln(long, int = DEC);
    size_t pprintln(unsigned long, int = DEC);
    size_t pprintln(double, int = 2);
    size_t pprintln(void);

    /* Empty implementation for backward compatibility */
    virtual void flush() {}
};
