/**
 * matrix.c
 * 
 * Copyright 2020 astro <yuleiz@gmail.com>
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
#include "quantum.h"
#include "matrix.h"
#include "tca6424.h"
#include "abelx.h"

static const uint16_t col_pins[MATRIX_COLS] = CUSTOM_MATRIX_COL_PINS;

void matrix_init_custom(void)
{
    tca6424_init();
    // set port0
    tca6424_write_config(TCA6424_PORT0, 0);
    // set port1
    tca6424_write_config(TCA6424_PORT1, 0);
    // set port2
    tca6424_write_config(TCA6424_PORT2, 0xF5);

    // clear output
    tca6424_write_port(TCA6424_PORT0, 0);
    tca6424_write_port(TCA6424_PORT1, 0);
    tca6424_write_port(TCA6424_PORT2, 0);
}


static uint8_t row_mask[] = {ROW1_MASK,ROW2_MASK,ROW3_MASK,ROW4_MASK,ROW5_MASK,ROW6_MASK};
static uint8_t col_mask[] = {COL1_MASK, COL2_MASK, COL3_MASK, COL4_MASK, COL5_MASK, COL6_MASK, COL7_MASK, COL8_MASK, COL9_MASK, COL10_MASK, COL11_MASK, COL12_MASK, COL13_MASK, COL14_MASK, COL15_MASK, COL16_MASK};

bool matrix_scan_custom(matrix_row_t current_matrix[])
{
    bool changed = false;
    uint8_t p0_data = tca6424_read_port(TCA6424_PORT0);

    for (int col = 0; col < MATRIX_COLS; col++) {
        // Select col and wait for col selecton to stabilize
        switch(col) {
        case 0:
            set_pin(col_pins[col]);
            break;
        case 1 ... 8:
            tca6424_write_port(TCA6424_PORT1, col_mask[col]);
            break;
        default:
            tca6424_write_port(TCA6424_PORT0, col_mask[col]|(p0_data&0x01));
            break;
        }
        matrix_io_delay();

        // read row port for all rows
        uint8_t row_value = tca6424_read_port(ROW_PORT);
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            uint8_t tmp = row;
            // Store last value of row prior to reading
            matrix_row_t last_row_value = current_matrix[tmp];

            // Check row pin state
            if (row_value & row_mask[row]) {
                // Pin HI, set col bit
                current_matrix[tmp] |= (1 << col);
            } else {
                // Pin LOW, clear col bit
                current_matrix[tmp] &= ~(1 << col);
            }

            // Determine if the matrix changed state
            if ((last_row_value != current_matrix[tmp]) && !(changed)) {
                changed = true;
            }
        }
        // Unselect col
        switch(col) {
        case 0:
            clear_pin(col_pins[col]);
            break;
        case 8:
            tca6424_write_port(TCA6424_PORT1, 0);
            break;
        case 15:
            tca6424_write_port(TCA6424_PORT0, p0_data&0x01);
            break;
        default:
            break;
        }
    }

    return changed;
}
