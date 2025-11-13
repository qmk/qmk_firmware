/* Copyright 2020 sekigon-gonnoc
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

#include "grs_70ec.h"

#include "ec_switch_matrix.h"
#include "matrix.h"
#include "debug.h"
#include "split_util.h"
#include "transport.h"
#include "debounce.h"

#ifndef LOW_THRESHOLD
#    define LOW_THRESHOLD 200
#endif

#ifndef HIGH_THRESHOLD
#    define HIGH_THRESHOLD 300
#endif

#define ERROR_DISCONNECT_COUNT 20

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

// row offsets for each hand
static uint8_t thisHand, thatHand;

// user-defined overridable functions
__attribute__((weak)) void matrix_slave_scan_user(void) {}

void matrix_init_custom(void) {
    split_pre_init();

    ecsm_config_t ecsm_config = {.low_threshold = LOW_THRESHOLD, .high_threshold = HIGH_THRESHOLD};

    ecsm_init(&ecsm_config);

    thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
    thatHand = ROWS_PER_HAND - thisHand;

    split_post_init();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool updated = ecsm_matrix_scan(current_matrix);

    static int cnt = 0;
    if (cnt++ == 300) {
        cnt = 0;
        ecsm_print_matrix();
        print("\n");
    }

    return updated;
}
