/*
Copyright 2019 worthlessowl
based on work by:
Jun Wako <wakojun@gmail.com>
Cole Markham <cole@ccmcomputing.net>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "timer.h"

#if (MATRIX_COLS <= 8)
#    define print_matrix_header() print("\nr/c 01234567\n")
#    define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse16(matrix_get_row(row))
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse32(matrix_get_row(row))
#    define ROW_SHIFTER ((uint32_t)1)
#endif

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_select_pins[3]    = MATRIX_COL_SELECT_PINS;
static const uint8_t dat_pin               = MATRIX_COL_DATA_PIN;

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
static matrix_row_t matrix[MATRIX_ROWS];     // raw values

/* 2d array containing binary representation of its index */
static const uint8_t num_in_binary[8][3] = {
    {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1},
};

static void select_col_analog(uint8_t col);
static void mux_pin_control(const uint8_t binary[]);
void        debounce_init(void);
void        debounce(matrix_row_t raw[], matrix_row_t cooked[], bool changed);

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__((weak)) void matrix_scan_kb(void) {
    matrix_scan_user();
}

inline uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & ((matrix_row_t)1 << col));
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

void matrix_print(void) {
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

// uses standard row code
static void select_row(uint8_t row) {
    gpio_set_pin_output(row_pins[row]);
    gpio_write_pin_low(row_pins[row]);
}

static void unselect_row(uint8_t row) {
    gpio_set_pin_input_high(row_pins[row]);
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        gpio_set_pin_input_high(row_pins[x]);
    }
}

static void init_pins(void) { // still need some fixing, this might not work
    unselect_rows();          // with the loop
    /*
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
      gpio_set_pin_input_high(col_pins[x]);
    }
    */
    gpio_set_pin_input_high(dat_pin);
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
        select_col_analog(col_index);
        wait_us(30);
        uint8_t pin_state = gpio_read_pin(dat_pin);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |= pin_state ? 0 : (ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

void matrix_init(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init();

    matrix_init_kb();

    gpio_set_pin_input(D5);
    gpio_set_pin_input(B0);
}

// modified for per col read matrix scan
uint8_t matrix_scan(void) {
    bool changed = false;

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }

    debounce(raw_matrix, matrix, changed);

    matrix_scan_kb();
    return (uint8_t)changed;
}

/*
uint8_t matrix_scan(void)
{
  bool changed = false;

#if (DIODE_DIRECTION == COL2ROW)
  // Set row, read cols
  for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    changed |= read_cols_on_row(raw_matrix, current_row);
  }
#endif

  debounce(raw_matrix, matrix, changed);

  matrix_scan_kb();
  return (uint8_t)changed;
}
*/

static void select_col_analog(uint8_t col) {
    switch (col) {
        case 0:
            mux_pin_control(num_in_binary[0]);
            break;
        case 1:
            mux_pin_control(num_in_binary[1]);
            break;
        case 2:
            mux_pin_control(num_in_binary[2]);
            break;
        case 3:
            mux_pin_control(num_in_binary[3]);
            break;
        case 4:
            mux_pin_control(num_in_binary[4]);
            break;
        case 5:
            mux_pin_control(num_in_binary[5]);
            break;
        case 6:
            mux_pin_control(num_in_binary[6]);
            break;
        case 7:
            mux_pin_control(num_in_binary[7]);
            break;
        default:
            break;
    }
}

static void mux_pin_control(const uint8_t binary[]) {
    // set pin0
    gpio_set_pin_output(col_select_pins[0]);
    if (binary[2] == 0) {
        gpio_write_pin_low(col_select_pins[0]);
    } else {
        gpio_write_pin_high(col_select_pins[0]);
    }
    // set pin1
    gpio_set_pin_output(col_select_pins[1]);
    if (binary[1] == 0) {
        gpio_write_pin_low(col_select_pins[1]);
    } else {
        gpio_write_pin_high(col_select_pins[1]);
    }
    // set pin2
    gpio_set_pin_output(col_select_pins[2]);
    if (binary[0] == 0) {
        gpio_write_pin_low(col_select_pins[2]);
    } else {
        gpio_write_pin_high(col_select_pins[2]);
    }
}
