/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
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



#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <hal.h>
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"
#include "action.h"
#include "keycode.h"
#include <string.h>
#include "moonlander.h"
#include "i2c_master.h"
#include "debounce.h"

/*
#define MATRIX_ROW_PINS { B10, B11, B12, B13, B14, B15 } outputs
#define MATRIX_COL_PINS { A0, A1, A2, A3, A6, A7, B0 }   inputs
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static matrix_row_t matrix_debouncing_right[MATRIX_COLS];
static bool         debouncing            = false;
static uint16_t     debouncing_time       = 0;
static bool         debouncing_right      = false;
static uint16_t     debouncing_time_right = 0;

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 20
#endif

extern bool mcp23018_leds[3];
extern bool is_launching;

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_io_delay(void) { wait_us(MATRIX_IO_DELAY); }

bool           mcp23018_initd = false;
static uint8_t mcp23018_reset_loop;

uint8_t mcp23018_tx[3];
uint8_t mcp23018_rx[1];

void mcp23018_init(void) {
    i2c_init();

    // #define MCP23_ROW_PINS { GPB5, GBP4, GBP3, GBP2, GBP1, GBP0 }       outputs
    // #define MCP23_COL_PINS { GPA0, GBA1, GBA2, GBA3, GBA4, GBA5, GBA6 } inputs

    mcp23018_tx[0] = 0x00;        // IODIRA
    mcp23018_tx[1] = 0b00000000;  // A is output
    mcp23018_tx[2] = 0b00111111;  // B is inputs

    if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, I2C_TIMEOUT)) {
        dprintf("error hori\n");
    } else {
        mcp23018_tx[0] = 0x0C;        // GPPUA
        mcp23018_tx[1] = 0b10000000;  // A is not pulled-up
        mcp23018_tx[2] = 0b11111111;  // B is pulled-up

        if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, I2C_TIMEOUT)) {
            dprintf("error hori\n");
        } else {
            mcp23018_initd = is_launching = true;
        }
    }
}

void matrix_init(void) {
    dprintf("matrix init\n");
    // debug_matrix = true;

    // outputs
    setPinOutput(B10);
    setPinOutput(B11);
    setPinOutput(B12);
    setPinOutput(B13);
    setPinOutput(B14);
    setPinOutput(B15);

    // inputs
    setPinInputLow(A0);
    setPinInputLow(A1);
    setPinInputLow(A2);
    setPinInputLow(A3);
    setPinInputLow(A6);
    setPinInputLow(A7);
    setPinInputLow(B0);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing_right, 0, MATRIX_COLS * sizeof(matrix_row_t));

    mcp23018_init();

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    bool changed = false;

    matrix_row_t data = 0;
    // actual matrix
    for (uint8_t row = 0; row < ROWS_PER_HAND; row++) {
        // strobe row
        switch (row) {
            case 0: writePinHigh(B10); break;
            case 1: writePinHigh(B11); break;
            case 2: writePinHigh(B12); break;
            case 3: writePinHigh(B13); break;
            case 4: writePinHigh(B14); break;
            case 5: writePinHigh(B15); break;
        }

        // need wait to settle pin state
        matrix_io_delay();

        // read col data
        data = (
            (readPin(A0) << 0 ) |
            (readPin(A1) << 1 ) |
            (readPin(A2) << 2 ) |
            (readPin(A3) << 3 ) |
            (readPin(A6) << 4 ) |
            (readPin(A7) << 5 ) |
            (readPin(B0) << 6 )
        );

        // unstrobe  row
        switch (row) {
            case 0: writePinLow(B10); break;
            case 1: writePinLow(B11); break;
            case 2: writePinLow(B12); break;
            case 3: writePinLow(B13); break;
            case 4: writePinLow(B14); break;
            case 5: writePinLow(B15); break;
        }

        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing             = true;
            debouncing_time        = timer_read();
            changed                = true;
        }
    }

    for (uint8_t row = 0; row <= ROWS_PER_HAND; row++) {
        // right side

        if (!mcp23018_initd) {
            if (++mcp23018_reset_loop == 0) {
                // if (++mcp23018_reset_loop >= 1300) {
                // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
                // this will be approx bit more frequent than once per second
                print("trying to reset mcp23018\n");
                mcp23018_init();
                if (!mcp23018_initd) {
                    print("left side not responding\n");
                } else {
                    print("left side attached\n");
#ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_init();
#endif
                }
            }
        }

        // #define MCP23_ROW_PINS { GPB5, GBP4, GBP3, GBP2, GBP1, GBP0 }       outputs
        // #define MCP23_COL_PINS { GPA0, GBA1, GBA2, GBA3, GBA4, GBA5, GBA6 } inputs

        // select row

        mcp23018_tx[0] = 0x12;                                                                   // GPIOA
        mcp23018_tx[1] = (0b01111111 & ~(1 << (row))) | ((uint8_t)!mcp23018_leds[2] << 7);       // activate row
        mcp23018_tx[2] = ((uint8_t)!mcp23018_leds[1] << 6) | ((uint8_t)!mcp23018_leds[0] << 7);  // activate row

        if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, I2C_TIMEOUT)) {
            dprintf("error hori\n");
            mcp23018_initd = false;
        }

        // read col

        mcp23018_tx[0] = 0x13;  // GPIOB
        if (MSG_OK != i2c_readReg(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx[0], &mcp23018_rx[0], 1, I2C_TIMEOUT)) {
            dprintf("error vert\n");
            mcp23018_initd = false;
        }

        data = ~(mcp23018_rx[0] & 0b00111111);
        // data = 0x01;

        if (matrix_debouncing_right[row] != data) {
            matrix_debouncing_right[row] = data;
            debouncing_right             = true;
            debouncing_time_right        = timer_read();
            changed                      = true;
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < ROWS_PER_HAND; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }

    if (debouncing_right && timer_elapsed(debouncing_time_right) > DEBOUNCE && mcp23018_initd) {
        for (int row = 0; row < ROWS_PER_HAND; row++) {
            matrix[11 - row] = 0;
            for (int col = 0; col < MATRIX_COLS; col++) {
                matrix[11 - row] |= ((matrix_debouncing_right[6 - col] & (1 << row) ? 1 : 0) << col);
            }
        }
        debouncing_right = false;
    }

    matrix_scan_quantum();

    return (uint8_t)changed;
}

bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & (1 << col)); }

matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
    dprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        dprintf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1 << col))
                dprintf("1");
            else
                dprintf("0");
        }
        dprintf("\n");
    }
}

// DO NOT REMOVE
// Needed for proper wake/sleep
void matrix_power_up(void) {
    bool temp_launching = is_launching;
    // outputs
    setPinOutput(B10);
    setPinOutput(B11);
    setPinOutput(B12);
    setPinOutput(B13);
    setPinOutput(B14);
    setPinOutput(B15);

    // inputs
    setPinInputLow(A0);
    setPinInputLow(A1);
    setPinInputLow(A2);
    setPinInputLow(A3);
    setPinInputLow(A6);
    setPinInputLow(A7);
    setPinInputLow(B0);

    mcp23018_init();
    is_launching = temp_launching;
    if (!is_launching) {
        ML_LED_1(false);
        ML_LED_2(false);
        ML_LED_3(false);
        ML_LED_4(false);
        ML_LED_5(false);
        ML_LED_6(false);
    }

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }

}
