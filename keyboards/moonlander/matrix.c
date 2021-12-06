/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "moonlander.h"
#include "i2c_master.h"

/*
#define MATRIX_ROW_PINS { B10, B11, B12, B13, B14, B15 } outputs
#define MATRIX_COL_PINS { A0, A1, A2, A3, A6, A7, B0 }   inputs
 */
/* matrix state(1:on, 0:off) */
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t raw_matrix_right[MATRIX_COLS];

#define ROWS_PER_HAND (MATRIX_ROWS / 2)
#ifndef MOONLANDER_I2C_TIMEOUT
#    define MOONLANDER_I2C_TIMEOUT 100
#endif

extern bool mcp23018_leds[3];
extern bool is_launching;

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

    if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, MOONLANDER_I2C_TIMEOUT)) {
        dprintf("error hori\n");
    } else {
        mcp23018_tx[0] = 0x0C;        // GPPUA
        mcp23018_tx[1] = 0b10000000;  // A is not pulled-up
        mcp23018_tx[2] = 0b11111111;  // B is pulled-up

        if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, MOONLANDER_I2C_TIMEOUT)) {
            dprintf("error hori\n");
        } else {
            mcp23018_initd = is_launching = true;
        }
    }
}

void matrix_init_custom(void) {
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

    mcp23018_init();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Try to re-init right side
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

    matrix_row_t data = 0;
    // actual matrix
    for (uint8_t row = 0; row <= ROWS_PER_HAND; row++) {
        // strobe row
        switch (row) {
            case 0: writePinHigh(B10); break;
            case 1: writePinHigh(B11); break;
            case 2: writePinHigh(B12); break;
            case 3: writePinHigh(B13); break;
            case 4: writePinHigh(B14); break;
            case 5: writePinHigh(B15); break;
            case 6: break; // Left hand has 6 rows
        }

        // right side
        if (mcp23018_initd) {
            // #define MCP23_ROW_PINS { GPB5, GBP4, GBP3, GBP2, GBP1, GBP0 }       outputs
            // #define MCP23_COL_PINS { GPA0, GBA1, GBA2, GBA3, GBA4, GBA5, GBA6 } inputs

            // select row
            mcp23018_tx[0] = 0x12;                                                                   // GPIOA
            mcp23018_tx[1] = (0b01111111 & ~(1 << (row))) | ((uint8_t)!mcp23018_leds[2] << 7);       // activate row
            mcp23018_tx[2] = ((uint8_t)!mcp23018_leds[1] << 6) | ((uint8_t)!mcp23018_leds[0] << 7);  // activate row

            if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, MOONLANDER_I2C_TIMEOUT)) {
                dprintf("error hori\n");
                mcp23018_initd = false;
            }

            // read col

            mcp23018_tx[0] = 0x13;  // GPIOB
            if (MSG_OK != i2c_readReg(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx[0], &mcp23018_rx[0], 1, MOONLANDER_I2C_TIMEOUT)) {
                dprintf("error vert\n");
                mcp23018_initd = false;
            }

            data = ~(mcp23018_rx[0] & 0b00111111);
            // data = 0x01;
        } else {
            data = 0;
        }

        if (raw_matrix_right[row] != data) {
            raw_matrix_right[row] = data;
            changed         = true;
        }


        // left side
        if (row < ROWS_PER_HAND) {
            // i2c comm incur enough wait time
            if (!mcp23018_initd) {
                // need wait to settle pin state
                matrix_io_delay();
            }
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
                case 6: break;
            }

            if (current_matrix[row] != data) {
                current_matrix[row]    = data;
                changed                = true;
            }
        }
    }
    for (uint8_t row = 0; row < ROWS_PER_HAND; row++) {
        current_matrix[11 - row] = 0;
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            current_matrix[11 - row] |= ((raw_matrix_right[6 - col] & (1 << row) ? 1 : 0) << col);
        }
    }
    return changed;
}

// DO NOT REMOVE
// Needed for proper wake/sleep
void matrix_power_up(void) {
    bool temp_launching = is_launching;

    matrix_init_custom();

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
