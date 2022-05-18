/*
Copyright 2022

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

#include "286_lt.h"
#include "print.h"
#include "debug.h"
#include "gpio.h"
#include "drivers/gpio/sn74hc595.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    dprintf("col|row: %u|%u, kc: 0x%04X, pressed: %b, time: %u, interrupt: %b, count: %u\n", record->event.key.col, record->event.key.row, keycode, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    writePinLow(C13);
    return true;
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;
    setPinOutput(C13);
    writePinLow(C13);
}

void matrix_init_user(void) {
    print("user init");
    writePinHigh(C13);
}

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    sn74hc595_setPin(current_col,0);
    //if (!a()) { // select col
    //    return;                     // skip NO_PIN col
    //}
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (readPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
            writePinLow(C13);
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
            writePinHigh(C13);
        }
    }

    // Unselect col
    sn74hc595_setPin(current_col,1);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}
