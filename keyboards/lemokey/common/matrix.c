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

#ifndef HC595_STCP
#    define HC595_STCP B0
#endif
#ifndef HC595_SHCP
#    define HC595_SHCP A1
#endif
#ifndef HC595_DS
#    define HC595_DS A7
#endif

#ifndef HC595_START_INDEX
#    define HC595_START_INDEX 0
#endif
#ifndef HC595_END_INDEX
#    define HC595_END_INDEX 15
#endif
#ifndef HC595_OFFSET_INDEX
#    define HC595_OFFSET_INDEX 0
#endif

#if defined(HC595_START_INDEX) && defined(HC595_END_INDEX)
#    if ((HC595_END_INDEX - HC595_START_INDEX + 1) > 16)
#        define SIZE_T uint32_t
#        define UNSELECT_ALL_COL 0xFFFFFFFF
#        define SELECT_ALL_COL 0x00000000
#    elif ((HC595_END_INDEX - HC595_START_INDEX + 1) > 8)
#        define SIZE_T uint16_t
#        define UNSELECT_ALL_COL 0xFFFF
#        define SELECT_ALL_COL 0x0000
#    else
#        define SIZE_T uint8_t
#        define UNSELECT_ALL_COL 0xFF
#        define SELECT_ALL_COL 0x00
#    endif
#endif

pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return readPin(pin);
    } else {
        return 1;
    }
}

static inline void setPinOutput_writeLow(pin_t pin) {
    setPinOutput(pin);
    writePinLow(pin);
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    setPinOutput(pin);
    writePinHigh(pin);
}

static inline void HC595_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    }
}

static void HC595_output(SIZE_T data, bool bit_flag) {
    uint8_t n = 1;

    ATOMIC_BLOCK_FORCEON {
        for (uint8_t i = 0; i < (HC595_END_INDEX - HC595_START_INDEX + 1); i++) {
            if (data & 0x1) {
                writePinHigh(HC595_DS);
            } else {
                writePinLow(HC595_DS);
            }
            writePinHigh(HC595_SHCP);
            HC595_delay(n);
            writePinLow(HC595_SHCP);
            HC595_delay(n);
            if (bit_flag) {
                break;
            } else {
                data = data >> 1;
            }
        }
        writePinHigh(HC595_STCP);
        HC595_delay(n);
        writePinLow(HC595_STCP);
        HC595_delay(n);
    }
}

static void select_col(uint8_t col) {
    if (col < HC595_START_INDEX || col > HC595_END_INDEX) {
        setPinOutput_writeLow(col_pins[col]);
    } else {
        if (col == HC595_START_INDEX) {
            HC595_output(0x00, true);
            if (col < HC595_OFFSET_INDEX) {
                HC595_output(0x01, true);
            }
        }
    }
}

static void unselect_col(uint8_t col) {
    if (col < HC595_START_INDEX || col > HC595_END_INDEX) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
        setPinOutput_writeHigh(col_pins[col]);
#else
        setPinInputHigh(col_pins[col]);
#endif
    } else {
        HC595_output(0x01, true);
    }
}

static void unselect_cols(void) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        if (col < HC595_START_INDEX || col > HC595_END_INDEX) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
            setPinOutput_writeHigh(col_pins[col]);
#else
            setPinInputHigh(col_pins[col]);
#endif
        } else {
            if (col == HC595_START_INDEX) {
                HC595_output(UNSELECT_ALL_COL, false);
            }
            break;
        }
    }
}

void select_all_cols(void) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        if (col < HC595_START_INDEX || col > HC595_END_INDEX) {
            setPinOutput_writeLow(col_pins[col]);
        } else {
            if (col == HC595_START_INDEX) {
                HC595_output(SELECT_ALL_COL, false);
            }
            break;
        }
    }
}

static void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    // Select col
    select_col(current_col); // select col
    HC595_delay(200);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    HC595_delay(200); // wait for all Row signals to go HIGH
}

void matrix_init_custom(void) {
    setPinOutput(HC595_DS);
    setPinOutput(HC595_STCP);
    setPinOutput(HC595_SHCP);

    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            setPinInputHigh(row_pins[x]);
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

void suspend_wakeup_init_kb(void) {
    // code will run on keyboard wakeup
    clear_keyboard();
}
