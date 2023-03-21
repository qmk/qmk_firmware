// Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
// Copyright 2017 Erin Call <hello@erincall.com>
// Copyright 2023 @frobiac
// SPDX-License-Identifier: GPL-2.0-or-later

// This implements a matrix scan (lite) for the BlackBowl keyboard.
// Each side has a dedicated MCP23018 I2C expander.

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "blackbowl.h"
#include "i2c_master.h"
#include "timer.h"

#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define ROW_SHIFTER ((matrix_row_t)1)

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col);

static uint8_t expander_reset_loop;
uint8_t        expander_status;
const uint8_t  expander_input_mask = ((1 << MATRIX_ROWS_PER_SIDE) - 1); // No special mapping, 5 bits [0..4] per side
bool           i2c_initialized     = false;

static const uint8_t I2C_ADDR_RIGHT = 0x4E;
static const uint8_t I2C_ADDR_LEFT  = 0x46;
static const uint8_t i2c_addr[]     = {I2C_ADDR_RIGHT, I2C_ADDR_LEFT};

void matrix_init_custom(void) {
    if (!i2c_initialized) {
        i2c_init();
        wait_ms(1000);
    }

    // Pin direction and pull-up depends on diode direction and column register:
    // ROW2COL, GPIOA => input, output
    uint8_t direction[2] = {0, expander_input_mask};
    uint8_t pullup[2]    = {0, expander_input_mask};

    for (uint8_t i = 0; i < 2; ++i) {
        expander_status = i2c_writeReg(i2c_addr[i], IODIRA, direction, 2, I2C_TIMEOUT);
        if (expander_status) return;

        expander_status = i2c_writeReg(i2c_addr[i], GPPUA, pullup, 2, I2C_TIMEOUT);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    if (expander_status) { // if there was an error
        ++expander_reset_loop;
        if (++expander_reset_loop == 0) {
            // since expander_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            matrix_init_custom();
        }
    }

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        matrix_has_changed |= read_rows_on_col(current_matrix, current_col);
    }

    return matrix_has_changed;
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool    matrix_changed = false;
    uint8_t port           = 0xFF & ~(1 << current_col);
    uint8_t column_state[] = {0, 0};

    // On both expanders: select col and read rows
    for (size_t i = 0; i < 2; ++i) {
        if (!expander_status) {
            expander_status = i2c_writeReg(i2c_addr[i], EXPANDER_COL_REGISTER, &port, 1, I2C_TIMEOUT);
        }
        wait_us(30);

        if (expander_status) {
            return false;
        }

        expander_status = i2c_readReg(i2c_addr[i], EXPANDER_ROW_REGISTER, &column_state[i], 1, I2C_TIMEOUT);
        column_state[i] = (~column_state[i]) & ((1 << MATRIX_ROWS_PER_SIDE) - 1);
    }

    // now map rows 0..4 on each side to cumulative to 0..9
    uint16_t col_state = column_state[0] | ((column_state[1] << MATRIX_ROWS_PER_SIDE) /*& 0x3e0*/);

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[current_row];

        if (col_state & (1 << current_row)) {
            // key closed; set state bit in matrix
            current_matrix[current_row] |= (ROW_SHIFTER << current_col);
        } else {
            // key open; clear state bit in matrix
            current_matrix[current_row] &= ~(ROW_SHIFTER << current_col);
        }

        // Determine whether the matrix changed state
        if ((last_row_value != current_matrix[current_row]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }
    return matrix_changed;
}
