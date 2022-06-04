/*
 * Copyright (c) 2018 Charlie Waters
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
#include <hal.h>
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"
#include "annepro2.h"

pin_t row_list[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_list[MATRIX_COLS] = MATRIX_COL_PINS;

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;
    // cache of input ports for columns
    static uint16_t port_cache[4];
    // scan each row
    for (int row = 0; row < MATRIX_ROWS; row++) {
        palClearLine(row_list[row]);
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        // read i/o ports
        port_cache[0] = palReadPort(IOPORTA);
        port_cache[1] = palReadPort(IOPORTB);
        port_cache[2] = palReadPort(IOPORTC);
        port_cache[3] = palReadPort(IOPORTD);
        palSetLine(row_list[row]);

        // get columns from ports
        matrix_row_t data = 0;
        for (int col = 0; col < MATRIX_COLS; ++col) {
            pin_t line = col_list[col];
            uint16_t port = port_cache[HT32_PAL_IDX(PAL_PORT(line))];
            data |= (((port & (1 << PAL_PAD(line))) ? 0 : 1) << col);
        }

        if (current_matrix[row] != data) {
            current_matrix[row] = data;
            matrix_has_changed  = true;
        }
    }
    return matrix_has_changed;
}