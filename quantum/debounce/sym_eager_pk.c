/*
Copyright 2017 Alex Ong<the.onga@gmail.com>
Copyright 2021 Simon Arlott
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

/*
Basic per-key algorithm. Uses an 8-bit counter per key.
After pressing a key, it immediately changes state, and sets a counter.
No further inputs are accepted until DEBOUNCE milliseconds have occurred.
*/

#include "debounce.h"
#include "timer.h"
#include "util.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

// Maximum debounce: 255ms
#if DEBOUNCE > UINT8_MAX
#    undef DEBOUNCE
#    define DEBOUNCE UINT8_MAX
#endif

#define DEBOUNCE_ELAPSED 0

#if DEBOUNCE > 0
typedef uint8_t debounce_counter_t;
// Uses MATRIX_ROWS_PER_HAND instead of MATRIX_ROWS to support split keyboards
static debounce_counter_t debounce_counters[MATRIX_ROWS_PER_HAND * MATRIX_COLS] = {DEBOUNCE_ELAPSED};
static bool               counters_need_update;
static bool               matrix_need_update;
static bool               cooked_changed;

static inline void update_debounce_counters(uint8_t elapsed_time);
static inline void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[]);

void debounce_init(void) {}

bool debounce(matrix_row_t raw[], matrix_row_t cooked[], bool changed) {
    static fast_timer_t last_time;
    bool                updated_last = false;
    cooked_changed                   = false;

    if (counters_need_update) {
        fast_timer_t now          = timer_read_fast();
        fast_timer_t elapsed_time = TIMER_DIFF_FAST(now, last_time);

        last_time    = now;
        updated_last = true;

        if (elapsed_time > 0) {
            // Update debounce counters with elapsed timer clamped to UINT8_MAX
            update_debounce_counters(MIN(elapsed_time, UINT8_MAX));
        }
    }

    if (changed || matrix_need_update) {
        if (!updated_last) {
            last_time = timer_read_fast();
        }

        transfer_matrix_values(raw, cooked);
    }

    return cooked_changed;
}

/**
 * @brief Updates per-key debounce counters and determines if matrix needs updating.
 *
 * Iterates through each key in the matrix and checks its debounce counter. If the debounce
 * period has elapsed, the counter is reset and the matrix is marked for update. Otherwise,
 * the counter is decremented by the elapsed time and marked for further updates if needed.
 *
 * @param elapsed_time The time elapsed since the last debounce update, in milliseconds.
 */
static inline void update_debounce_counters(uint8_t elapsed_time) {
    counters_need_update = false;
    matrix_need_update   = false;

    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        uint16_t row_offset = row * MATRIX_COLS;

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t index = row_offset + col;

            if (debounce_counters[index] != DEBOUNCE_ELAPSED) {
                if (debounce_counters[index] <= elapsed_time) {
                    debounce_counters[index] = DEBOUNCE_ELAPSED;
                    matrix_need_update       = true;
                } else {
                    debounce_counters[index] -= elapsed_time;
                    counters_need_update = true;
                }
            }
        }
    }
}

/**
 * @brief Transfers debounced key states from the raw matrix to the cooked matrix.
 *
 * For each key in the matrix, this function checks if its state has changed and if its
 * debounce counter has elapsed. If so, the debounce counter is reset, the cooked matrix
 * is updated to reflect the new state, and the matrix is marked for further updates.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix to be updated.
 */
static inline void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[]) {
    matrix_need_update = false;

    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        uint16_t     row_offset   = row * MATRIX_COLS;
        matrix_row_t delta        = raw[row] ^ cooked[row];
        matrix_row_t existing_row = cooked[row];

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t index = row_offset + col;

            matrix_row_t col_mask = (MATRIX_ROW_SHIFTER << col);
            if (delta & col_mask) {
                if (debounce_counters[index] == DEBOUNCE_ELAPSED) {
                    debounce_counters[index] = DEBOUNCE;
                    counters_need_update     = true;
                    existing_row ^= col_mask; // flip the bit.
                    cooked_changed = true;
                }
            }
        }
        cooked[row] = existing_row;
    }
}

#else
#    include "none.c"
#endif
