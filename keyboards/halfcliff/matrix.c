/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
#include "atomic_util.h"
#include "split_util.h"
#include "transport.h"
#include "debounce.h"
#include "wait.h"

#define ERROR_DISCONNECT_COUNT 5

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
static matrix_row_t matrix[MATRIX_ROWS];     // debounced values

// row offsets for each hand
uint8_t thisHand, thatHand;

// user-defined overridable functions
__attribute__((weak)) void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__((weak)) void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_slave_scan_user(void) {}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {}

static inline void gpio_atomic_set_pin_output_low(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void gpio_atomic_set_pin_input_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

// matrix code
static void select_row(uint8_t row) {
    gpio_atomic_set_pin_output_low(row_pins[row]);
}

static void unselect_row(uint8_t row) {
    gpio_atomic_set_pin_input_high(row_pins[row]);
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
        gpio_atomic_set_pin_input_high(row_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    // Select row
    select_row(current_row);
    wait_us(30);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = gpio_read_pin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);
    if (current_row + 1 < MATRIX_ROWS) {
        wait_us(30); // wait for row signal to go HIGH
    }

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }
    return false;
}

static void select_col(uint8_t col) {
    gpio_atomic_set_pin_output_low(col_pins[col]);
}

static void unselect_col(uint8_t col) {
    gpio_atomic_set_pin_input_high(col_pins[col]);
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        gpio_atomic_set_pin_input_high(col_pins[x]);
    }
}

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        gpio_atomic_set_pin_input_high(col_pins[x]);
    }
    unselect_cols();
    for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
        gpio_atomic_set_pin_input_high(row_pins[x]);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col
    select_col(current_col);
    wait_us(30);

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value    = current_matrix[row_index];
        matrix_row_t current_row_value = last_row_value;

        // Check row pin state
        if (gpio_read_pin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_row_value)) {
            matrix_changed |= true;
            current_matrix[row_index] = current_row_value;
        }
    }

    // Unselect col
    unselect_col(current_col);
    if (current_col + 1 < MATRIX_COLS) {
        wait_us(30); // wait for col signal to go HIGH
    }

    return matrix_changed;
}

void matrix_init(void) {
    split_pre_init();

    // Set pinout for right half if pinout for that half is defined
    if (!isLeftHand) {
#ifdef DIRECT_PINS_RIGHT
        const pin_t direct_pins_right[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS_RIGHT;
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            for (uint8_t j = 0; j < MATRIX_COLS; j++) {
                direct_pins[i][j] = direct_pins_right[i][j];
            }
        }
#endif
#ifdef MATRIX_ROW_PINS_RIGHT
        const pin_t row_pins_right[MATRIX_ROWS] = MATRIX_ROW_PINS_RIGHT;
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            row_pins[i] = row_pins_right[i];
        }
#endif
#ifdef MATRIX_COL_PINS_RIGHT
        const pin_t col_pins_right[MATRIX_COLS] = MATRIX_COL_PINS_RIGHT;
        for (uint8_t i = 0; i < MATRIX_COLS; i++) {
            col_pins[i] = col_pins_right[i];
        }
#endif
    }

    thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
    thatHand = ROWS_PER_HAND - thisHand;

    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init();

    matrix_init_kb();

    split_post_init();
}

bool matrix_post_scan(void) {
    bool changed = false;
    if (is_keyboard_master()) {
        static uint8_t error_count;

        matrix_row_t slave_matrix[ROWS_PER_HAND] = {0};
        if (!transport_master(matrix + thisHand, slave_matrix)) {
            error_count++;

            if (error_count > ERROR_DISCONNECT_COUNT) {
                // reset other half if disconnected
                for (int i = 0; i < ROWS_PER_HAND; ++i) {
                    matrix[thatHand + i] = 0;
                    slave_matrix[i]      = 0;
                }

                changed = true;
            }
        } else {
            error_count = 0;

            for (int i = 0; i < ROWS_PER_HAND; ++i) {
                if (matrix[thatHand + i] != slave_matrix[i]) {
                    matrix[thatHand + i] = slave_matrix[i];
                    changed              = true;
                }
            }
        }

        matrix_scan_kb();
    } else {
        transport_slave(matrix + thatHand, matrix + thisHand);

        matrix_slave_scan_user();
    }

    return changed;
}

uint8_t matrix_scan(void) {
    bool                local_changed = false;
    static matrix_row_t temp_raw_matrix[MATRIX_ROWS]; // temp raw values

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < ROWS_PER_HAND / 2; current_row++) {
        local_changed |= read_cols_on_row(raw_matrix, current_row);
    }

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        local_changed |= read_rows_on_col(temp_raw_matrix, current_col);
        // Updated key matrix on lines 6-10 (or lines 16-20)
        if (local_changed) {
            for (uint8_t i = ROWS_PER_HAND / 2; i < ROWS_PER_HAND; i++) {
                raw_matrix[i] = temp_raw_matrix[i];
            }
        }
    }

    debounce(raw_matrix, matrix + thisHand, local_changed);

    bool remote_changed = matrix_post_scan();
    return (uint8_t)(local_changed || remote_changed);
}
