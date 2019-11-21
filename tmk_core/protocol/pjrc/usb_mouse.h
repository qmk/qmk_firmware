/* USB Mouse Plus Debug Channel Example for Teensy USB Development Board
 * http://www.pjrc.com/teensy/usb_mouse.html
 * Copyright (c) 2009 PJRC.COM, LLC
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

#ifndef USB_MOUSE_H
#define USB_MOUSE_H 1

#include <stdint.h>
#include <stdbool.h>
#include "usb.h"

#define MOUSE_INTERFACE 1
#define MOUSE_ENDPOINT 2
#define MOUSE_SIZE 8
#define MOUSE_BUFFER EP_SINGLE_BUFFER

#define MOUSE_BTN1 (1 << 0)
#define MOUSE_BTN2 (1 << 1)
#define MOUSE_BTN3 (1 << 2)
#define MOUSE_BTN4 (1 << 3)
#define MOUSE_BTN5 (1 << 4)

extern uint8_t usb_mouse_protocol;

int8_t usb_mouse_send(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons);
void   usb_mouse_print(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons);

#endif
