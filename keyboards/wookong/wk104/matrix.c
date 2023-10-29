/* Copyright 2023 Gyphae Team <https://github.com/gyphae>
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
#include "matrix.h"
#include "gpio.h"

#ifndef GPIOH_BASE
#   define GPIOH_BASE  (0xFF595A00U)
#endif

#ifndef SHR_SERIES_NUM
#   define SHR_SERIES_NUM 1
#endif

static uint8_t shift_values[SHR_SERIES_NUM] = {0};

static void 	shift_out(void);
static void	   	shift_writeAll(int level);
static uint8_t 	read_rows(void);
static void    	init_cols(void);
static void    	select_col(uint8_t col);
static void    	unselect_col(uint8_t col);

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;


void shift_out(void) {
    uint8_t n = SHR_SERIES_NUM;
    writePinLow(SHR_LATCH_PIN);
    while(n--){
        for (uint8_t i = 0; i < 8; i++) {
            writePinLow(SHR_CLOCK_PIN);
            writePin(SHR_DATA_PIN, shift_values[n] & (0x80 >> i));
            writePinHigh(SHR_CLOCK_PIN);
	    }
    }
    writePinHigh(SHR_LATCH_PIN);
}

void shift_writeAll(int level) {
    memset(shift_values, level ? 0xFF : 0, sizeof(shift_values));
    shift_out();
}

void shift_writePin(pin_t pin, int level) {
	uint8_t group = (pin - H0) >> 3;
	uint8_t	bit = 0x01 << ((pin - H0)&0x07);

    if(group >= SHR_SERIES_NUM) 
        return;

    if(level)
        shift_values[group] |= bit;
    else
        shift_values[group] &= ~bit;
    shift_out();
}


void matrix_init_custom(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        setPinInputLow(row_pins[row]);
    }
    
	setPinOutput(SHR_DATA_PIN);
    setPinOutput(SHR_LATCH_PIN);
    setPinOutput(SHR_CLOCK_PIN);
	
    init_cols();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        waitInputPinDelay();
        uint8_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = ((uint32_t)(current_matrix[row]) & (matrix_row_t)(1UL << col)) ? 1 : 0;
            bool curr_bit = ((uint32_t)rows & (uint32_t)(1UL << row)) ? 1 : 0;
            if (prev_bit != curr_bit) {
                current_matrix[row] = (uint32_t)(current_matrix[row]) ^ (uint32_t)(1UL << col);
                matrix_has_changed = true;
            }
        }
        unselect_col(col);
    }

    return matrix_has_changed;
}

static uint8_t read_rows(void) {
    uint8_t row_value = 0;
    for(uint8_t row = 0; row < MATRIX_ROWS; row++) {
        row_value |= (readPin(row_pins[row]) << row);
    }
    return row_value;
}

static void init_cols(void) {
    shift_writeAll(0);
    for(uint8_t col = 0; col < MATRIX_COLS; col++) {
        if(col_pins[col] < H0) {
            setPinOutput(col_pins[col]);
            writePinLow(col_pins[col]);
        }
    }
}

static void select_col(uint8_t col) {
    if(col_pins[col] < H0){
        writePinHigh(col_pins[col]);
        waitInputPinDelay();
        waitInputPinDelay();
        waitInputPinDelay();
        waitInputPinDelay();
        waitInputPinDelay();
        waitInputPinDelay();
    }else{
        shift_writePin(col_pins[col], 1);
    }
}

static void unselect_col(uint8_t col) {
    if(col_pins[col] < H0){
        writePinLow(col_pins[col]);
    }else{
        shift_writePin(col_pins[col], 0);
    }
}
