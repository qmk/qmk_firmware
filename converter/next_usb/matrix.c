/*
NeXT non-ADB Keyboard USB Converter
 
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
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "util.h"
#include "serial.h"
#include "matrix.h"
#include "debug.h"
#include "matrix.h"
#include "next_kbd.h"

static void matrix_make(uint8_t code);
static void matrix_break(uint8_t code);

static uint8_t matrix[MATRIX_ROWS];
#define ROW(code)      ((code>>3)&0xF)
#define COL(code)      (code&0x07)

static bool is_modified = false;

/* number of matrix rows */
inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

/* number of matrix columns */
inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

#ifndef NEXT_KBD_LED1_ON
#define NEXT_KBD_LED1_ON
#endif

#ifndef NEXT_KBD_LED1_OFF
#define NEXT_KBD_LED1_OFF
#endif

#define NEXT_KBD_PWR_READ (NEXT_KBD_PWR_PIN&(1<<NEXT_KBD_PWR_BIT))

static bool power_state = false;

/* intialize matrix for scanning. should be called once. */
void matrix_init(void)
{
#ifdef DEBUG_ON_INIT
    debug_enable = true;
#endif

    // I've found that the matrix likes a little while for things to 
    // settle down before it gets started.  Not sure why :)
    _delay_ms(250);
    
    dprintf("[ Intializing NeXT keyboard ]\n");
    NEXT_KBD_LED1_DDR |=  (1<<NEXT_KBD_LED1_BIT);  // LED pin to output
    NEXT_KBD_LED1_ON;
    
    NEXT_KBD_PWR_DDR &= ~(1<<NEXT_KBD_PWR_BIT);  // Power Button pin to input
    NEXT_KBD_PWR_PIN |=  (1<<NEXT_KBD_PWR_BIT);  // KBD_PWR pull up
    
    power_state = NEXT_KBD_PWR_READ ? false : true;
    dprintf("Initial power button state: %b\n", power_state);
    
    next_kbd_init();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

#ifdef NEXT_KBD_INIT_FLASH_LEDS
    dprintf("flashing LEDs:");
    // flash the LEDs after initialization
    bool leds_on = true;
    for (uint8_t i = 0; i <= 6; i++)
    {
        leds_on = leds_on ? false : true;
        dprintf(" %b", leds_on); 
        next_kbd_set_leds(leds_on, leds_on);
        _delay_ms(250);
    }
    dprintf("\n");
#endif

    dprintf("[ NeXT keyboard initialized ]\n");

    return;
}

#define NEXT_KBD_KEYCODE(response)               (uint8_t)((response&0xFF)>>1)
#define NEXT_KBD_PRESSED_KEYCODE(response)       (uint8_t)(((response)&0xF00)==0x400)
#define NEXT_KBD_PRESSED(response, mask)         (uint8_t)(((response)&mask)>0)
#define NEXT_KBD_PRESSED_CONTROL(response)       NEXT_KBD_PRESSED(response,0x01000)
#define NEXT_KBD_PRESSED_SHIFT_LEFT(response)    NEXT_KBD_PRESSED(response,0x02000)
#define NEXT_KBD_PRESSED_SHIFT_RGHT(response)    NEXT_KBD_PRESSED(response,0x04000)
#define NEXT_KBD_PRESSED_CMD_LEFT(response)      NEXT_KBD_PRESSED(response,0x08000)
#define NEXT_KBD_PRESSED_CMD_RGHT(response)      NEXT_KBD_PRESSED(response,0x10000)
#define NEXT_KBD_PRESSED_ALT_LEFT(response)      NEXT_KBD_PRESSED(response,0x20000)
#define NEXT_KBD_PRESSED_ALT_RGHT(response)      NEXT_KBD_PRESSED(response,0x40000)
#define NEXT_KBD_MAKE_OR_BREAK(key, code) \
    do { \
        if (NEXT_KBD_PRESSED_##key(resp) > 0) \
            matrix_make(code); \
        else \
            matrix_break(code); \
    } while (0);

#define NEXT_KBD_PWR_KEYCODE 0x58

/* scan all key states on matrix */
uint8_t matrix_scan(void)
{
    _delay_ms(5);
    
    //next_kbd_set_leds(false, false);
    NEXT_KBD_LED1_OFF;
    
    is_modified = false;
    
    if (!NEXT_KBD_PWR_READ) {
        matrix_make(NEXT_KBD_PWR_KEYCODE);
        power_state = 1;
        if (is_modified)
        {
            dprintf("Power state 1\n");
            
        }
    } else {
        matrix_break(NEXT_KBD_PWR_KEYCODE);
        power_state = 0;
        if (is_modified)
        {
            dprintf("Power state 0\n");
            
        }
    }
    
    uint32_t resp = (next_kbd_recv());
    
    if (resp == NEXT_KBD_KMBUS_IDLE)
    {
        return 0;
    }
    
    NEXT_KBD_LED1_ON;
    
#ifdef NEXT_KBD_SHIFT_FLASH_LEDS
    next_kbd_set_leds(
        NEXT_KBD_PRESSED_SHIFT_LEFT(resp) ? true : false, 
        NEXT_KBD_PRESSED_SHIFT_RGHT(resp) ? true : false
    );
#endif
    
    dprintf("[ r=%04lX keycode=%02X pressed=%X CTRL=%X SHIFT_LEFT=%X SHIFT_RGHT=%X CMD_LEFT=%X CMD_RGHT=%X ALT_LEFT=%X ALT_RGHT=%X ]\n", \
        resp, \
        NEXT_KBD_KEYCODE(resp), \
        NEXT_KBD_PRESSED_KEYCODE(resp), \
        NEXT_KBD_PRESSED_CONTROL(resp), \
        NEXT_KBD_PRESSED_SHIFT_LEFT(resp), \
        NEXT_KBD_PRESSED_SHIFT_RGHT(resp), \
        NEXT_KBD_PRESSED_CMD_LEFT(resp), \
        NEXT_KBD_PRESSED_CMD_RGHT(resp), \
        NEXT_KBD_PRESSED_ALT_LEFT(resp), \
        NEXT_KBD_PRESSED_ALT_RGHT(resp) \
    );
    
    // Modifier keys don't return keycode; have to check the upper bits    
    NEXT_KBD_MAKE_OR_BREAK(ALT_RGHT,   0x51);
    NEXT_KBD_MAKE_OR_BREAK(ALT_LEFT,   0x52);
    NEXT_KBD_MAKE_OR_BREAK(CMD_RGHT,   0x53);
    NEXT_KBD_MAKE_OR_BREAK(CMD_LEFT,   0x54);
    NEXT_KBD_MAKE_OR_BREAK(SHIFT_RGHT, 0x55);
    NEXT_KBD_MAKE_OR_BREAK(SHIFT_LEFT, 0x56);
    NEXT_KBD_MAKE_OR_BREAK(CONTROL,    0x57);
    NEXT_KBD_MAKE_OR_BREAK(KEYCODE,    NEXT_KBD_KEYCODE(resp));
    
    return 1;
}

/* whether modified from previous scan. used after matrix_scan. */
bool matrix_is_modified()
{
    return is_modified;
}

/* whether a switch is on */
inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

/* matrix state on row */
inline
uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

/* print matrix for debug */
void matrix_print(void)
{
}

inline
static void matrix_make(uint8_t code)
{
    if (!matrix_is_on(ROW(code), COL(code))) {
        matrix[ROW(code)] |= 1<<COL(code);
        is_modified = true;
    }
}

inline
static void matrix_break(uint8_t code)
{
    if (matrix_is_on(ROW(code), COL(code))) {
        matrix[ROW(code)] &= ~(1<<COL(code));
        is_modified = true;
    }
}
