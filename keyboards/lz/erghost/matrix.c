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
 * These columns use two 74HC138 3 to 8 bit demultiplexer. B0, F1 is the enable pin, must be set high (1) to use it.
 *
 * col / pin:     PB5  PB7  PF0  PB0  PF1  PE6
 * 0:              0 ── 0 ── 0    1 ── 0    0 
 * ────────────────────────────────────────────
 * 1:              0 ── 0 ── 1    1 ── 0    0
 * ────────────────────────────────────────────    
 * 2:              0 ── 1 ── 0    1 ── 0    0 
 * ────────────────────────────────────────────    
 * 3:              0 ── 1 ── 1    1 ── 0    0 
 * ────────────────────────────────────────────    
 * 4:              1 ── 0 ── 0    1 ── 0    0 
 * ────────────────────────────────────────────    
 * 5:              1 ── 0 ── 1    1 ── 0    0 
 * ────────────────────────────────────────────    
 * 6:              1 ── 1 ── 0    1 ── 0    0 
 * ────────────────────────────────────────────    
 * 7:              1 ── 1 ── 1    1 ── 0    0 
 * ────────────────────────────────────────────    
 * 8:              0 ── 0 ── 0    0 ── 1    0 
 * ────────────────────────────────────────────    
 * 9:              0 ── 0 ── 1    0 ── 1    0 
 * ────────────────────────────────────────────    
 *10:              0 ── 1 ── 0    0 ── 1    0 
 * ────────────────────────────────────────────    
 *11:              0 ── 1 ── 1    0 ── 1    0 
 * ────────────────────────────────────────────    
 *12:              1 ── 0 ── 0    0 ── 1    0 
 * ────────────────────────────────────────────    
 *13:              1 ── 0 ── 1    0 ── 1    0 
 * ────────────────────────────────────────────    
 *14:              1 ── 1 ── 1    0 ── 1    0 
 * ────────────────────────────────────────────    
 *15:              1 ── 1 ── 0    0 ── 1    0 
 * ────────────────────────────────────────────    
 *16:              0 ── 0 ── 0    0 ── 0    1  
 *
 */
static void select_col(uint8_t col) {
    switch (col) {
        case 0:
          writePinLow(B5);
          writePinLow(B7);
          writePinLow(F0);
          writePinHigh(B0);
          break;
        case 1:
          writePinLow(B5);
          writePinLow(B7);
          writePinHigh(F0);
          writePinHigh(B0);
          break;
        case 2:
          writePinLow(B5);
          writePinHigh(B7);
          writePinLow(F0);
          writePinHigh(B0);
          break;
        case 3:
          writePinLow(B5);
          writePinHigh(B7);
          writePinHigh(F0);
          writePinHigh(B0);
          break;
        case 4:
          writePinHigh(B5);
          writePinLow(B7);
          writePinLow(F0);
          writePinHigh(B0);
          break;
        case 5:
          writePinHigh(B5);
          writePinLow(B7);
          writePinHigh(F0);
          writePinHigh(B0);
          break;
        case 6:
          writePinHigh(B5);
          writePinHigh(B7);
          writePinLow(F0);
          writePinHigh(B0);
          break;
        case 7:
          writePinHigh(B5);
          writePinHigh(B7);
          writePinHigh(F0);
          writePinHigh(B0);
          break;
        case 8:
          writePinLow(B5);
          writePinLow(B7);
          writePinLow(F0);
          writePinHigh(F1);
          break;
        case 9:
          writePinLow(B5);
          writePinLow(B7);
          writePinHigh(F0);
          writePinHigh(F1);
          break;
        case 10:
          writePinLow(B5);
          writePinHigh(B7);
          writePinLow(F0);
          writePinHigh(F1);
          break;
        case 11:
          writePinLow(B5);
          writePinHigh(B7);
          writePinHigh(F0);
          writePinHigh(F1);
          break;
        case 12:
          writePinHigh(B5);
          writePinLow(B7);
          writePinLow(F0);
          writePinHigh(F1);
          break;
        case 13:
          writePinHigh(B5);
          writePinLow(B7);
          writePinHigh(F0);
          writePinHigh(F1);
          break;
        case 14:
          writePinHigh(B5);
          writePinHigh(B7);
          writePinHigh(F0);
          writePinHigh(F1);
          break;
        case 15:
          writePinHigh(B5);
          writePinHigh(B7);
          writePinLow(F0);
          writePinHigh(F1);
          break;
        case 16:
          writePinLow(E6);
          break;
    }
}

static void unselect_col(uint8_t col) {
    switch (col) {
        case 0:
          writePinHigh(B5);
          writePinHigh(B7);
          writePinHigh(F0);
          writePinLow(B0);
          break;
        case 1:
          writePinHigh(B5);
          writePinHigh(B7);
          writePinLow(F0);
          writePinLow(B0);
          break;
        case 2:
          writePinHigh(B5);
          writePinLow(B7);
          writePinHigh(F0);
          writePinLow(B0);
          break;
        case 3:
          writePinHigh(B5);
          writePinLow(B7);
          writePinLow(F0);
          writePinLow(B0);
          break;
        case 4:
          writePinLow(B5);
          writePinHigh(B7);
          writePinHigh(F0);
          writePinLow(B0);
          break;
        case 5:
          writePinLow(B5);
          writePinHigh(B7);
          writePinLow(F0);
          writePinLow(B0);
          break;
        case 6:
          writePinLow(B5);
          writePinLow(B7);
          writePinHigh(F0);
          writePinLow(B0);
          break;
        case 7:
          writePinLow(B5);
          writePinLow(B7);
          writePinLow(F0);
          writePinLow(B0);
          break;
        case 8:
          writePinHigh(B5);
          writePinHigh(B7);
          writePinHigh(F0);
          writePinLow(F1);
          break;
        case 9:
          writePinHigh(B5);
          writePinHigh(B7);
          writePinLow(F0);
          writePinLow(F1);
          break;
        case 10:
          writePinHigh(B5);
          writePinLow(B7);
          writePinHigh(F0);
          writePinLow(F1);
          break;
        case 11:
          writePinHigh(B5);
          writePinLow(B7);
          writePinLow(F0);
          writePinLow(F1);
          break;
        case 12:
          writePinLow(B5);
          writePinHigh(B7);
          writePinHigh(F0);
          writePinLow(F1);
          break;
        case 13:
          writePinLow(B5);
          writePinHigh(B7);
          writePinLow(F0);
          writePinLow(F1);
          break;
        case 14:
          writePinLow(B5);
          writePinLow(B7);
          writePinLow(F0);
          writePinLow(F1);
          break;
        case 15:
          writePinLow(B5);
          writePinLow(B7);
          writePinHigh(F0);
          writePinLow(F1);
          break;
        case 16:
          writePinHigh(E6);
          break;
    }
}

static void unselect_cols(void) {
    //Native
    writePinHigh(E6);

    //Demultiplexer
    writePinLow(B0);
    writePinLow(F1);
    writePinHigh(B5);
    writePinHigh(B7);
    writePinHigh(F0);
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
    setPinOutput(B5);
    setPinOutput(B7);
    setPinOutput(F0);
    setPinOutput(B0);
    setPinOutput(F1);
    setPinOutput(E6);
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

