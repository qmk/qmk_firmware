/*
Copyright 2023 Cutie Club

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
#include "quantum.h"
#include "i2c_master.h"
#include "print.h"

#include "pcal6416a/pcal6416a.h"
#include "indicator_leds.h"
#include "lib/i2c_helpers.h"

static const pcal_gpio_pin row_pins[MATRIX_ROWS] = PCAL_ROW_PINS;
static const pcal_gpio_pin column_pins[MATRIX_COLS] = PCAL_COL_PINS;

static i2c_status_t update_matrix_for_row(uint8_t row, matrix_row_t current_matrix[], bool* row_changed) {
    matrix_row_t previous_row_state = current_matrix[row];
    current_matrix[row] = 0;

    RETURN_STATUS_IF_I2C_FAIL(pcal_write_pin(row_pins[row], LOW));

    for (uint8_t column = 0; column < MATRIX_COLS; column++) {
        pcal_gpio_pin current_column_pin = column_pins[column];
        pcal_gpio_state pin_state = HIGH;
        RETURN_STATUS_IF_I2C_FAIL(pcal_read_pin(current_column_pin, &pin_state));
        if(pin_state == LOW) {
            current_matrix[row] |= (1 << column);
        }
    }

    RETURN_STATUS_IF_I2C_FAIL(pcal_write_pin(row_pins[row], HIGH));

    *row_changed = previous_row_state != current_matrix[row];
    if (*row_changed){
        uprintf("Row %d Changed\n", row);
    }
    return I2C_STATUS_SUCCESS;
}

static i2c_status_t init_io_expander(void) {
    RETURN_STATUS_IF_I2C_FAIL(set_pin_array_direction(column_pins, MATRIX_COLS, INPUT_PULLUP));
    RETURN_STATUS_IF_I2C_FAIL(set_pin_array_initial_state(row_pins, MATRIX_ROWS, HIGH));
    return I2C_STATUS_SUCCESS;
}

#define I2C_SUCCESS(i2c_status) (i2c_status == I2C_STATUS_SUCCESS)

static bool board_connected = false;

void matrix_init_custom(void) {
    i2c_init();
    board_connected = I2C_SUCCESS(init_io_expander()) && indicator_leds_init() == 0;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    if(!board_connected) {
        // Release all keys in matrix
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            matrix_row_t previous_row = current_matrix[row];
            current_matrix[row] = 0;
            if(!matrix_has_changed) matrix_has_changed = previous_row != current_matrix[row];
        }
        // Early return to ensure any currently held keys are released immediately otherwise
        // keys will be held for longer than necessary while waiting for i2c timeouts
        if (matrix_has_changed) return matrix_has_changed;

        bool board_detected = I2C_SUCCESS(init_io_expander());
        if (board_detected) {
            // board has been re-inserted, sometimes when the cable is initially inserted the I/O expander
            // may end up in a partially setup state because of this a delay and re-call of init_io_expander()
            // is used to ensure the board is correctly configured
            _delay_ms(500);
            board_connected = I2C_SUCCESS(init_io_expander());
            // Update leds to reflect the keyboards state
            led_update_kb(host_keyboard_led_state());
        }
    } else {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool row_changed = false;

            board_connected = I2C_SUCCESS(update_matrix_for_row(row, current_matrix, &row_changed));
            if(!board_connected) break;

            if(!matrix_has_changed && row_changed) {
                matrix_has_changed = true;
            }
        }
    }

    return matrix_has_changed;
}
