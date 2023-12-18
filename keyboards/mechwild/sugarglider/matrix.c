// Copyright 2023 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "mcp23018.h"
#include "wait.h"
#include "debug.h"
#include "encoder.h"

#define I2C_ADDR 0x20
#define ROW_POS { 0b01000000, 0b10000000, 0b01000000, 0b10000000, 0b00000100, 0b00010000, 0b00100000, 0b00000010, 0b00001000 }

static uint8_t mcp23018_errors = 0;

static void mcp23018_init_cols(void) {
    mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, ALL_INPUT);
    mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, ALL_INPUT);
}

static void mcp23018_scan(void) {
    if (!mcp23018_errors) {
        return;
    }

    static uint16_t mcp23018_reset_loop = 0;
    if (++mcp23018_reset_loop > 0x1FFF) {
        // tuned to about 5s given the current scan rate
        dprintf("trying to reset mcp23018\n");
        mcp23018_reset_loop = 0;
        mcp23018_errors     = 0;
        mcp23018_init_cols();
    }
}

static matrix_row_t read_cols(void) {
    if (mcp23018_errors) {
        return 0;
    }

    uint8_t ret = 0xFF;                                                         // sets all to 1
    mcp23018_errors += !mcp23018_readPins(I2C_ADDR, mcp23018_PORTB, &ret);      // will update with values 0 = pulled down by connection, 1 = pulled up by pullup resistors

    return (~ret) & 0b00111111; // Clears out the two row bits in the B buffer.
}

static void select_row(uint8_t row) {
    uint8_t row_pos[MATRIX_ROWS] = ROW_POS;
    if (mcp23018_errors) {
        // wait to mimic i2c interactions
        //wait_us(100);
        return;
    }
    
    if (row > 1) {
        mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, ALL_INPUT);
        mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, ~(row_pos[row]));
    } else {
        mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, ALL_INPUT);
        mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, ~(row_pos[row]));
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selection to stabilize
    select_row(current_row);
    // Skip the wait_us(30); as i2c is slow enough to debounce the io changes

    current_matrix[current_row] = read_cols();

    return (last_row_value != current_matrix[current_row]);
}

void matrix_init_custom(void) {
    mcp23018_init(I2C_ADDR);
    mcp23018_init_cols();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    mcp23018_scan();

    bool changed = false;
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
#ifdef ENCODER_ENABLE
        encoder_read();
#endif
    }
    return changed;
}
