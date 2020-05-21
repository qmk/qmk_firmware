/*
Copyright 2012-2020 Jun Wako, Jack Humbert, Yiancar, Ein Terakawa

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
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

#ifdef DIRECT_PINS
static const pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
#else
static const pin_t row_pins[] = MATRIX_ROW_PINS;
static const pin_t col_pins[] = MATRIX_COL_PINS;

/* Consistency checking of the size of the matrix and the number of pins */
// clang-format off
#    if (DIODE_DIRECTION == BOTHWAYS)
#        define NUM_ROW_PINS (MATRIX_ROWS / 2)
_Static_assert(NUM_ROW_PINS * 2 == MATRIX_ROWS, "Must be exactly divisible");
_Static_assert(NUM_ROW_PINS == sizeof(row_pins)/sizeof(row_pins[0]), \
    "Number of elements in MATRIX_ROW_PINS * 2 must be equal to MATRIX_ROWS");
#    else
#        define NUM_ROW_PINS MATRIX_ROWS
_Static_assert(NUM_ROW_PINS == sizeof(row_pins)/sizeof(row_pins[0]), \
    "Number of elements in MATRIX_ROW_PINS must be equal to MATRIX_ROWS");
#    endif

_Static_assert(MATRIX_COLS == sizeof(col_pins)/sizeof(col_pins[0]), \
    "Number of elements in MATRIX_COL_PINS must be equal to MATRIX_COLS");
// clang-format on
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
#if (DIODE_DIRECTION == EITHERWAY)
static matrix_row_t last_matrix[MATRIX_ROWS];  // raw values of last scan
#endif
extern matrix_row_t matrix[MATRIX_ROWS];  // debounced values

// matrix code

#ifdef DIRECT_PINS

static void init_pins(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            pin_t pin = direct_pins[row][col];
            if (pin != NO_PIN) {
                setPinInputHigh(pin);
            }
        }
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t last_row_value = current_matrix[current_row];
    current_matrix[current_row] = 0;

    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        pin_t pin = direct_pins[current_row][col_index];
        if (pin != NO_PIN) {
            current_matrix[current_row] |= readPin(pin) ? 0 : (MATRIX_ROW_SHIFTER << col_index);
        }
    }

    return (last_row_value != current_matrix[current_row]);
}

#else

#    if (DIODE_DIRECTION == COL2ROW) || (DIODE_DIRECTION == ROW2COL)
#    elif (DIODE_DIRECTION == EITHERWAY) || (DIODE_DIRECTION == BOTHWAYS)
#    else
#        error DIODE_DIRECTION must be one of COL2ROW, ROW2COL, EITHERWAY or BOTHWAYS!
#    endif

#    if (DIODE_DIRECTION != ROW2COL)
static void select_row(uint8_t row) {
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row) { setPinInputHigh(row_pins[row]); }

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    matrix_io_delay();

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}
#    endif

#    if (DIODE_DIRECTION != COL2ROW)
static void select_col(uint8_t col) {
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void unselect_col(uint8_t col) { setPinInputHigh(col_pins[col]); }

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    matrix_io_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < NUM_ROW_PINS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
#        if (DIODE_DIRECTION != EITHERWAY)
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
#        endif
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_col(current_col);

    return matrix_changed;
}
#    endif

static void unselect_rows(void) {
    for (uint8_t x = 0; x < NUM_ROW_PINS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static void init_pins(void) {
    unselect_rows();
    unselect_cols();
}

#endif

void matrix_init(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    bool changed = false;

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }
#elif (DIODE_DIRECTION == ROW2COL)
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(raw_matrix, current_col);
    }
#elif (DIODE_DIRECTION == EITHERWAY)
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        last_matrix[current_row] = raw_matrix[current_row];
        read_cols_on_row(raw_matrix, current_row);
    }
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        read_rows_on_col(raw_matrix, current_col);
    }
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        if (last_matrix[current_row] != raw_matrix[current_row]) {
            changed = true;
        }
    }
#elif (DIODE_DIRECTION == BOTHWAYS)
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS / 2; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(raw_matrix + MATRIX_ROWS / 2, current_col);
    }
#endif

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
    return (uint8_t)changed;
}
