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
#include "host.h"
#include "led.h"
#include "adb.h"
#include "matrix.h"


#if (MATRIX_COLS > 16)
#   error "MATRIX_COLS must not exceed 16"
#endif
#if (MATRIX_ROWS > 255)
#   error "MATRIX_ROWS must not exceed 255"
#endif

#define ADB_CAPS_UP     (ADB_CAPS | 0x80)


static bool is_modified = false;

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

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    print_enable = true;
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;
    print("debug enabled.\n");
    return;
}

uint8_t matrix_scan(void)
{
    uint16_t codes;
    uint8_t key0, key1;

    is_modified = false;
    codes = adb_host_kbd_recv();
    key0 = codes>>8;
    key1 = codes&0xFF;

    if (debug_matrix && codes) {
        print("adb_host_kbd_recv: "); phex16(codes); print("\n");
    }

#ifdef MATRIX_HAS_LOCKING_CAPS
    // Send Caps key up event
    if (matrix_is_on(MATRIX_ROW(ADB_CAPS), MATRIX_COL(ADB_CAPS))) {
        register_key(ADB_CAPS_UP);
    }
#endif
    if (codes == 0) {                           // no keys
        return 0;
    } else if (codes == 0x7F7F) {   // power key press
        register_key(0x7F);
    } else if (codes == 0xFFFF) {   // power key release
        register_key(0xFF);
    } else if (key0 == 0xFF) {      // error
        if (debug_matrix) print("adb_host_kbd_recv: ERROR(matrix cleared.)\n");
        // clear matrix to unregister all keys
        for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;
        return key1;
    } else {
#ifdef MATRIX_HAS_LOCKING_CAPS    
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
            // Ignore LockingCaps key down event when CAPS LOCK is on
            if (key0 == ADB_CAPS && (key1 == ADB_CAPS || key1 == 0xFF)) return 0;
            if (key0 == ADB_CAPS) key0 = key1;
            if (key1 == ADB_CAPS) key1 = 0xFF;
            // Convert LockingCaps key up event into down event
            if (key0 == ADB_CAPS_UP) key0 = ADB_CAPS;
            if (key1 == ADB_CAPS_UP) key1 = ADB_CAPS;
        } else {
            // ADB_CAPS LOCK off:
            // Ignore LockingCaps key up event when ADB_CAPS LOCK is off
            if (key0 == ADB_CAPS_UP && (key1 == ADB_CAPS_UP || key1 == 0xFF)) return 0;
            if (key0 == ADB_CAPS_UP) key0 = key1;
            if (key1 == ADB_CAPS_UP) key1 = 0xFF;
        }
#endif        
        register_key(key0);
        if (key1 != 0xFF)       // key1 is 0xFF when no second key.
            register_key(key1);
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
