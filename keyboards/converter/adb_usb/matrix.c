/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Ported to QMK by Peter Roe <pete@13bit.me>
*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "util.h"
#include "debug.h"
#include "adb.h"
#include "matrix.h"
#include "report.h"
#include "host.h"
#include "led.h"
#include "timer.h"

#ifndef ADB_MOUSE_MAXACC
#    define ADB_MOUSE_MAXACC 8
#endif

static bool is_iso_layout = false;

// matrix state buffer(1:on, 0:off)
static matrix_row_t matrix[MATRIX_ROWS];

static void register_key(uint8_t key);

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void)
{
    adb_host_init();

    // wait for keyboard to boot up and receive command
    _delay_ms(2000);

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;
    // print("debug enabled.\n");

    matrix_init_quantum();
}

#ifdef ADB_MOUSE_ENABLE

#ifdef MAX
#undef MAX
#endif
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

static report_mouse_t mouse_report = {};

void housekeeping_task_kb(void) {
    adb_mouse_task();
}

void adb_mouse_task(void)
{
    uint16_t codes;
    int16_t x, y;
    static int8_t mouseacc;

    /* tick of last polling */
    static uint16_t tick_ms;

    // polling with 12ms interval
    if (timer_elapsed(tick_ms) < 12) return;
    tick_ms = timer_read();

    codes = adb_host_mouse_recv();
    // If nothing received reset mouse acceleration, and quit.
    if (!codes) {
        mouseacc = 1;
        return;
    };
    // Bit sixteen is button.
    if (~codes & (1 << 15))
        mouse_report.buttons |= MOUSE_BTN1;
    if (codes & (1 << 15))
        mouse_report.buttons &= ~MOUSE_BTN1;
    // lower seven bits are movement, as signed int_7.
    // low byte is X-axis, high byte is Y.
    y = (codes>>8 & 0x3F);
    x = (codes>>0 & 0x3F);
    // bit seven and fifteen is negative
    // usb does not use int_8, but int_7 (measuring distance) with sign-bit.
    if (codes & (1 << 6))
          x = (x-0x40);
    if (codes & (1 << 14))
         y = (y-0x40);
    // Accelerate mouse. (They weren't meant to be used on screens larger than 320x200).
    x *= mouseacc;
    y *= mouseacc;
    // Cap our two bytes per axis to one byte.
    // Easier with a MIN-function, but since -MAX(-a,-b) = MIN(a,b)...
	 // I.E. MIN(MAX(x,-127),127) = -MAX(-MAX(x, -127), -127) = MIN(-MIN(-x,127),127)
    mouse_report.x = -MAX(-MAX(x, -127), -127);
    mouse_report.y = -MAX(-MAX(y, -127), -127);
    if (debug_mouse) {
            print("adb_host_mouse_recv: "); print_bin16(codes); print("\n");
            print("adb_mouse raw: [");
            print_hex8(mouseacc); print(" ");
            print_hex8(mouse_report.buttons); print("|");
            print_decs(mouse_report.x); print(" ");
            print_decs(mouse_report.y); print("]\n");
    }
    // Send result by usb.
    host_mouse_send(&mouse_report);
    // increase acceleration of mouse
    mouseacc += ( mouseacc < ADB_MOUSE_MAXACC ? 1 : 0 );
    return;
}
#endif

uint8_t matrix_scan(void)
{
    /* extra_key is volatile and more convoluted than necessary because gcc refused
    to generate valid code otherwise. Making extra_key uint8_t and constructing codes
    here via codes = extra_key<<8 | 0xFF; would consistently fail to even LOAD
    extra_key from memory, and leave garbage in the high byte of codes. I tried
    dozens of code variations and it kept generating broken assembly output. So
    beware if attempting to make extra_key code more logical and efficient. */
    static volatile uint16_t extra_key = 0xFFFF;
    uint16_t codes;
    uint8_t key0, key1;

    /* tick of last polling */
    static uint16_t tick_ms;

    codes = extra_key;
    extra_key = 0xFFFF;

    if ( codes == 0xFFFF )
    {
        // polling with 12ms interval
        if (timer_elapsed(tick_ms) < 12) return 0;
        tick_ms = timer_read();

        codes = adb_host_kbd_recv();
    }

    key0 = codes>>8;
    key1 = codes&0xFF;

    if (debug_matrix && codes) {
        print("adb_host_kbd_recv: "); print_hex16(codes); print("\n");
    }

    if (codes == 0) {                           // no keys
        return 0;
    } else if (codes == 0x7F7F) {   // power key press
        register_key(0x7F);
    } else if (codes == 0xFFFF) {   // power key release
        register_key(0xFF);
    } else if (key0 == 0xFF) {      // error
        xprintf("adb_host_kbd_recv: ERROR(%d)\n", codes);
        // something wrong or plug-in
        matrix_init();
        return key1;
    } else {
        /* Swap codes for ISO keyboard
         * https://github.com/tmk/tmk_keyboard/issues/35
         *
         * ANSI
         * ,-----------    ----------.
         * | *a|  1|  2     =|Backspa|
         * |-----------    ----------|
         * |Tab  |  Q|     |  ]|   *c|
         * |-----------    ----------|
         * |CapsLo|  A|    '|Return  |
         * |-----------    ----------|
         * |Shift   |      Shift     |
         * `-----------    ----------'
         *
         * ISO
         * ,-----------    ----------.
         * | *a|  1|  2     =|Backspa|
         * |-----------    ----------|
         * |Tab  |  Q|     |  ]|Retur|
         * |-----------    -----`    |
         * |CapsLo|  A|    '| *c|    |
         * |-----------    ----------|
         * |Shif| *b|      Shift     |
         * `-----------    ----------'
         *
         *         ADB scan code   USB usage
         *         -------------   ---------
         * Key     ANSI    ISO     ANSI    ISO
         * ---------------------------------------------
         * *a      0x32    0x0A    0x35    0x35
         * *b      ----    0x32    ----    0x64
         * *c      0x2A    0x2A    0x31    0x31(or 0x32)
         */
        if (is_iso_layout) {
            if ((key0 & 0x7F) == 0x32) {
                key0 = (key0 & 0x80) | 0x0A;
            } else if ((key0 & 0x7F) == 0x0A) {
                key0 = (key0 & 0x80) | 0x32;
            }
        }
        register_key(key0);
        if (key1 != 0xFF)       // key1 is 0xFF when no second key.
            extra_key = key1<<8 | 0xFF; // process in a separate call
    }

    matrix_scan_quantum();
    return 1;
}

void matrix_print(void){

}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

inline
static void register_key(uint8_t key)
{
    uint8_t col, row;
    col = key&0x07;
    row = (key>>3)&0x0F;
    if (key&0x80) {
        matrix[row] &= ~(1<<col);
    } else {
        matrix[row] |=  (1<<col);
    }
}
