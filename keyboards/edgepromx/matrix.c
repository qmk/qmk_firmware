/*
Copyright 2023 Jernej Turnsek <jernej.turnsek@gmail.com>

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


#include QMK_KEYBOARD_H
#include "i2c_master.h"

extern i2c_status_t mcp23017_status;

#define I2C_WRITE   0x00
#define I2C_READ    0x01

// For a better understanding of the i2c protocol, this is a good read:
// https://www.robot-electronics.co.uk/i2c-tutorial

// I2C address:
// See the datasheet, section 3.3.1 on addressing I2C devices and figure 3-6 for an
// illustration
// http://ww1.microchip.com/downloads/en/devicedoc/20001952c.pdf
// All address pins of the mcp23017 are connected to the ground on the ferris
// | 0  | 1  | 0  | 0  | A2 | A1 | A0 |
// | 0  | 1  | 0  | 0  | 0  | 0  | 0  |
#define I2C_ADDR 0b0100000
#define I2C_ADDR_WRITE ((I2C_ADDR << 1) | I2C_WRITE)
#define I2C_ADDR_READ ((I2C_ADDR << 1) | I2C_READ)

// Register addresses
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C  // GPIO pull-up resistor register
#define GPPUB 0x0D
#define GPIOA 0x12  // general purpose i/o port register (write modifies OLAT)
#define GPIOB 0x13
#define OLATA 0x14  // output latch register
#define OLATB 0x15

bool         i2c_initialized = 0;
i2c_status_t mcp23017_status = I2C_ADDR;

uint8_t init_mcp23017(void) {
    print("starting init");
    mcp23017_status = I2C_ADDR;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();
        i2c_initialized = true;
        wait_ms(I2C_TIMEOUT);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    uint8_t buf[]   = {IODIRA, 0b00000000, 0b11111111};
    mcp23017_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);
    if (!mcp23017_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        uint8_t pullup_buf[] = {GPPUA, 0b00000000, 0b11111111};
        mcp23017_status      = i2c_transmit(I2C_ADDR_WRITE, pullup_buf, sizeof(pullup_buf), I2C_TIMEOUT);
    }
    return mcp23017_status;
}

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];  // debounced values

static matrix_row_t read_cols(uint8_t row);
static void         init_cols(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

static uint8_t mcp23017_reset_loop;

void matrix_init_custom(void) {
    // initialize row and col

    mcp23017_status = init_mcp23017();

    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
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
static inline bool store_matrix_row(matrix_row_t current_matrix[], uint8_t index) {
    matrix_row_t temp = read_cols(index);
    if (current_matrix[index] != temp) {
        current_matrix[index] = temp;
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (mcp23017_status) {  // if there was an error
        if (++mcp23017_reset_loop == 0) {
            // if (++mcp23017_reset_loop >= 1300) {
            // since mcp23017_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            dprint("trying to reset mcp23017\n");
            mcp23017_status = init_mcp23017();
            if (mcp23017_status) {
                dprint("right side not responding\n");
            } else {
                dprint("right side attached\n");
            }
        }
    }

    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);

        // we don't need a 30us delay anymore, because selecting a
        // left-hand row requires more than 30us for i2c.

        changed |= store_matrix_row(current_matrix, i);

        unselect_rows();
    }

    return changed;
}

static void init_cols(void) {
    // init on mcp23017
    // not needed, already done as part of init_mcp23017()
}

static matrix_row_t read_cols(uint8_t row) {
    if (mcp23017_status) {  // if there was an error
        return 0;
    } else {
        uint8_t buf[]   = {GPIOB};
        mcp23017_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);
        // We read all the pins on GPIOB.
        // The initial state was all ones and any depressed key at a given column for the currently selected row will have its bit flipped to zero.
        // The return value is a row as represented in the generic matrix code were the rightmost bits represent the lower columns and zeroes represent non-depressed keys while ones represent depressed keys.
        // Since the pins connected to eact columns are sequential, and counting from zero up (col 5 -> GPIOB0, col 6 -> GPIOB1 and so on), the only transformation needed is a bitwise not to swap all zeroes and ones.
        uint8_t data[] = {0};
        if (!mcp23017_status) {
            mcp23017_status = i2c_receive(I2C_ADDR_READ, data, sizeof(data), I2C_TIMEOUT);
            data[0]         = ~(data[0]);
        }
        return data[0];
    }
}

static void unselect_rows(void) {
    // no need to unselect on mcp23017, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction
}

static void select_row(uint8_t row) {
    // select on mcp23017
    if (mcp23017_status) {  // if there was an error
                            // do nothing
    } else {
        // Select the desired row by writing a byte for the entire GPIOA bus where only the bit representing the row we want to select is a zero (write instruction) and every other bit is a one.
        uint8_t buf[]   = {GPIOA, 0xFF & ~(1 << row)};
        mcp23017_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);
    }
}
