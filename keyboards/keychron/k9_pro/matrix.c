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

#include "quantum.h"

#define HC595_STCP B0
#define HC595_SHCP A1
#define HC595_DS A7

pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

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

static inline void setPinInput_high(pin_t pin) {
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

static inline void HC595_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    }
}

static void HC595_output(uint16_t data) {
    ATOMIC_BLOCK_FORCEON {
        for (uint8_t i = 0; i < MATRIX_COLS; i++) {
            if (data & 0x1) {
                writePinHigh(HC595_DS);
            } else {
                writePinLow(HC595_DS);
            }

            data = data >> 1;

            writePinHigh(HC595_SHCP);
            HC595_delay(1);
            writePinLow(HC595_SHCP);
            HC595_delay(1);
        }
        writePinHigh(HC595_STCP);
        HC595_delay(1);
        writePinLow(HC595_STCP);
        HC595_delay(1);
    }
}

static void HC595_output_oneBit(uint8_t data) {
    ATOMIC_BLOCK_FORCEON {
        if (data & 0x1) {
            writePinHigh(HC595_DS);
        } else {
            writePinLow(HC595_DS);
        }

        writePinHigh(HC595_SHCP);
        HC595_delay(1);
        writePinLow(HC595_SHCP);
        HC595_delay(1);

        writePinHigh(HC595_STCP);
        HC595_delay(1);
        writePinLow(HC595_STCP);
        HC595_delay(1);
    }
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    } else {
        if (col == 0) {
            HC595_output_oneBit(0x00);
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
        setPinInput_high(pin);
#endif
    } else {
        HC595_output_oneBit(0x01);
    }
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        pin_t pin = col_pins[x];
        if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
            setPinOutput_writeHigh(pin);
#else
            setPinInput_high(pin);
#endif
        } else {
            if (x == 0) HC595_output(0xFFFF);
        }
    }
}

void select_all_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        pin_t pin = col_pins[x];
        if (pin != NO_PIN) {
            setPinOutput_writeLow(pin);
        } else {
            if (x == 0) HC595_output(0x0000);
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
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
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
    setPinOutput(HC595_DS);
    setPinOutput(HC595_STCP);
    setPinOutput(HC595_SHCP);

    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            setPinInput_high(row_pins[x]);
        }
    }

    unselect_cols();
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
