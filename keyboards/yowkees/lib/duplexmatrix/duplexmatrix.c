/*
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include <string.h>
#include "quantum.h"
#include "matrix.h"
#include "debounce.h"

#ifdef SPLIT_KEYBOARD
#    include "split_common/split_util.h"
#    include "split_common/transactions.h"
#endif

#ifdef SPLIT_KEYBOARD
#    define PINNUM_ROW (MATRIX_ROWS / 2)
#    define ROWS_PER_HAND (MATRIX_ROWS / 2)
#else
#    define PINNUM_ROW (MATRIX_ROWS)
#    define ROWS_PER_HAND (MATRIX_ROWS)
#endif
#define PINNUM_COL (MATRIX_COLS / 2)

#define MATRIXSIZE_PER_HAND (ROWS_PER_HAND * sizeof(matrix_row_t))

static pin_t row_pins[PINNUM_ROW] = MATRIX_ROW_PINS;
static pin_t col_pins[PINNUM_COL] = MATRIX_COL_PINS;

static inline void set_pin_input(pin_t pin) {
    setPinInputHigh(pin);
}

static void set_pins_input(pin_t* pins, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) {
        set_pin_input(pins[i]);
    }
}

static inline void set_pin_output(pin_t pin) {
    setPinOutput(pin);
    writePinLow(pin);
}

static inline bool get_pin(pin_t pin) {
    return readPin(pin);
}

__attribute__((weak)) void duplex_scan_raw_post_kb(matrix_row_t out_matrix[]) {}

static void duplex_scan_raw(matrix_row_t out_matrix[]) {
    // scan column to row
    for (uint8_t row = 0; row < PINNUM_ROW; row++) {
        set_pin_output(row_pins[row]);
        matrix_output_select_delay();
        for (uint8_t col = 0; col < PINNUM_COL; col++) {
            if (!get_pin(col_pins[col])) {
                out_matrix[row] |= 1 << col;
            }
        }
        set_pin_input(row_pins[row]);
        matrix_output_unselect_delay(row, false);
    }

    // scan row to column.
    for (uint8_t col = 0; col < PINNUM_COL; col++) {
        set_pin_output(col_pins[col]);
        matrix_output_select_delay();
        matrix_row_t shifter = ((matrix_row_t)1) << (col + PINNUM_COL);
        for (uint8_t row = 0; row < PINNUM_ROW; row++) {
            if (!get_pin(row_pins[row])) {
                out_matrix[row] |= shifter;
            }
        }
        set_pin_input(col_pins[col]);
        matrix_output_unselect_delay(col, false);
    }

    duplex_scan_raw_post_kb(out_matrix);
}

static bool duplex_scan(matrix_row_t current_matrix[]) {
    bool         changed = false;
    matrix_row_t tmp[MATRIX_ROWS] = {0};

    duplex_scan_raw(tmp);
    for (uint8_t row = 0; row < PINNUM_ROW; row++) {
        if (tmp[row] != current_matrix[row]) {
            changed = true;
            current_matrix[row] = tmp[row];
        }
    }
    return changed;
}

#ifdef SPLIT_KEYBOARD
static uint8_t thisHand, thatHand;
#else
#    define thisHand 0
#endif

void matrix_init_custom(void) {
#ifdef SPLIT_KEYBOARD
    split_pre_init();
#endif

    set_pins_input(col_pins, PINNUM_COL);
    set_pins_input(row_pins, PINNUM_ROW);

#ifdef SPLIT_KEYBOARD
    thisHand = isLeftHand ? 0 : ROWS_PER_HAND;
    thatHand = ROWS_PER_HAND - thisHand;

    split_post_init();
#endif
}

#ifdef SPLIT_KEYBOARD

// user-defined overridable functions
__attribute__((weak)) void matrix_slave_scan_kb(void) {
    matrix_slave_scan_user();
}

__attribute__((weak)) void matrix_slave_scan_user(void) {}

#endif

// declare matrix buffers which defined in quantum/matrix_common.c
extern matrix_row_t raw_matrix[MATRIX_ROWS];
extern matrix_row_t matrix[MATRIX_ROWS];

uint8_t matrix_scan(void) {
    bool changed = duplex_scan(raw_matrix);

    debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, changed);

#ifdef SPLIT_KEYBOARD
    if (!is_keyboard_master()) {
        // send to primary.
        transport_slave(matrix + thatHand, matrix + thisHand);
        matrix_slave_scan_kb();
        return changed;
    }

    // receive from secondary.
    static bool   last_connected = false;
    matrix_row_t* that_raw       = raw_matrix + ROWS_PER_HAND;
    memset(that_raw, 0, MATRIXSIZE_PER_HAND);
    if (transport_master_if_connected(matrix + thisHand, that_raw)) {
        last_connected = true;
        if (memcmp(matrix + thatHand, that_raw, MATRIXSIZE_PER_HAND) != 0) {
            memcpy(matrix + thatHand, that_raw, MATRIXSIZE_PER_HAND);
            changed = true;
        }
    } else if (last_connected) {
        last_connected = false;
        memset(matrix + thatHand, 0, MATRIXSIZE_PER_HAND);
        changed = true;
    }
#endif

    matrix_scan_kb();
    return changed;
}
