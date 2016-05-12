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


#if (MATRIX_COLS > 16)
#   error "MATRIX_COLS must not exceed 16"
#endif
#if (MATRIX_ROWS > 255)
#   error "MATRIX_ROWS must not exceed 255"
#endif


static bool is_modified = false;
static report_mouse_t mouse_report = {};

// matrix state buffer(1:on, 0:off)
#if (MATRIX_COLS <= 8)
static uint8_t matrix[MATRIX_ROWS];
#else
static uint16_t matrix[MATRIX_ROWS];
#endif

#ifdef MATRIX_HAS_GHOST
static bool matrix_has_ghost_in_row(uint8_t row);
#endif
static void register_key(uint8_t key);


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    adb_host_init();
    // wait for keyboard to boot up and receive command
    _delay_ms(1000);
    // Enable keyboard left/right modifier distinction
    // Addr:Keyboard(0010), Cmd:Listen(10), Register3(11)
    // upper byte: reserved bits 0000, device address 0010
    // lower byte: device handler 00000011
    adb_host_listen(0x2B,0x02,0x03);

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    debug_enable = true;
    //debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = true;
    print("debug enabled.\n");

    // LED flash
    DDRD |= (1<<6); PORTD |= (1<<6);
    _delay_ms(500);
    DDRD |= (1<<6); PORTD &= ~(1<<6);

    return;
}

#ifdef ADB_MOUSE_ENABLE

#ifdef MAX
#undef MAX
#endif
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

void adb_mouse_task(void)
{
    uint16_t codes;
    int16_t x, y;
    static int8_t mouseacc; 
    _delay_ms(12);  // delay for preventing overload of poor ADB keyboard controller
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

    is_modified = false;

    codes = extra_key;
    extra_key = 0xFFFF;

    if ( codes == 0xFFFF )
    {
        _delay_ms(12);  // delay for preventing overload of poor ADB keyboard controller
        codes = adb_host_kbd_recv();
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
        return key1;
    } else {
        register_key(key0);
        if (key1 != 0xFF)       // key1 is 0xFF when no second key.
            extra_key = key1<<8 | 0xFF; // process in a separate call
    }

    return 1;
}

bool matrix_is_modified(void)
{
    return is_modified;
}

inline
bool matrix_has_ghost(void)
{
#ifdef MATRIX_HAS_GHOST
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix_has_ghost_in_row(i))
            return true;
    }
#endif
    return false;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
#if (MATRIX_COLS <= 8)
uint8_t matrix_get_row(uint8_t row)
#else
uint16_t matrix_get_row(uint8_t row)
#endif
{
    return matrix[row];
}

void matrix_print(void)
{
    if (!debug_matrix) return;
#if (MATRIX_COLS <= 8)
    print("r/c 01234567\n");
#else
    print("r/c 0123456789ABCDEF\n");
#endif
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
#if (MATRIX_COLS <= 8)
        pbin_reverse(matrix_get_row(row));
#else
        pbin_reverse16(matrix_get_row(row));
#endif
#ifdef MATRIX_HAS_GHOST
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
#endif
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
#if (MATRIX_COLS <= 8)
        count += bitpop(matrix[i]);
#else
        count += bitpop16(matrix[i]);
#endif
    }
    return count;
}

#ifdef MATRIX_HAS_GHOST
inline
static bool matrix_has_ghost_in_row(uint8_t row)
{
    // no ghost exists in case less than 2 keys on
    if (((matrix[row] - 1) & matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && (matrix[i] & matrix[row]) == matrix[row])
            return true;
    }
    return false;
}
#endif

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
    is_modified = true;
}
