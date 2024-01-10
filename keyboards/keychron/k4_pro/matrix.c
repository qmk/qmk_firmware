/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#include "stdint.h"
#include "hal.h"
#include "gpio.h"
#include "quantum.h"

#define HC595_STCP A0
#define HC595_SHCP A1
#define HC595_DS C15

#define DIRECT_COL_NUM 2

pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static inline void HC595_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    };
}

static void HC595_output(uint16_t data) {
    uint8_t i;
    uint8_t n = 1;

    for (i = 16; i > 0; i--) {
        writePinLow(HC595_SHCP);

        if (data & 0x8000)
            writePinHigh(HC595_DS);
        else
            writePinLow(HC595_DS);

        data <<= 1;

        HC595_delay(n);

        writePinHigh(HC595_SHCP);
        HC595_delay(n);
    }

    HC595_delay(n);
    writePinLow(HC595_STCP);
    HC595_delay(n);
    writePinHigh(HC595_STCP);
}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinInputHigh(pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return readPin(pin);
    } else {
        return 1;
    }
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (col < DIRECT_COL_NUM) {
        setPinOutput_writeLow(pin);
        return true;
    } else {
        HC595_output(~(0x01 << (col - DIRECT_COL_NUM)));
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (col < DIRECT_COL_NUM) {
        setPinInputHigh_atomic(pin);
    } else {
        HC595_output(0xFFFF);
    }
}

static void unselect_cols(void) {
    for (uint8_t i = 0; i < DIRECT_COL_NUM; i++)
        writePinHigh(col_pins[i]);
    HC595_output(0xFFFF);
}

void select_all_cols(void) {
    for (uint8_t i = 0; i < DIRECT_COL_NUM; i++)
        setPinOutput_writeLow(col_pins[i]);
    HC595_output(0x0000);
}

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }

    HC595_delay(100);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
            // key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
        }
    }

    unselect_col(current_col);
    HC595_delay(100);
}

void matrix_init_custom(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            setPinInputHigh_atomic(row_pins[x]);
        }
    }
    setPinOutput(HC595_DS);
    setPinOutput(HC595_STCP);
    setPinOutput(HC595_SHCP);
    unselect_cols();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        matrix_read_rows_on_col(curr_matrix, current_col);
    }

    matrix_has_changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (matrix_has_changed) memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));

    return matrix_has_changed;
}
