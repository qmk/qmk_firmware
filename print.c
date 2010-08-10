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

// Version 1.0: Initial Release

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "print.h"

void print_P(const char *s)
{
	char c;

	while (1) {
		c = pgm_read_byte(s++);
		if (!c) break;
		if (c == '\n') usb_debug_putchar('\r');
		usb_debug_putchar(c);
	}
}

void phex1(unsigned char c)
{
	usb_debug_putchar(c + ((c < 10) ? '0' : 'A' - 10));
}

void phex(unsigned char c)
{
	phex1(c >> 4);
	phex1(c & 15);
}

void phex16(unsigned int i)
{
	phex(i >> 8);
	phex(i);
}




