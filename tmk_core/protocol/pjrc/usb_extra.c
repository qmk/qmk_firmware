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

#include <util/delay.h>
#include <avr/interrupt.h>
#include "host.h"
#include "usb_extra.h"

int8_t usb_extra_send(uint8_t report_id, uint16_t data) {
    uint8_t intr_state, timeout;

    if (!usb_configured()) return -1;
    intr_state = SREG;
    cli();
    UENUM   = EXTRA_ENDPOINT;
    timeout = UDFNUML + 50;
    while (1) {
        // are we ready to transmit?
        if (UEINTX & (1 << RWAL)) break;
        SREG = intr_state;
        // has the USB gone offline?
        if (!usb_configured()) return -1;
        // have we waited too long?
        if (UDFNUML == timeout) return -1;
        // get ready to try checking again
        intr_state = SREG;
        cli();
        UENUM = EXTRA_ENDPOINT;
    }

    UEDATX = report_id;
    UEDATX = data & 0xFF;
    UEDATX = (data >> 8) & 0xFF;

    UEINTX = 0x3A;
    SREG   = intr_state;
    return 0;
}

int8_t usb_extra_consumer_send(uint16_t bits) { return usb_extra_send(REPORT_ID_CONSUMER, bits); }

int8_t usb_extra_system_send(uint16_t bits) { return usb_extra_send(REPORT_ID_SYSTEM, bits); }
