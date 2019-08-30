/* USB Keyboard Plus Debug Channel Example for Teensy USB Development Board
 * http://www.pjrc.com/teensy/usb_keyboard.html
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

#ifndef USB_EXTRA_H
#define USB_EXTRA_H 1
/*
 * Enhanced keyboard features for Windows:
 * Audio control and System control
 *
 * http://www.microsoft.com/whdc/archive/w2kbd.mspx
 */

#include <stdint.h>
#include "usb.h"

#define EXTRA_INTERFACE 3
#define EXTRA_ENDPOINT 4
#define EXTRA_SIZE 8
#define EXTRA_BUFFER EP_DOUBLE_BUFFER

int8_t usb_extra_consumer_send(uint16_t bits);
int8_t usb_extra_system_send(uint16_t bits);

#endif
