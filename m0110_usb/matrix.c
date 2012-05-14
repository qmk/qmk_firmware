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
#include "m0110.h"
#include "matrix.h"


#define CAPS        0x39
#define CAPS_BREAK  (CAPS | 0x80)
#define ROW(key)    ((key)>>3&0x0F)
#define COL(key)    ((key)&0x07)

#define ARROW_UP_BREAK      (0x4D | 0x80)
#define ARROW_DOWN_BREAK    (0x48 | 0x80)
#define ARROW_LEFT_BREAK    (0x46 | 0x80)
#define ARROW_RIGHT_BREAK   (0x42 | 0x80)


static bool is_modified = false;

// matrix state buffer(1:on, 0:off)
static uint8_t *matrix;
static uint8_t _matrix0[MATRIX_ROWS];

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
    print_enable = true;
    debug_enable = true;
    debug_matrix = false;
    debug_keyboard = false;
    debug_mouse = false;
    print("debug enabled.\n");

    m0110_init();
    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    matrix = _matrix0;
    return;
}

uint8_t matrix_scan(void)
{
    uint8_t key;

    is_modified = false;
    key = m0110_recv_key();

#ifdef MATRIX_HAS_LOCKING_CAPS
    // Send Caps key up event
    if (matrix_is_on(ROW(CAPS), COL(CAPS))) {
        is_modified = true;
        register_key(CAPS_BREAK);
    }
#endif
    if (key == M0110_NULL) {
        return 0;
    } else if (key == M0110_ERROR) {
        return 0;
    } else if (key == ARROW_UP_BREAK ||
               key == ARROW_DOWN_BREAK ||
               key == ARROW_LEFT_BREAK ||
               key == ARROW_RIGHT_BREAK) {
        // WORK AROUND: exceptional handling for M0110A
        // Unregister both Arrow key and coressponding Calc key when receive Arrow key break.
        //
        // Shift + Calc keys(=/*+):
        //    Send no Shift break(0xF1) when release Calc keys. Can't be desinguished from Arrow keys.
        //    (press: 0x71, 0x79, 0xXX      release: 0x79, 0xXX)
        //    See m0110.c for key events and scan codes.
        is_modified = true;
        register_key(key);
        register_key(key|M0110_CALC_OFFSET);
    } else {
#ifdef MATRIX_HAS_LOCKING_CAPS    
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
            // CAPS LOCK on:
            // Ignore LockingCaps key down event
            if (key == CAPS) return 0;
            // Convert LockingCaps key up event into down event
            if (key == CAPS_BREAK) key = CAPS;
        } else {
            // CAPS LOCK off:
            // Ignore LockingCaps key up event
            if (key == CAPS_BREAK) return 0;
        }
#endif        
        is_modified = true;
        register_key(key);
    }

    if (debug_enable) {
        print("key: "); phex(key); print("\n");
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
uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop(matrix[i]);
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
    if (key&0x80) {
        matrix[ROW(key)] &= ~(1<<COL(key));
    } else {
        matrix[ROW(key)] |=  (1<<COL(key));
    }
}
