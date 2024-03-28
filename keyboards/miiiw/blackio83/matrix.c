/* Copyright 2023 ArthurCyy <https://github.com/ArthurCyy>
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
#include "wait.h"
#include "common/shift_register.h"

static uint8_t read_rows(void);
static void    init_cols(void);
static void    select_col(uint8_t col);
static void    unselect_col(uint8_t col);
static void    unselect_cols(void);

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

#ifdef DIP_SWITCH_PINS
#    define NUMBER_OF_DIP_SWITCHES (sizeof(dip_switch_pad) / sizeof(pin_t))
static pin_t dip_switch_pad[] = DIP_SWITCH_PINS;
#endif

void matrix_init_custom(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        setPinInputLow(row_pins[row]);
    }
    
    shift_init();
    init_cols();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        waitInputPinDelay();
        uint8_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = ((uint32_t)(current_matrix[row]) & (matrix_row_t)(1UL << col)) ? 1 : 0;
            bool curr_bit = ((uint32_t)rows & (uint32_t)(1UL << row)) ? 1 : 0;
            if (prev_bit != curr_bit) {
                current_matrix[row] = (uint32_t)(current_matrix[row]) ^ (uint32_t)(1UL << col);
                changed = true;
            }
        }
        unselect_col(col);
    }

    return changed;
}

void matrix_power_up(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        palDisableLineEvent(row_pins[row]);
        setPinInputLow(row_pins[row]);
    }
    init_cols();
#ifdef DIP_SWITCH_PINS
    for (uint8_t i = 1; i < NUMBER_OF_DIP_SWITCHES; i++) {
        setPinInputHigh(dip_switch_pad[i]);
    }
#endif
}

void matrix_power_down(void) {
    unselect_cols();
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        setPinInputLow(row_pins[row]);
        palEnableLineEvent(row_pins[row], PAL_EVENT_MODE_RISING_EDGE);
    }
#ifdef DIP_SWITCH_PINS
    for (uint8_t i = 1; i < NUMBER_OF_DIP_SWITCHES; i++) {
        setPinInputLow(dip_switch_pad[i]);
    }
#endif
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

static void unselect_cols(void) {
    shift_writeAll(1);
    for(uint8_t col = 0; col < MATRIX_COLS; col++) {
        if(col_pins[col] < H0) {
            setPinOutput(col_pins[col]);
            writePinHigh(col_pins[col]);
        }
    }
}
