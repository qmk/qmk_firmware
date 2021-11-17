/*
Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar
Copyright 2019 Evy Dekkers

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

#include "matrix.h"
#include "gpio.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

/* Cols 0 - 16
 * These columns use two 74HC138 3 to 8 bit demultiplexer. B4, C7 is the enable pin, must be set high (1) to use it.
 *
 * col / pin:     PA0  PA1  PA2  PB4  PC7  PC2  PC3  PC5
 * 0:              0 ── 0 ── 0    1 ── 0    0    0    0
 * ────────────────────────────────────────────
 * 1:              0 ── 0 ── 1    1 ── 0    0    0    0
 * ────────────────────────────────────────────
 * 2:              0 ── 1 ── 0    1 ── 0    0    0    0
 * ────────────────────────────────────────────
 * 3:              0 ── 1 ── 1    1 ── 0    0    0    0
 * ────────────────────────────────────────────
 * 4:              1 ── 0 ── 0    1 ── 0    0    0    0
 * ────────────────────────────────────────────
 * 5:              1 ── 0 ── 1    1 ── 0    0    0    0
 * ────────────────────────────────────────────
 * 6:              1 ── 1 ── 0    1 ── 0    0    0    0
 * ────────────────────────────────────────────
 * 7:              1 ── 1 ── 1    1 ── 0    0    0    0
 * ────────────────────────────────────────────
 * 8:              1 ── 1 ── 1    0 ── 1    0    0    0
 * ────────────────────────────────────────────
 * 9:              0 ── 0 ── 0    0 ── 1    0    0    0
 * ────────────────────────────────────────────
 *10:              0 ── 0 ── 1    0 ── 1    0    0    0
 * ────────────────────────────────────────────
 *11:              0 ── 1 ── 0    0 ── 1    0    0    0
 * ────────────────────────────────────────────
 *12:              0 ── 1 ── 1    0 ── 1    0    0    0
 * ────────────────────────────────────────────
 *13:              1 ── 0 ── 0    0 ── 1    0    0    0
 * ────────────────────────────────────────────
 *14:              1 ── 0 ── 1    0 ── 1    0    0    0
 * ────────────────────────────────────────────
 *15:              1 ── 1 ── 0    0 ── 1    0    0    0
 * ────────────────────────────────────────────
 *16:              0 ── 0 ── 0    0 ── 0    1    0    0
 * ────────────────────────────────────────────
 *17:              0 ── 0 ── 0    0 ── 0    0    1    0
 * ────────────────────────────────────────────
 *18:              0 ── 0 ── 0    0 ── 0    0    0    1
 *
 */
static void select_col(uint8_t col) {
    switch (col) {
        case 0:
          writePinLow(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinHigh(B4);
          break;
        case 1:
          writePinLow(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinHigh(B4);
          break;
        case 2:
          writePinLow(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinHigh(B4);
          break;
        case 3:
          writePinLow(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinHigh(B4);
          break;
        case 4:
          writePinHigh(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinHigh(B4);
          break;
        case 5:
          writePinHigh(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinHigh(B4);
          break;
        case 6:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinHigh(B4);
          break;
        case 7:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinHigh(B4);
          break;
        case 8:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinHigh(C7);
          break;
        case 9:
          writePinLow(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinHigh(C7);
          break;
        case 10:
          writePinLow(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinHigh(C7);
          break;
        case 11:
          writePinLow(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinHigh(C7);
          break;
        case 12:
          writePinLow(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinHigh(C7);
          break;
        case 13:
          writePinHigh(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinHigh(C7);
          break;
        case 14:
          writePinHigh(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinHigh(C7);
          break;
        case 15:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinHigh(C7);
          break;
        case 16:
          writePinLow(C2);
          break;
        case 17:
          writePinLow(C3);
          break;
        case 18:
          writePinLow(C5);
          break;
    }
}

static void unselect_col(uint8_t col) {
    switch (col) {
        case 0:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinLow(B4);
          break;
        case 1:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinLow(B4);
          break;
        case 2:
          writePinHigh(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinLow(B4);
          break;
        case 3:
          writePinHigh(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinLow(B4);
          break;
        case 4:
          writePinLow(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinLow(B4);
          break;
        case 5:
          writePinLow(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinLow(B4);
          break;
        case 6:
          writePinLow(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinLow(B4);
          break;
        case 7:
          writePinLow(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinLow(B4);
          break;
        case 8:
          writePinLow(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinLow(C7);
          break;
        case 9:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinLow(C7);
          break;
        case 10:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinLow(C7);
          break;
        case 11:
          writePinHigh(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinLow(C7);
          break;
        case 12:
          writePinHigh(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinLow(C7);
          break;
        case 13:
          writePinLow(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinLow(C7);
          break;
        case 14:
          writePinLow(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinLow(C7);
          break;
        case 15:
          writePinLow(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinLow(C7);
          break;
        case 16:
          writePinHigh(C2);
          break;
        case 17:
          writePinHigh(C3);
          break;
        case 18:
          writePinHigh(C5);
          break;
    }
}

static void unselect_cols(void) {
    //Native
    writePinHigh(C2);
    writePinHigh(C3);
    writePinHigh(C5);

    //Demultiplexer
    writePinLow(B4);
    writePinLow(C7);
    writePinHigh(A0);
    writePinHigh(A1);
    writePinHigh(A2);
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
    setPinOutput(A0);
    setPinOutput(A1);
    setPinOutput(A2);
    setPinOutput(B4);
    setPinOutput(C7);
    setPinOutput(C2);
    setPinOutput(C3);
    setPinOutput(C5);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    matrix_io_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
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

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }

    return changed;
}
