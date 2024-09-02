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
#include "mcp23018.h"

#pragma GCC push_options
#pragma GCC optimize("-O3")
/*
#define MATRIX_ROW_PINS { B10, B11, B12, B13, B14, B15 } outputs
#define MATRIX_COL_PINS { A0, A1, A2, A3, A6, A7, B0 }   inputs
#define MCP23_ROW_PINS { GPB5, GBP4, GBP3, GBP2, GBP1, GBP0 }       outputs
#define MCP23_COL_PINS { GPA0, GBA1, GBA2, GBA3, GBA4, GBA5, GBA6 } inputs

 */
/* matrix state(1:on, 0:off) */
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values
extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
static matrix_row_t raw_matrix_right[MATRIX_ROWS];

#define MCP_ROWS_PER_HAND (MATRIX_ROWS / 2)

extern bool mcp23018_leds[3];
extern bool is_launching;

static uint16_t mcp23018_reset_loop;
uint8_t         mcp23018_errors;

bool io_expander_ready(void) {
    uint8_t tx;
    return mcp23018_read_pins(MCP23018_DEFAULT_ADDRESS, mcp23018_PORTA, &tx);
}

void matrix_init_custom(void) {
    // outputs
    gpio_set_pin_output(B10);
    gpio_set_pin_output(B11);
    gpio_set_pin_output(B12);
    gpio_set_pin_output(B13);
    gpio_set_pin_output(B14);
    gpio_set_pin_output(B15);

    // inputs
    gpio_set_pin_input_low(A0);
    gpio_set_pin_input_low(A1);
    gpio_set_pin_input_low(A2);
    gpio_set_pin_input_low(A3);
    gpio_set_pin_input_low(A6);
    gpio_set_pin_input_low(A7);
    gpio_set_pin_input_low(B0);

    mcp23018_init(MCP23018_DEFAULT_ADDRESS);
    mcp23018_errors += !mcp23018_set_config(MCP23018_DEFAULT_ADDRESS, mcp23018_PORTA, 0b00000000);
    mcp23018_errors += !mcp23018_set_config(MCP23018_DEFAULT_ADDRESS, mcp23018_PORTB, 0b00111111);

    if (!mcp23018_errors) {
        is_launching = true;
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    // Attempt to reset the mcp23018 if it's not initialized
    if (mcp23018_errors) {
        if (++mcp23018_reset_loop > 0x1FFF) {
            if (io_expander_ready()) {
                // If we managed to initialize the mcp23018 - we need to reinitialize the matrix / layer state. During an electric discharge the i2c peripherals might be in a weird state. Giving a delay and resetting the MCU allows to recover from this.
                wait_ms(200);
                mcu_reset();
            }
        }
    }

    matrix_row_t data = 0;
    // actual matrix
    for (uint8_t row = 0; row <= MCP_ROWS_PER_HAND; row++) {
        // strobe row
        switch (row) {
            case 0:
                gpio_write_pin_high(B10);
                break;
            case 1:
                gpio_write_pin_high(B11);
                break;
            case 2:
                gpio_write_pin_high(B12);
                break;
            case 3:
                gpio_write_pin_high(B13);
                break;
            case 4:
                gpio_write_pin_high(B14);
                break;
            case 5:
                gpio_write_pin_high(B15);
                break;
            case 6:
                break; // Left hand has 6 rows
        }

        // Selecting the row on the right side of the keyboard.
        if (!mcp23018_errors) {
            // select row
            mcp23018_errors += !mcp23018_set_output_all(MCP23018_DEFAULT_ADDRESS, (0b01111111 & ~(1 << (row))) | ((uint8_t)!mcp23018_leds[2] << 7), ((uint8_t)!mcp23018_leds[1] << 6) | ((uint8_t)!mcp23018_leds[0] << 7));
        }

        // Reading the left side of the keyboard.
        if (row < MCP_ROWS_PER_HAND) {
            // i2c comm incur enough wait time
            if (mcp23018_errors) {
                // need wait to settle pin state
                matrix_io_delay();
            }
            // read col data
            data = ((readPin(A0) << 0) | (readPin(A1) << 1) | (readPin(A2) << 2) | (readPin(A3) << 3) | (readPin(A6) << 4) | (readPin(A7) << 5) | (readPin(B0) << 6));
            // unstrobe  row
            switch (row) {
                case 0:
                    gpio_write_pin_low(B10);
                    break;
                case 1:
                    gpio_write_pin_low(B11);
                    break;
                case 2:
                    gpio_write_pin_low(B12);
                    break;
                case 3:
                    gpio_write_pin_low(B13);
                    break;
                case 4:
                    gpio_write_pin_low(B14);
                    break;
                case 5:
                    gpio_write_pin_low(B15);
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
        if (!mcp23018_errors) {
            uint8_t rx;
            mcp23018_errors += !mcp23018_read_pins(MCP23018_DEFAULT_ADDRESS, mcp23018_PORTB, &rx);
            data = ~(rx & 0b00111111);
        } else {
            data = 0;
        }

        if (raw_matrix_right[row] != data) {
            raw_matrix_right[row] = data;
            changed               = true;
        }
    }

    for (uint8_t row = 0; row < MCP_ROWS_PER_HAND; row++) {
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
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

bool is_transport_connected(void) {
    return (bool)(mcp23018_errors == 0);
}
#pragma GCC pop_options
