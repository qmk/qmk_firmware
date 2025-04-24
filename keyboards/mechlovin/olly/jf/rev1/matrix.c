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

#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"

#ifdef DIRECT_PINS
static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
#elif (DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW)
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
//static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif

// matrix code

#ifdef DIRECT_PINS

static void init_pins(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            pin_t pin = direct_pins[row][col];
            if (pin != NO_PIN) {
                gpio_set_pin_input_high(pin);
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
            current_matrix[current_row] |= gpio_read_pin(pin) ? 0 : (MATRIX_ROW_SHIFTER << col_index);
        }
    }

    return (last_row_value != current_matrix[current_row]);
}

#elif (DIODE_DIRECTION == COL2ROW)

static void select_row(uint8_t row) {
    gpio_set_pin_output(row_pins[row]);
    gpio_write_pin_low(row_pins[row]);
}

static void unselect_row(uint8_t row) { gpio_set_pin_input_high(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        gpio_set_pin_input_high(row_pins[x]);
    }
}

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        gpio_set_pin_input_high(col_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    wait_us(30);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

        // Select the col pin to read (active low)
        uint8_t pin_state = gpio_read_pin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

#elif (DIODE_DIRECTION == ROW2COL)

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
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_high(B4);
          break;
        case 1:
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_high(B4);
          break;
        case 2:
          gpio_write_pin_low(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_high(B4);
          break;
        case 3:
          gpio_write_pin_low(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_high(B4);
          break;
        case 4:
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_high(B4);
          break;
        case 5:
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_high(B4);
          break;
        case 6:
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_high(B4);
          break;
        case 7:
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_high(B4);
          break;
        case 8:
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_high(C7);
          break;
        case 9:
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_high(C7);
          break;
        case 10:
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_high(C7);
          break;
        case 11:
          gpio_write_pin_low(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_high(C7);
          break;
        case 12:
          gpio_write_pin_low(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_high(C7);
          break;
        case 13:
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_high(C7);
          break;
        case 14:
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_high(C7);
          break;
        case 15:
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_high(C7);
          break;
        case 16:
          gpio_write_pin_low(C2);
          break;
        case 17:
          gpio_write_pin_low(C3);
          break;
        case 18:
          gpio_write_pin_low(C5);
          break;
    }
}

static void unselect_col(uint8_t col) {
    switch (col) {
        case 0:
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_low(B4);
          break;
        case 1:
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_low(B4);
          break;
        case 2:
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_low(B4);
          break;
        case 3:
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_low(B4);
          break;
        case 4:
          gpio_write_pin_low(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_low(B4);
          break;
        case 5:
          gpio_write_pin_low(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_low(B4);
          break;
        case 6:
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_low(B4);
          break;
        case 7:
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_low(B4);
          break;
        case 8:
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_low(C7);
          break;
        case 9:
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_low(C7);
          break;
        case 10:
          gpio_write_pin_high(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_low(C7);
          break;
        case 11:
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_low(C7);
          break;
        case 12:
          gpio_write_pin_high(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_low(C7);
          break;
        case 13:
          gpio_write_pin_low(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_low(C7);
          break;
        case 14:
          gpio_write_pin_low(A0);
          gpio_write_pin_high(A1);
          gpio_write_pin_low(A2);
          gpio_write_pin_low(C7);
          break;
        case 15:
          gpio_write_pin_low(A0);
          gpio_write_pin_low(A1);
          gpio_write_pin_high(A2);
          gpio_write_pin_low(C7);
          break;
        case 16:
          gpio_write_pin_high(C2);
          break;
        case 17:
          gpio_write_pin_high(C3);
          break;
        case 18:
          gpio_write_pin_high(C5);
          break;
    }
}

static void unselect_cols(void) {
    //Native
    gpio_write_pin_high(C2);
    gpio_write_pin_high(C3);
    gpio_write_pin_high(C5);

    //Demultiplexer
    gpio_write_pin_low(B4);
    gpio_write_pin_low(C7);
    gpio_write_pin_high(A0);
    gpio_write_pin_high(A1);
    gpio_write_pin_high(A2);
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        gpio_set_pin_input_high(row_pins[x]);
    }
    gpio_set_pin_output(A0);
    gpio_set_pin_output(A1);
    gpio_set_pin_output(A2);
    gpio_set_pin_output(B4);
    gpio_set_pin_output(C7);
    gpio_set_pin_output(C2);
    gpio_set_pin_output(C3);
    gpio_set_pin_output(C5);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (gpio_read_pin(row_pins[row_index]) == 0) {
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

#endif

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }
#elif (DIODE_DIRECTION == ROW2COL)
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }
#endif

    return changed;
}
