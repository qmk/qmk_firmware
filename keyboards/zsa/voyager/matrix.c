// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "voyager.h"
#include "i2c_master.h"

extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values
extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
static matrix_row_t raw_matrix_right[MATRIX_COLS];

#define ROWS_PER_HAND (MATRIX_ROWS / 2)
#ifndef VOYAGER_I2C_TIMEOUT
#    define VOYAGER_I2C_TIMEOUT 100
#endif

extern bool mcp23018_leds[3];
extern bool is_launching;

bool mcp23018_initd = false;
static uint8_t mcp23018_reset_loop;

uint8_t mcp23018_tx[3];
uint8_t mcp23018_rx[1];

void mcp23018_init(void) {
    i2c_init();

    mcp23018_tx[0] = 0x00;       // IODIRA
    mcp23018_tx[1] = 0b00000000; // A is output
    mcp23018_tx[2] = 0b00111111; // B is inputs

    if (MSG_OK == i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, VOYAGER_I2C_TIMEOUT)) {
        mcp23018_tx[0] = 0x0C;       // GPPUA
        mcp23018_tx[1] = 0b10000000; // A is not pulled-up
        mcp23018_tx[2] = 0b11111111; // B is pulled-up
        wait_ms(5);

        if (MSG_OK == i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, VOYAGER_I2C_TIMEOUT)) {
            wait_ms(5);
            mcp23018_initd = is_launching = true;
        }
    }
}

bool io_expander_ready(void) {
    uint8_t tx[1] = {0x13};
    if (MSG_OK == i2c_readReg(MCP23018_DEFAULT_ADDRESS << 1, tx[0], &tx[0], 1, VOYAGER_I2C_TIMEOUT)) {
        return true;
    }
    return false;
}

void matrix_init_custom(void) {
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
    // Attempt to reset the mcp23018 if it's not initialized
    if (!mcp23018_initd) {
        if (++mcp23018_reset_loop == 0) {
            // Since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans. This will be approx bit more frequent than once per second.
            if (io_expander_ready()) {
                // If we managed to initialize the mcp23018 - we need to reinitialize the matrix / layer state. During an electric discharge the i2c peripherals might be in a weird state. Giving a delay and resetting the MCU allows to recover from this.
                wait_ms(200);
                mcu_reset();
            }
        }
    }

    // Scanning left and right side of the keyboard for key presses.
    // Left side is scanned by reading the gpio pins directly, right side is scanned by reading the mcp23018 registers.

    matrix_row_t data = 0;
    for (uint8_t row = 0; row <= ROWS_PER_HAND; row++) {
        // strobe row
        switch (row) {
            case 0:
                writePinHigh(B10);
                break;
            case 1:
                writePinHigh(B11);
                break;
            case 2:
                writePinHigh(B12);
                break;
            case 3:
                writePinHigh(B13);
                break;
            case 4:
                writePinHigh(B14);
                break;
            case 5:
                writePinHigh(B15);
                break;
            case 6:
                break; // Left hand has 6 rows
        }

        // Selecting the row on the right side of the keyboard.
        if (mcp23018_initd) {
            // select row
            mcp23018_tx[0] = 0x12;                                                                  // GPIOA
            mcp23018_tx[1] = (0b01111111 & ~(1 << (row))) | ((uint8_t)!mcp23018_leds[2] << 7);      // activate row
            mcp23018_tx[2] = ((uint8_t)!mcp23018_leds[1] << 6) | ((uint8_t)!mcp23018_leds[0] << 7); // activate row

            if (MSG_OK != i2c_transmit(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx, 3, VOYAGER_I2C_TIMEOUT)) {
                mcp23018_initd = false;
            }
        }
        // Reading the left side of the keyboard.
        if (row < ROWS_PER_HAND) {
            // i2c comm incur enough wait time
            if (!mcp23018_initd) {
                // need wait to settle pin state
                matrix_io_delay();
            }
            // read col data
            data = ((readPin(A0) << 0) | (readPin(A1) << 1) | (readPin(A2) << 2) | (readPin(A3) << 3) | (readPin(A6) << 4) | (readPin(A7) << 5) | (readPin(B0) << 6));
            // unstrobe  row
            switch (row) {
                case 0:
                    writePinLow(B10);
                    break;
                case 1:
                    writePinLow(B11);
                    break;
                case 2:
                    writePinLow(B12);
                    break;
                case 3:
                    writePinLow(B13);
                    break;
                case 4:
                    writePinLow(B14);
                    break;
                case 5:
                    writePinLow(B15);
                    break;
                case 6:
                    break;
            }

            if (current_matrix[row] != data) {
                current_matrix[row] = data;
                changed             = true;
            }
        }

        // Reading the right side of the keyboard.
        if (mcp23018_initd) {
            for (uint16_t i = 0; i < IO_EXPANDER_OP_DELAY; i++) {
                __asm__("nop");
            }

            mcp23018_tx[0] = 0x13; // GPIOB
            if (MSG_OK != i2c_readReg(MCP23018_DEFAULT_ADDRESS << 1, mcp23018_tx[0], &mcp23018_rx[0], 1, VOYAGER_I2C_TIMEOUT)) {
                mcp23018_initd = false;
            }
            data = ~(mcp23018_rx[0] & 0b00111111);
            for (uint16_t i = 0; i < IO_EXPANDER_OP_DELAY; i++) {
                __asm__("nop");
            }
        } else {
            data = 0;
        }

        if (raw_matrix_right[row] != data) {
            raw_matrix_right[row] = data;
            changed               = true;
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
    if (!temp_launching) {
        STATUS_LED_1(false);
        STATUS_LED_2(false);
        STATUS_LED_3(false);
        STATUS_LED_4(false);
    }

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

bool is_transport_connected(void) {
    return mcp23018_initd;
}
