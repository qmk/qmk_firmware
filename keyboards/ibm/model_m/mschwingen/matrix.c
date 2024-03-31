/*
 * Copyright 2020 Michael Schwingen

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
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "spi_master.h"
#include "print.h"
#include "mschwingen.h"

#define SPI_TIMEOUT 100

/* Keyboard Matrix Assignments */
static uint16_t row_bits[MATRIX_ROWS] = {
    0x4000, 0x8000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0100, 0x0200,
    0x0040, 0x0080, 0x0020, 0x0010, 0x0008, 0x0004, 0x0001, 0x0002};

static const pin_t col_pins[MATRIX_COLS] = {D1, D4, D7, B4, F7, F6, F5, F4};

static void select_col(uint8_t col) {
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void unselect_col(uint8_t col) { setPinInputHigh(col_pins[col]); }

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    uint16_t row_data;
    bool     matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    matrix_io_delay();

    writePinLow(SR_LOAD_PIN);
    writePinHigh(SR_LOAD_PIN);

    row_data = spi_read() << 8;
    row_data |= spi_read();

    dprintf("%02X ", ~row_data);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value    = current_matrix[row_index];
        matrix_row_t current_row_value = last_row_value;

        // Check row pin state
        if ((row_data & row_bits[row_index]) == 0) {
            // Pin LO, set col bit
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_row_value)) {
            matrix_changed            = true;
            current_matrix[row_index] = current_row_value;
        }
    }

    // Unselect col
    unselect_col(current_col);

    return matrix_changed;
}

void matrix_init_custom(void) {
    unselect_cols();

    // set 4MHz SPI clock
    SPSR = 0;
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(CPOL);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    dprint("\r\nScan: ");

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }
    update_layer_leds();
    return changed;
}
