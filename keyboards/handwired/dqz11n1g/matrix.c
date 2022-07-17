/*
  Copyright (c) 2022 David Kuehling <dvdkhlng TA posteo TOD de>

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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>

#include "spi_master.h"
#include "quantum.h"
#include "matrix.h"

static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

static void unselect_rows(void);

void matrix_init_custom(void) {
    /* initialize row pins */
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        setPinOutput(row_pins[row]);
    }
    unselect_rows();

    /* columns read via shift-register on SPI lines */

    /* Enable SPI, Master, set clock rate fck/2.  First bit already at Qh
     * output before clock edge (CPHA=0).  SN74HC165 shift register shifts
     * on low-to-high transition (CPOL=1).  Receive the LSB first (DORD=1).
     */
    bool lsbFirst = true;
    uint8_t mode = 2;  /* CPOL=1, CPHA=0 */
    uint16_t divisor = 16;

    /* According to Atmega32U4 datasheet, PB0 *must* be set to output,
     * otherwise it will interfere with SPI master operation.  On pro-micro
     * it's connected to a yellew LED. */
    pin_t slavePin = PB0;
    spi_init();
    spi_start(slavePin, lsbFirst, mode, divisor);

    /* Initialize pin controlling the shift register's SH/~LD pin */
    setPinOutput(ROW_SHIFT_PIN);
}

static void select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        writePinHigh(pin);
    }
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        writePinLow(pin);
    }
}

static void unselect_rows(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        unselect_row(row);
    }
}

bool matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    /* Start with a clear matrix row */
    matrix_row_t current_row_value = 0;

    /* Set shift register SH/~LD pin to "load" mode */
    writePinLow(ROW_SHIFT_PIN);
    select_row(current_row);
    matrix_output_select_delay();

    /* Set shift register SH/~LD pin to "shift" mode */
    writePinHigh(ROW_SHIFT_PIN);

    /* For each octet of columns... */
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index += 8) {
        spi_status_t read_result = spi_read();
        if (read_result >= 0) {
            /* only if SPI read successful: populate the matrix row with the
               state of the 8 consecutive column bits */
            current_row_value |= ((matrix_row_t)read_result << col_index);
        }
    }

    /* Unselect row & wait for all columns signals to go high. */
    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0); 

    /* Update row in matrix. */
    if (current_row_value != current_matrix[current_row]) {
        current_matrix[current_row] = current_row_value;
        return true;
    }

    return false;
}

bool matrix_scan_custom(matrix_row_t curr_matrix[]) {
    bool changed = false;

    /* set row, read cols */
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= matrix_read_cols_on_row(curr_matrix, current_row);
    }

    return changed;
}

/*
 * Local Variables:
 * c-basic-offset:4
 * fill-column: 76
 * End:
 */
