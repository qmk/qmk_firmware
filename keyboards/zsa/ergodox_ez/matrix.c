/*

Note for ErgoDox EZ customizers: Here be dragons!
This is not a file you want to be messing with.
All of the interesting stuff for you is under keymaps/ :)
Love, Erez

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

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
#include "ergodox_ez.h"
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "i2c_master.h"
#include "gpio.h"
#include "atomic_util.h"

/*
 * This constant define not debouncing time in msecs, assuming eager_pr.
 *
 * On Ergodox matrix scan rate is relatively low, because of slow I2C.
 * Now it's only 317 scans/second, or about 3.15 msec/scan.
 * According to Cherry specs, debouncing time is 5 msec.
 *
 * However, some switches seem to have higher debouncing requirements, or
 * something else might be wrong. (Also, the scan speed has improved since
 * that comment was written.)
 */

/* matrix state(1:on, 0:off) */
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static const pin_t onboard_row_pins[MATRIX_ROWS] = MATRIX_ONBOARD_ROW_PINS;
static const pin_t onboard_col_pins[MATRIX_COLS] = MATRIX_ONBOARD_COL_PINS;
static const bool row_expanded[MATRIX_ROWS] = ROWS_EXPANDED;

static void         init_cols(void);
static matrix_row_t read_cols(uint8_t row);
static void         unselect_rows(void);
static void         select_row(uint8_t row);
static void         unselect_row(uint8_t row);

static uint8_t mcp23018_reset_loop;
i2c_status_t mcp23018_status = 0x20;
static bool i2c_initialized = false;

#ifdef RGBLIGHT_ENABLE
extern bool i2c_rgblight;
#endif

#define MCP23018_IODIRA          0x00            // i/o direction register
#define MCP23018_IODIRB          0x01
#define MCP23018_GPPUA           0x0C            // GPIO pull-up resistor register
#define MCP23018_GPPUB           0x0D
#define MCP23018_GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define MCP23018_GPIOB           0x13
#define MCP23018_OLATA           0x14            // output latch register
#define MCP23018_OLATB           0x15


uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    if (!i2c_initialized) {
        i2c_init(); // on pins D(1,0)
        i2c_initialized = true;
        wait_ms(1000);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    uint8_t buf[]   = {0b00000000, 0b00111111};
    mcp23018_status = i2c_writeReg(MCP23018_EXPANDER_I2C_ADDR, MCP23018_IODIRA, buf, sizeof(buf), ERGODOX_EZ_I2C_TIMEOUT);

    if (!mcp23018_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        mcp23018_status = i2c_writeReg(MCP23018_EXPANDER_I2C_ADDR, MCP23018_GPPUA, buf, sizeof(buf), ERGODOX_EZ_I2C_TIMEOUT);
    }

    return mcp23018_status;
}

void matrix_init_custom(void) {
    // initialize row and col

    mcp23018_status = init_mcp23018();

    unselect_rows();
    init_cols();
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_row(uint8_t index) {
    matrix_row_t temp = 0x3F & read_cols(index);
    if (raw_matrix[index] != temp) {
        raw_matrix[index] = temp;
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (mcp23018_status) {  // if there was an error
        if (++mcp23018_reset_loop == 0) {
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
                wait_ms(200);
                mcu_reset();
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

        changed |= store_raw_matrix_row(left_index);
        changed |= store_raw_matrix_row(right_index);

        unselect_rows();
    }

    return changed;
}

static void init_cols(void) {
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        ATOMIC_BLOCK_FORCEON {
            setPinInputHigh(onboard_col_pins[x]);
        }
    }
}

static matrix_row_t read_cols(uint8_t row) {
    if (row < MATRIX_ROWS_PER_SIDE) {
        if (mcp23018_status) {  // if there was an error
            return 0;
        } else {
            uint8_t data = 0;
            // reading GPIOB (column port) since in mcp23018's sequential mode
            // it is addressed directly after writing to GPIOA in select_row()
            mcp23018_status = i2c_readReg(MCP23018_EXPANDER_I2C_ADDR, EXPANDER_COL_REGISTER, &data, 1, ERGODOX_EZ_I2C_TIMEOUT);
            return ~data;
        }
    } else {
        select_row(row);
        matrix_row_t current_row_value                         = 0;
        for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
            // Select the col pin to read (active low)
            uint8_t pin_state = readPin(onboard_col_pins[col_index]);

            // Populate the matrix row with the state of the col pin
            current_row_value |= pin_state ? 0 : ((matrix_row_t)1 << col_index);
        }
        unselect_row(row);
        return current_row_value;
    }
}

/* Row pin configuration
 *
 * Teensy
 * row: 7   8   9   10  11  12  13
 * pin: B0  B1  B2  B3  D2  D3  C6
 *
 * MCP23018
 * row: 0   1   2   3   4   5   6
 * pin: A0  A1  A2  A3  A4  A5  A6
 */
static void unselect_rows(void) {
    // no need to unselect on mcp23018, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction

    for (uint8_t row_index = MATRIX_ROWS_PER_SIDE; row_index < MATRIX_ROWS; row_index++) {
        if (!row_expanded[row_index]) {
            unselect_row(row_index);
        }
    }
}

static void unselect_row(uint8_t row) {
    if (!row_expanded[row]) {
        ATOMIC_BLOCK_FORCEON {
            setPinInputHigh(onboard_row_pins[row]);
        }
    }
}

static void select_row(uint8_t row) {
    if (row < 7) {
        // select on mcp23018
        if (!mcp23018_status) {
            // set active row low  : 0
            // set other rows hi-Z : 1
            uint8_t data;
            data = 0xFF & ~(1 << row);
            mcp23018_status = i2c_writeReg(MCP23018_EXPANDER_I2C_ADDR, EXPANDER_ROW_REGISTER, &data, 1, ERGODOX_EZ_I2C_TIMEOUT);
        }
    } else {
        // select on teensy
        // Output low(DDR:1, PORT:0) to select
        if (!row_expanded[row]) {
            ATOMIC_BLOCK_FORCEON {
                setPinOutput(onboard_row_pins[row]);
                writePinLow(onboard_row_pins[row]);
            }
        }
    }
}

// DO NOT REMOVE
// Needed for proper wake/sleep
void matrix_power_up(void) {
    matrix_init_custom();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }

}
