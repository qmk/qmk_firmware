/*

NeXT non-ADB Keyboard Protocol

Copyright 2013, Benjamin Gould (bgould@github.com)

Based on:
TMK firmware code Copyright 2011,2012 Jun WAKO <wakojun@gmail.com>
Arduino code by "Ladyada" Limor Fried (http://ladyada.net/, http://adafruit.com/), released under BSD license

Timing reference thanks to http://m0115.web.fc2.com/ (dead link), http://cfile7.uf.tistory.com/image/14448E464F410BF22380BB
Pinouts thanks to http://www.68k.org/~degs/nextkeyboard.html
Keycodes from http://ftp.netbsd.org/pub/NetBSD/NetBSD-release-6/src/sys/arch/next68k/dev/

This software is licensed with a Modified BSD License.
All of this is supposed to be Free Software, Open Source, DFSG-free,
GPL-compatible, and OK to use in both free and proprietary applications.
Additions and corrections to this file are welcome.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

* Neither the name of the copyright holders nor the names of
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#include <stdint.h>
#include <stdbool.h>
#include <util/atomic.h>
#include <util/delay.h>
#include "next_kbd.h"
#include "debug.h"

static inline void     out_lo(void);
static inline void     out_hi(void);
static inline void     query(void);
static inline void     reset(void);
static inline uint32_t response(void);

/* The keyboard sends signal with 50us pulse width on OUT line
 * while it seems to miss the 50us pulse on In line.
 * next_kbd_set_leds() often fails to sync LED status with 50us
 * but it works well with 51us(+1us) on TMK converter(ATMeaga32u2) at least.
 * TODO: test on Teensy and Pro Micro configuration
 */
#define out_hi_delay(intervals)                       \
    do {                                              \
        out_hi();                                     \
        _delay_us((NEXT_KBD_TIMING + 1) * intervals); \
    } while (0);
#define out_lo_delay(intervals)                       \
    do {                                              \
        out_lo();                                     \
        _delay_us((NEXT_KBD_TIMING + 1) * intervals); \
    } while (0);
#define query_delay(intervals)                        \
    do {                                              \
        query();                                      \
        _delay_us((NEXT_KBD_TIMING + 1) * intervals); \
    } while (0);
#define reset_delay(intervals)                        \
    do {                                              \
        reset();                                      \
        _delay_us((NEXT_KBD_TIMING + 1) * intervals); \
    } while (0);

void next_kbd_init(void) {
    out_hi();
    NEXT_KBD_IN_DDR &= ~(1 << NEXT_KBD_IN_BIT);  // KBD_IN  to input
    NEXT_KBD_IN_PORT |= (1 << NEXT_KBD_IN_BIT);  // KBD_IN  pull up

    query_delay(5);
    reset_delay(8);

    query_delay(5);
    reset_delay(8);
}

void next_kbd_set_leds(bool left, bool right) {
    cli();
    out_lo_delay(9);

    out_hi_delay(3);
    out_lo_delay(1);

    if (left) {
        out_hi_delay(1);
    } else {
        out_lo_delay(1);
    }

    if (right) {
        out_hi_delay(1);
    } else {
        out_lo_delay(1);
    }

    out_lo_delay(7);
    out_hi();
    sei();
}

#define NEXT_KBD_READ (NEXT_KBD_IN_PIN & (1 << NEXT_KBD_IN_BIT))
uint32_t next_kbd_recv(void) {
    // First check to make sure that the keyboard is actually connected;
    // if not, just return
    // TODO: reflect the status of the keyboard in a return code
    if (!NEXT_KBD_READ) {
        sei();
        return 0;
    }

    query();
    uint32_t resp = response();

    return resp;
}

static inline uint32_t response(void) {
    cli();

    // try a 5ms read; this should be called after the query method has
    // been run so if a key is pressed we should get a response within
    // 5ms; if not then send a reset and exit
    uint8_t  i             = 0;
    uint32_t data          = 0;
    uint16_t reset_timeout = 50000;
    while (NEXT_KBD_READ && reset_timeout) {
        asm("");
        _delay_us(1);
        reset_timeout--;
    }
    if (!reset_timeout) {
        reset();
        sei();
        return 0;
    }
    _delay_us(NEXT_KBD_TIMING / 2);
    for (; i < 22; i++) {
        if (NEXT_KBD_READ) {
            data |= ((uint32_t)1 << i);
            /* Note:
             * My testing with the ATmega32u4 showed that there might
             * something wrong with the timing here; by the end of the
             * second data byte some of the modifiers can get bumped out
             * to the next bit over if we just cycle through the data
             * based on the expected interval.  There is a bit (i = 10)
             * in the middle of the data that is always on followed by
             * one that is always off - so we'll use that to reset our
             * timing in case we've gotten ahead of the keyboard;
             */
            if (i == 10) {
                i++;
                while (NEXT_KBD_READ)
                    ;
                _delay_us(NEXT_KBD_TIMING / 2);
            }
        } else {
            /* redundant - but I don't want to remove if it might screw
             * up the timing
             */
            data |= ((uint32_t)0 << i);
        }
        _delay_us(NEXT_KBD_TIMING);
    }

    sei();

    return data;
}

static inline void out_lo(void) {
    NEXT_KBD_OUT_PORT &= ~(1 << NEXT_KBD_OUT_BIT);
    NEXT_KBD_OUT_DDR |= (1 << NEXT_KBD_OUT_BIT);
}

static inline void out_hi(void) {
    /* input with pull up */
    NEXT_KBD_OUT_DDR &= ~(1 << NEXT_KBD_OUT_BIT);
    NEXT_KBD_OUT_PORT |= (1 << NEXT_KBD_OUT_BIT);
}

static inline void query(void) {
    out_lo_delay(5);
    out_hi_delay(1);
    out_lo_delay(3);
    out_hi();
}

static inline void reset(void) {
    out_lo_delay(1);
    out_hi_delay(4);
    out_lo_delay(1);
    out_hi_delay(6);
    out_lo_delay(10);
    out_hi();
}
