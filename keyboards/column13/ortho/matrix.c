/* Copyright 2019
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
#include <avr/io.h>
#include <string.h>
#include <quantum.h>
#include <matrix.h>
#include <i2c_master.h>

#include "../modulo/expander.h"

#include <debug.h>

//_____CUSTOM MATRIX IMPLEMENTATION____________________________________________________

static expander expanders[MATRIX_ROWS] = {
    PCA9555(0x00),
    PCA9555(0x01),
    PCA9555(0x02),
    PCA9555(0x03),
    PCA9555(0x04),
    PCA9555(0x05)
};

void matrix_init_custom(void) {
    debug_enable = true;

    // _delay_ms(50);

    expander_init(expanders, MATRIX_ROWS);
    dprint("expanders initialized\n");
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    dprint("matrix_scan_custom");
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
//        xprintf("read[%d/%d]\n", i, MATRIX_ROWS);
        matrix_row_t last_row = current_matrix[i];
        matrix_row_t current_row = expander_readPins(&expanders[i]);
        if (current_row != 0 && current_row != last_row) {
            xprintf("row[%d]: %04X -> %04X\n", i, last_row, current_row);
        }
        current_matrix[i] = current_row;
        changed |= (last_row != current_row);
    }

    return changed;
}
