/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

#define DS A7
#define STCP B0
#define SHCP B1

#ifdef MATRIX_ROW_PINS
static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif  // MATRIX_ROW_PINS
#ifdef MATRIX_COL_PINS
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif  // MATRIX_COL_PINS

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinHigh(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputHigh(pin); }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return readPin(pin);
    } else {
        return 1;
    }
}

static void delay_nTime(uint8_t time) {
    while(time--);
}

static void SendTo595(uint8_t byteData) {
    uint8_t i = 0;

    for (; i < 8; i++) {
        if (byteData & 0x1) {
            setPinOutput_writeHigh(DS);
        } else {
            setPinOutput_writeLow(DS);
        }
        byteData = byteData>>1;

        setPinOutput_writeHigh(SHCP);
        delay_nTime(10);
        setPinOutput_writeLow(SHCP);
    }
    setPinOutput_writeHigh(STCP);
    delay_nTime(10);
    setPinOutput_writeLow(STCP);
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    } else {
        SendTo595(~(0x1<<(MATRIX_COLS - col -1)));
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
        setPinInputHigh_atomic(pin);
    } else {
        SendTo595(0xFF);
    }
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
            unselect_col(x);
    }
}

static void matrix_init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            setPinInputHigh_atomic(row_pins[x]);
        }
    }
}

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) {
        return;                      // skip NO_PIN col
    }
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed);  // wait for all Row signals to go HIGH
}

void matrix_init_custom(void) {
    // initialize key pins
    matrix_init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        matrix_read_rows_on_col(curr_matrix, current_col);
    }

    bool changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));

    return changed;
}
