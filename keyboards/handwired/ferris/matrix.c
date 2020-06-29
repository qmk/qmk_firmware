/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
          2020 Pierre Chevalier <pierrechevalier83@gmail.com>

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
 * This code was heavily inspired by the ergodox_ez keymap, and modernized
 * to take advantage of the quantum.h microcontroller agnostics gpio control
 * abstractions and use the macros defined in config.h for the wiring as opposed
 * to repeating that information all over the place.
 */

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include QMK_KEYBOARD_H

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static matrix_row_t read_cols(uint8_t row);
static void         init_cols(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

static uint8_t mcp23017_reset_loop;
// static uint16_t mcp23017_reset_loop;

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

void matrix_init(void) {
    // initialize row and col

    mcp23017_status = init_mcp23017();

    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i]     = 0;
        raw_matrix[i] = 0;
    }

    debounce_init(MATRIX_ROWS);
    matrix_init_quantum();
}

void matrix_power_up(void) {
    mcp23017_status = init_mcp23017();

    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_row(uint8_t index) {
    matrix_row_t temp = read_cols(index);
    if (raw_matrix[index] != temp) {
        raw_matrix[index] = temp;
        return true;
    }
    return false;
}

uint8_t matrix_scan(void) {
    if (mcp23017_status) {  // if there was an error
        if (++mcp23017_reset_loop == 0) {
            // if (++mcp23017_reset_loop >= 1300) {
            // since mcp23017_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            print("trying to reset mcp23017\n");
            mcp23017_status = init_mcp23017();
            if (mcp23017_status) {
                print("right side not responding\n");
            } else {
                print("right side attached\n");
            }
        }
    }

    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS_PER_SIDE; i++) {
        // select rows from left and right hands
        uint8_t left_index  = i;
        uint8_t right_index = i + MATRIX_ROWS_PER_SIDE;
        select_row(left_index);
        select_row(right_index);

        // we don't need a 30us delay anymore, because selecting a
        // left-hand row requires more than 30us for i2c.

        changed |= store_raw_matrix_row(left_index);
        changed |= store_raw_matrix_row(right_index);

        unselect_rows();
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
    matrix_scan_quantum();

    return 1;
}

bool matrix_is_modified(void)  // deprecated and evidently not called.
{
    return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row);
        print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

static void init_cols(void) {
    // init on mcp23017
    // not needed, already done as part of init_mcp23017()

    // init on mcu
    pin_t matrix_col_pins_mcu[MATRIX_COLS_PER_SIDE] = MATRIX_COL_PINS_MCU;
    for (int pin_index = 0; pin_index < MATRIX_COLS_PER_SIDE; pin_index++) {
        pin_t pin = matrix_col_pins_mcu[pin_index];
        setPinInput(pin);
        writePinHigh(pin);
    }
}

static matrix_row_t read_cols(uint8_t row) {
    if (row < MATRIX_ROWS_PER_SIDE) {
        pin_t        matrix_col_pins_mcu[MATRIX_COLS_PER_SIDE] = MATRIX_COL_PINS_MCU;
        matrix_row_t current_row_value                         = 0;
        // For each col...
        for (uint8_t col_index = 0; col_index < MATRIX_COLS_PER_SIDE; col_index++) {
            // Select the col pin to read (active low)
            uint8_t pin_state = readPin(matrix_col_pins_mcu[col_index]);

            // Populate the matrix row with the state of the col pin
            current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
        }
        return current_row_value;
    } else {
        if (mcp23017_status) {  // if there was an error
            return 0;
        } else {
            uint8_t data    = 0;
            mcp23017_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);
            if (mcp23017_status) goto out;
            mcp23017_status = i2c_write(GPIOA, I2C_TIMEOUT);
            if (mcp23017_status) goto out;
            mcp23017_status = i2c_start(I2C_ADDR_READ, I2C_TIMEOUT);
            if (mcp23017_status) goto out;
            mcp23017_status = i2c_read_nack(I2C_TIMEOUT);
            if (mcp23017_status < 0) goto out;
            // We read all the pins on GPIOA.
            // The initial state was all ones and any depressed key at a given column for the currently selected row will have its bit flipped to zero.
            // The return value is a row as represented in the generic matrix code were the rightmost bits represent the lower columns and zeroes represent non-depressed keys while ones represent depressed keys.
            // Since the pins connected to eact columns are sequential, and counting from zero up (col 5 -> GPIOA0, col 6 -> GPIOA1 and so on), the only transformation needed is a bitwise not to swap all zeroes and ones.
            data            = ~((uint8_t)mcp23017_status);
            mcp23017_status = I2C_STATUS_SUCCESS;
        out:
            i2c_stop();
            // return reverse_bits(data, MATRIX_COLS_PER_SIDE);
            return data;
        }
    }
}

static void unselect_rows(void) {
    // no need to unselect on mcp23017, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction

    // unselect rows on microcontroller
    pin_t matrix_row_pins_mcu[MATRIX_ROWS_PER_SIDE] = MATRIX_ROW_PINS_MCU;
    for (int pin_index = 0; pin_index < MATRIX_ROWS_PER_SIDE; pin_index++) {
        pin_t pin = matrix_row_pins_mcu[pin_index];
        setPinInput(pin);
        writePinLow(pin);
    }
}

static void select_row(uint8_t row) {
    if (row < MATRIX_ROWS_PER_SIDE) {
        // select on atmega32u4
        pin_t matrix_row_pins_mcu[MATRIX_ROWS_PER_SIDE] = MATRIX_ROW_PINS_MCU;
        pin_t pin                                       = matrix_row_pins_mcu[row];
        setPinOutput(pin);
        writePinLow(pin);
    } else {
        // select on mcp23017
        if (mcp23017_status) {  // if there was an error
                                // do nothing
        } else {
            mcp23017_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);
            if (mcp23017_status) goto out;
            mcp23017_status = i2c_write(GPIOB, I2C_TIMEOUT);
            if (mcp23017_status) goto out;
            // Select the desired row by writing a byte for the entire GPIOB bus where only the bit representing the row we want to select is a zero (write instruction) and every other bit is a one.
            // Note that the row - MATRIX_ROWS_PER_SIDE reflects the fact that being on the right hand, the columns are numbered from MATRIX_ROWS_PER_SIDE to MATRIX_ROWS, but the pins we want to write to are indexed from zero up on the GPIOB bus.
            mcp23017_status = i2c_write(0xFF & ~(1 << (row - MATRIX_ROWS_PER_SIDE)), I2C_TIMEOUT);

            if (mcp23017_status) goto out;
        out:
            i2c_stop();
        }
    }
}
