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

#include <stdint.h>
#include <stdbool.h>
#include "usb_hid.h"
#include "keycode.h"
#include "util.h"
#include "print.h"
#include "debug.h"
#include "matrix.h"

/* KEY CODE to Matrix
 *
 * HID keycode(1 byte):
 * Higher 5 bits indicates ROW and lower 3 bits COL.
 *
 *  7 6 5 4 3 2 1 0
 * +---------------+
 * |   ROW   | COL |
 * +---------------+
 *
 * Matrix space(32 * 8):
 *      01234567
 *   0 +--------+
 *   : |        |
 *   : |        |
 *  31 +--------+
 */
#define ROW_MASK 0xF8
#define COL_MASK 0x07
#define CODE(row, col)  (((row) << 3) | (col))
#define ROW(code)       (((code) & ROW_MASK) >> 3)
#define COL(code)       ((code) & COL_MASK)
#define ROW_BITS(code)  (1 << COL(code))


uint8_t matrix_rows(void) { return MATRIX_ROWS; }
uint8_t matrix_cols(void) { return MATRIX_COLS; }
void matrix_init(void) {}
bool matrix_has_ghost(void) { return false; }

static bool matrix_is_mod =false;

uint8_t matrix_scan(void) {
    static uint16_t last_time_stamp = 0;

    if (last_time_stamp != usb_hid_time_stamp) {
        last_time_stamp = usb_hid_time_stamp;
        matrix_is_mod = true;
    } else {
        matrix_is_mod = false;
    }
    return 1;
}

bool matrix_is_modified(void) {

    return matrix_is_mod;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    uint8_t code = CODE(row, col);

    if (IS_MOD(code)) {
        if (usb_hid_keyboard_report.mods & ROW_BITS(code)) {
            return true;
        }
    }
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (usb_hid_keyboard_report.keys[i] == code) {
            return true;
        }
    }
    return false;
}

uint8_t matrix_get_row(uint8_t row) {
    uint8_t row_bits = 0;

    if (IS_MOD(CODE(row, 0)) && usb_hid_keyboard_report.mods) {
        row_bits |= usb_hid_keyboard_report.mods;
    }

    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (IS_ANY(usb_hid_keyboard_report.keys[i])) {
            if (row == ROW(usb_hid_keyboard_report.keys[i])) {
                row_bits |= ROW_BITS(usb_hid_keyboard_report.keys[i]);
            }
        }
    }
    return row_bits;
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;

    count += bitpop(usb_hid_keyboard_report.mods);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (IS_ANY(usb_hid_keyboard_report.keys[i])) {
            count++;
        }
    }
    return count;
}

void matrix_print(void) {
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
#ifdef MATRIX_HAS_GHOST
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
#endif
        print("\n");
    }
}
