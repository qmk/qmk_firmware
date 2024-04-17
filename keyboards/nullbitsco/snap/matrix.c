/* Copyright 2021 Jay Greco
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
#include <string.h>
#include "split_util.h"
#include "wait.h"

#define VIRT_COLS_PER_HAND 1
#define PHYS_COLS_PER_HAND (MATRIX_COLS - VIRT_COLS_PER_HAND)
#define ROWS_PER_HAND (MATRIX_ROWS / 2)
#define COL_SHIFTER ((uint32_t)1)
#define EXT_PIN_ROW 2
#define EXT_PIN_COL 8

// Row & column pins
static uint8_t  row_pins_left[MATRIX_ROWS]      = MATRIX_ROW_PINS;
static uint8_t  col_pins_left[MATRIX_MUX_COLS]  = MATRIX_COL_MUX_PINS;
static uint8_t  row_pins_right[MATRIX_ROWS]     = MATRIX_ROW_PINS_RIGHT;
static uint8_t  col_pins_right[MATRIX_MUX_COLS] = MATRIX_COL_MUX_PINS_RIGHT;
static uint8_t* row_pins                        = row_pins_left;
static uint8_t* col_pins                        = col_pins_left;

// Internal functions
static void init_pins(void) {
    // Set cols to outputs, low
    for (uint8_t pin = 0; pin < MATRIX_MUX_COLS; pin++) {
        setPinOutput(col_pins[pin]);
    }

    // Unselect cols
    for (uint8_t bit = 0; bit < MATRIX_MUX_COLS; bit++) {
        writePinLow(col_pins[bit]);
    }

    // Set rows to input, pullup
    for (uint8_t pin = 0; pin < ROWS_PER_HAND; pin++) {
        setPinInputHigh(row_pins[pin]);
    }

    // Set extended pin (only on right side)
    if (!isLeftHand) {
        // Set extended pin to input, pullup
        setPinInputHigh(MATRIX_EXT_PIN_RIGHT);
    }
}

static void select_col(uint8_t col) {
    // Drive demux with correct column address
    for (uint8_t bit = 0; bit < MATRIX_MUX_COLS; bit++) {
        uint8_t state = (col & (0b1 << bit)) >> bit;
        writePin(col_pins[bit], !state);
    }
}

static void read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    select_col(current_col % PHYS_COLS_PER_HAND);
    wait_us(5);

    // Read each row sequentially
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        if (readPin(row_pins[row_index]) == 0) {
            current_matrix[row_index] |= (COL_SHIFTER << current_col);
        } else {
            current_matrix[row_index] &= ~(COL_SHIFTER << current_col);
        }
    }
}

static void read_ext_pin(matrix_row_t current_matrix[]) {
    // Read the state of the extended matrix pin
    if (!isLeftHand) {
        if (readPin(MATRIX_EXT_PIN_RIGHT) == 0) {
            current_matrix[EXT_PIN_ROW] |= (COL_SHIFTER << EXT_PIN_COL);
        } else {
            current_matrix[EXT_PIN_ROW] &= ~(COL_SHIFTER << EXT_PIN_COL);
        }
    }
}

void matrix_init_custom(void) {
    if (!isLeftHand) {
        row_pins = row_pins_right;
        col_pins = col_pins_right;
    }

    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t last_matrix[MATRIX_ROWS];
    memcpy(last_matrix, current_matrix, sizeof(last_matrix));

    #ifdef DEBUG_SLOW_MATRIX
    // Slow for debugging
    wait_ms(1000);
    #endif

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < PHYS_COLS_PER_HAND; current_col++) {
        read_rows_on_col(current_matrix, current_col);
    }

    // Read extended pin and store in matrix
    read_ext_pin(current_matrix);

    // Check if the matrix changed
    bool changed = memcmp(last_matrix, current_matrix, sizeof(last_matrix)) != 0;

    return changed;
}
