/* Copyright 2022 Jack Kester
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

#include "config.h"
#include "quantum.h"

#define SHIFTER ((uint32_t)1)

static const uint8_t row_pins[MATRIX_ROW_PIN_COUNT] = MATRIX_ROW_PINS;
static const uint8_t row_masks[MATRIX_ROWS] = MATRIX_ROW_MASKS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static void select_row(uint8_t row) {
    uint8_t mask = row_masks[row];
    for(uint8_t i = 0; i<MATRIX_ROW_PIN_COUNT; i++){
        writePin(row_pins[i], (mask>>(MATRIX_ROW_PIN_COUNT-1-i))&1);
    }
}

void matrix_init_custom(void){
    //output on row pins to select row
    for (uint8_t pin = 0; pin < MATRIX_ROW_PIN_COUNT; pin++) {
        setPinOutput(row_pins[pin]);
    }
    //input on cols to read from cols
    for (uint8_t pin = 0; pin < MATRIX_COLS; pin++) {
        setPinInputHigh(col_pins[pin]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row){
    select_row(current_row);
    wait_us(MATRIX_IO_DELAY);

    matrix_row_t last_row_value = current_matrix[current_row];

    for(uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++){

        if (!readPin(col_pins[current_col])){
            current_matrix[current_row] |=  (SHIFTER << current_col);
        }else{
            current_matrix[current_row] &= ~(SHIFTER << current_col);
        }

    }

    return last_row_value != current_matrix[current_row];
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed = read_cols_on_row(current_matrix, current_row) || changed;
    }

    return changed;
}

#undef SHIFTER
