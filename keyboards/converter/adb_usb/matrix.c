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
*/

/*
 * scan matrix
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




static bool has_media_keys = false;
static bool is_iso_layout = false;

// matrix state buffer(1:on, 0:off)
static matrix_row_t matrix[MATRIX_ROWS];

static void register_key(uint8_t key);


void matrix_init(void)
{
    // LED on
    DDRD |= (1<<6); PORTD |= (1<<6);

    adb_host_init();
    // wait for keyboard to boot up and receive command
    _delay_ms(2000);

    // device scan
    xprintf("Before init:\n");
    for (uint8_t addr = 1; addr < 16; addr++) {
        uint16_t reg3 = adb_host_talk(addr, ADB_REG_3);
        if (reg3) {
            xprintf("Scan: addr:%d, reg3:%04X\n", addr, reg3);
        }
        _delay_ms(20);
    }

    // Determine ISO keyboard by handler id
    // http://lxr.free-electrons.com/source/drivers/macintosh/adbhid.c?v=4.4#L815
    uint8_t handler_id = (uint8_t) adb_host_talk(ADB_ADDR_KEYBOARD, ADB_REG_3);
    switch (handler_id) {
    case 0x04: case 0x05: case 0x07: case 0x09: case 0x0D:
    case 0x11: case 0x14: case 0x19: case 0x1D: case 0xC1:
    case 0xC4: case 0xC7:
        is_iso_layout = true;
        break;
    default:
        is_iso_layout = false;
        break;
    }
    xprintf("hadler_id: %02X, is_iso_layout: %s\n", handler_id, (is_iso_layout ? "yes" : "no"));

    // Adjustable keyboard media keys: address=0x07 and handlerID=0x02
    has_media_keys = (0x02 == (adb_host_talk(ADB_ADDR_APPLIANCE, ADB_REG_3) & 0xff));
    if (has_media_keys) {
        xprintf("Found: media keys\n");
    }

    // Enable keyboard left/right modifier distinction
    // Listen Register3
    //  upper byte: reserved bits 0000, keyboard address 0010
    //  lower byte: device handler 00000011
    adb_host_listen(ADB_ADDR_KEYBOARD, ADB_REG_3, ADB_ADDR_KEYBOARD, ADB_HANDLER_EXTENDED_PROTOCOL);

    // device scan
    xprintf("After init:\n");
    for (uint8_t addr = 1; addr < 16; addr++) {
        uint16_t reg3 = adb_host_talk(addr, ADB_REG_3);
        if (reg3) {
            xprintf("Scan: addr:%d, reg3:%04X\n", addr, reg3);
        }
        _delay_ms(20);
    }

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    led_set(host_keyboard_leds());

    debug_enable = true;
    //debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = true;
    print("debug enabled.\n");

    // LED off
    DDRD |= (1<<6); PORTD &= ~(1<<6);
    return;
}

#ifdef ADB_MOUSE_ENABLE

#ifdef MAX
#undef MAX
#endif
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

static report_mouse_t mouse_report = {};

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
            phex(mouseacc); print(" ");
            phex(mouse_report.buttons); print("|");
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

        codes = adb_host_kbd_recv(ADB_ADDR_KEYBOARD);

        // Adjustable keybaord media keys
        if (codes == 0 && has_media_keys &&
                (codes = adb_host_kbd_recv(ADB_ADDR_APPLIANCE))) {
            // key1
            switch (codes & 0x7f ) {
            case 0x00:  // Mic
                codes = (codes & ~0x007f) | 0x42;
                break;
            case 0x01:  // Mute
                codes = (codes & ~0x007f) | 0x4a;
                break;
            case 0x02:  // Volume down
                codes = (codes & ~0x007f) | 0x49;
                break;
            case 0x03:  // Volume Up
                codes = (codes & ~0x007f) | 0x48;
                break;
            case 0x7F:  // no code
                break;
            default:
                xprintf("ERROR: media key1\n");
                return 0x11;
            }
            // key0
            switch ((codes >> 8) & 0x7f ) {
            case 0x00:  // Mic
                codes = (codes & ~0x7f00) | (0x42 << 8);
                break;
            case 0x01:  // Mute
                codes = (codes & ~0x7f00) | (0x4a << 8);
                break;
            case 0x02:  // Volume down
                codes = (codes & ~0x7f00) | (0x49 << 8);
                break;
            case 0x03:  // Volume Up
                codes = (codes & ~0x7f00) | (0x48 << 8);
                break;
            default:
                xprintf("ERROR: media key0\n");
                return 0x10;
            }
        }
    }
    key0 = codes>>8;
    key1 = codes&0xFF;

    if (debug_matrix && codes) {
        print("adb_host_kbd_recv: "); phex16(codes); print("\n");
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

    return 1;
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
