/* Copyright 2020 zvecr<git@zvecr.com>
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
#include "mcp23018.h"
#include "quantum.h"

// Optimize scanning code for speed as a slight mitigation for the port expander
#pragma GCC push_options
#pragma GCC optimize("-O3")

#define I2C_ADDR 0x20

static uint16_t mcp23018_reset_loop = 0;
static uint8_t  mcp23018_errors     = 0;

static const pin_t row_pins[MATRIX_ROWS / 2] = {B1, D5, D4, D6, D7, B4};
static const pin_t col_pins[MATRIX_COLS]     = {F5, F6, F7, C7, C6, B6, B5, D3, D2, B3, B2};

//_____REGULAR funcs____________________________________________________________

static void select_row(uint8_t row) {
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row) { setPinInputHigh(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS / 2; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    matrix_row_t current_row_value = 0;

    // Select row and wait for row selection to stabilize
    select_row(current_row);
    wait_us(5);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    if (last_row_value == current_row_value) {
        return false;
    }

    current_matrix[current_row] = current_row_value;
    return true;
}

//_____MCP23018 funcs___________________________________________________________

static void init_pins_MCP23018(void) {
    mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, 0b11111111);
    mcp23018_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, 0b01100000);
}

static void select_row_MCP23018(uint8_t row) {
    uint8_t mask = 0;

    switch (row) {
        case 6:
            mask = 0b10000000;
            break;
        case 7:
            mask = 0b00000001;
            break;
        case 8:
            mask = 0b00000010;
            break;
        case 9:
            mask = 0b00000100;
            break;
        case 10:
            mask = 0b00001000;
            break;
        case 11:
            mask = 0b00010000;
            break;
    }

    mcp23018_errors += !mcp23018_set_output(I2C_ADDR, mcp23018_PORTB, ~mask);
}

static uint16_t read_cols_MCP23018(void) {
    uint16_t tmp = 0xFFFF;
    mcp23018_errors += !mcp23018_read_pins_all(I2C_ADDR, &tmp);

    uint16_t state = ((tmp & 0b11111111) << 2) | ((tmp & 0b0110000000000000) >> 13);
    return (~state) & 0b1111111111;
}

static bool read_cols_on_row_MCP23018(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // No need to Clear data in matrix row as we just replace in one go

    // Select row and wait for row selection to stabilize
    select_row_MCP23018(current_row);

    matrix_row_t current_row_value = read_cols_MCP23018();

    // No need to Unselect row as the next `select_row` will blank everything

    if (last_row_value == current_row_value) {
        return false;
    }

    current_matrix[current_row] = current_row_value;
    return true;
}

//_____CUSTOM MATRIX IMPLEMENTATION____________________________________________________

void matrix_init_custom(void) {
    mcp23018_init(I2C_ADDR);

    init_pins();
    init_pins_MCP23018();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS / 2; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }

    if (mcp23018_errors) {
        if (++mcp23018_reset_loop > 0x7FFF) {
            // tuned to about 5s given the current scan rate
            print("trying to reset mcp23018\n");
            mcp23018_reset_loop = 0;
            mcp23018_errors     = 0;
            init_pins_MCP23018();
        }
        return changed;
    }

    for (uint8_t current_row = MATRIX_ROWS / 2; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row_MCP23018(current_matrix, current_row);
    }
    return changed;
}
#pragma GCC pop_options
