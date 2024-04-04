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

#include "matrix.h"
#include "atomic_util.h"
#include <string.h>

// Pin connected to DS of 74HC595
#define DATA_PIN A7
// Pin connected to SH_CP of 74HC595
#define CLOCK_PIN B1
// Pin connected to ST_CP of 74HC595
#define LATCH_PIN B0

#ifdef MATRIX_ROW_PINS
static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif // MATRIX_ROW_PINS
#ifdef MATRIX_COL_PINS
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif // MATRIX_COL_PINS

#define ROWS_PER_HAND (MATRIX_ROWS)

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_high(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return gpio_read_pin(pin);
    } else {
        return 1;
    }
}

static void shiftOutMultiple(uint16_t dataOut) {
    for (uint8_t i = 0; i < 8; i++) {
        if (dataOut & 0x1) {
            setPinOutput_writeHigh(DATA_PIN);
        } else {
            setPinOutput_writeLow(DATA_PIN);
        }
        dataOut = dataOut >> 1;
        setPinOutput_writeHigh(CLOCK_PIN);
        setPinOutput_writeLow(CLOCK_PIN);
    }
    setPinOutput_writeHigh(LATCH_PIN);
    setPinOutput_writeLow(LATCH_PIN);
}

static void shiftOut_single(uint8_t dataOut) {
    if (dataOut & 0x1) {
        setPinOutput_writeHigh(DATA_PIN);
    } else {
        setPinOutput_writeLow(DATA_PIN);
    }
    setPinOutput_writeHigh(CLOCK_PIN);
    setPinOutput_writeLow(CLOCK_PIN);
    setPinOutput_writeHigh(LATCH_PIN);
    setPinOutput_writeLow(LATCH_PIN);
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    } else {
        if (col == (MATRIX_COLS - 8)) {
            shiftOut_single(0x00);
        } else {
            shiftOut_single(0x01);
        }
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
        setPinOutput_writeHigh(pin);
#else
        setPinInputHigh_atomic(pin);
#endif
    } else {
        if (col == (MATRIX_COLS - 1)) {
            setPinOutput_writeHigh(CLOCK_PIN);
            setPinOutput_writeLow(CLOCK_PIN);
            setPinOutput_writeHigh(LATCH_PIN);
            setPinOutput_writeLow(LATCH_PIN);
        }
    }
}

static void unselect_cols(void) {
    // unselect column pins
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        pin_t pin = col_pins[x];
        if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
            setPinOutput_writeHigh(pin);
#else
            setPinInputHigh_atomic(pin);
#endif
        } else {
            if (x == (MATRIX_COLS - 1)) {
                // unselect Shift Register
                shiftOutMultiple(0xFF);
            }
        }
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

static void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }

    if (current_col < (MATRIX_COLS - 8)) {
        matrix_output_select_delay();
    } else {
        matrix_output_select_delay();
        matrix_output_select_delay();
        matrix_output_select_delay();
        matrix_output_select_delay();
    }

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}

void matrix_init_custom(void) {
    // initialize key pins
    matrix_init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }

    bool changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));

    return changed;
}
