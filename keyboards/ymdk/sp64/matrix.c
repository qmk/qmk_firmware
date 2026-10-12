/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
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
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "sp64.h"
#include "debounce.h"

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

// Debouncing: store for each key the number of scans until it's eligible to
// change.  When scanning the matrix, ignore any changes in keys that have
// already changed in the last DEBOUNCE scans.
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static void matrix_select_row(uint8_t row);

#ifdef RIGHT_HALF
static uint8_t mcp23018_reset_loop = 0;
#endif

// user-defined overridable functions

__attribute__((weak)) void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__((weak)) void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

// helper functions
void matrix_init(void) {
    // all outputs for rows high
    DDRB  = 0xFF;
    PORTB = 0xFF;
    // all inputs for columns
    DDRA = 0x00;
    DDRC &= ~(0x111111 << 2);
    DDRD &= ~(1 << PIND7);
    // all columns are pulled-up
    PORTA = 0xFF;
    PORTC |= (0b111111 << 2);
    PORTD |= (1 << PIND7);

#ifdef RIGHT_HALF
    // initialize row and col
    mcp23018_status = init_mcp23018();
#endif

    // initialize matrix state: all keys off
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix[row]            = 0;
        matrix_debouncing[row] = 0;
    }
    debounce_init();
    matrix_init_kb();
}

uint8_t matrix_scan(void) {
#ifdef RIGHT_HALF
    // Then the keyboard
    if (mcp23018_status != I2C_STATUS_SUCCESS) {
        if (++mcp23018_reset_loop == 0) {
            // if (++mcp23018_reset_loop >= 1300) {
            // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
            }
        }
    }
#endif
    bool changed = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t cols;

        matrix_select_row(row);
#ifndef RIGHT_HALF
        _delay_us(5);
#endif

        cols = (
            // cols 0..7, PORTA 0 -> 7
            (~PINA) & 0xFF);

#ifdef RIGHT_HALF
        uint8_t data = 0x7F;
        // Receive the columns from right half
        i2c_receive(I2C_ADDR, &data, 1, MCP23018_I2C_TIMEOUT);
        cols |= ((~(data) & 0x7F) << 7);
#endif

        if (matrix_debouncing[row] != cols) {
            matrix_debouncing[row] = cols;
            // debouncing = DEBOUNCE;
            changed = true;
        }
    }

    debounce(matrix_debouncing, matrix, changed);

    matrix_scan_kb();

#ifdef DEBUG_MATRIX
    for (uint8_t c = 0; c < MATRIX_COLS; c++)
        for (uint8_t r = 0; r < MATRIX_ROWS; r++)
            if (matrix_is_on(r, c)) xprintf("r:%d c:%d \n", r, c);
#endif

    return (uint8_t)changed;
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

static void matrix_select_row(uint8_t row) {
#ifdef RIGHT_HALF
    uint8_t txdata[3];

    // Set the remote row on port A
    txdata[0]       = GPIOA;
    txdata[1]       = 0xFF & ~(1 << row);
    mcp23018_status = i2c_transmit(I2C_ADDR, (uint8_t *)txdata, 2, MCP23018_I2C_TIMEOUT);
#endif

    // select other half
    DDRB  = (1 << row);
    PORTB = ~(1 << row);
}
