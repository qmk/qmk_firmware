/* Copyright 2023 Viktus Design LLC
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

#include "quantum.h"
#include "ec.h"
#include "matrix.h"
//#include "debug.h"  // needed for debugging

#define RESET_PT 55
#define ACTUATION_PT 65

// console debugging for pad values
void keyboard_post_init_kb() {
    debug_enable = true;
    debug_matrix = true;
}

void matrix_init_custom(void) {
    ec_config_t ec_config = {.reset_pt = RESET_PT, .actuation_pt = ACTUATION_PT};

    ec_init(&ec_config);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool updated = ec_matrix_scan(current_matrix);

    // console debugging for pad values
    /*static int cnt = 0;
    if (cnt++ == 1000) {
        cnt = 0;
        ec_dprint_matrix();
        dprintf("\n");
    }*/

    return updated;
}
