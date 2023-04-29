/* Copyright 2022 @ Keychron (https://www.keychron.com)
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
#include "quantum.h"

#ifndef PIN_USED_74HC595
#    define PIN_USED_74HC595 8
#endif
#ifndef PIN_START_74HC595
#    define PIN_START_74HC595 8
#endif

#ifdef MATRIX_ROW_PINS
static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif // MATRIX_ROW_PINS
#ifdef MATRIX_COL_PINS
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif // MATRIX_COL_PINS

#define ROWS_PER_HAND (MATRIX_ROWS)

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

void small_delay(volatile uint8_t timeout) {
    while (timeout--);
}

static void shiftOut(uint16_t dataOut) {
    ATOMIC_BLOCK_FORCEON {
        for (uint8_t i = 0; i < PIN_USED_74HC595; i++) {
            if (dataOut & 0x1) {
                writePinHigh(DATA_PIN_74HC595);
            } else {
                writePinLow(DATA_PIN_74HC595);
            }
            dataOut = dataOut >> 1;
            writePinHigh(CLOCK_PIN_74HC595);
            small_delay(2);
            writePinLow(CLOCK_PIN_74HC595);
        }
        writePinHigh(LATCH_PIN_74HC595);
        small_delay(2);
        writePinLow(LATCH_PIN_74HC595);
    }
}

static void shiftOut_single(uint8_t data) {
    ATOMIC_BLOCK_FORCEON {
        if (data & 0x1) {
            writePinHigh(DATA_PIN_74HC595);
        } else {
            writePinLow(DATA_PIN_74HC595);
        }
        writePinHigh(CLOCK_PIN_74HC595);
        small_delay(2);
        writePinLow(CLOCK_PIN_74HC595);
        writePinHigh(LATCH_PIN_74HC595);
        small_delay(2);
        writePinLow(LATCH_PIN_74HC595);
    }
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    } else {
        if (col == PIN_START_74HC595) {
            shiftOut_single(0x00);
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
        shiftOut_single(0x01);
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
        }
        if (x == PIN_START_74HC595)
            // unselect Shift Register
            shiftOut(0xFFFF);
    }
}

static void matrix_init_pins(void) {
    setPinOutput(DATA_PIN_74HC595);
    setPinOutput(CLOCK_PIN_74HC595);
    setPinOutput(LATCH_PIN_74HC595);
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            setPinOutput(col_pins[x]);
        }
    }
#endif
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

    matrix_output_select_delay();

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
