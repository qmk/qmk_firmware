/*
Copyright 2017 Alex Ong<the.onga@gmail.com>
Copyright 2020 Andrei Purdea<andrei@purdea.ro>
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
Basic symmetric per-row algorithm. Uses an 8-bit counter per row.
When no state changes have occured for DEBOUNCE milliseconds, we push the state.
*/

#include "debounce.h"
#include "timer.h"
#include "util.h"

#ifdef PROTOCOL_CHIBIOS
#    if CH_CFG_USE_MEMCORE == FALSE
#        error ChibiOS is configured without a memory allocator. Your keyboard may have set `#define CH_CFG_USE_MEMCORE FALSE`, which is incompatible with this debounce algorithm.
#    endif
#endif

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

// Maximum debounce: 255ms
#if DEBOUNCE > UINT8_MAX
#    undef DEBOUNCE
#    define DEBOUNCE UINT8_MAX
#endif

typedef uint8_t debounce_counter_t;

#if DEBOUNCE > 0
// Uses MATRIX_ROWS_PER_HAND instead of MATRIX_ROWS to support split keyboards
static debounce_counter_t debounce_counters[MATRIX_ROWS_PER_HAND] = {0};
static bool               counters_need_update;
static bool               cooked_changed;

#    define DEBOUNCE_ELAPSED 0

static void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t elapsed_time);
static void start_debounce_counters(matrix_row_t raw[], matrix_row_t cooked[]);

void debounce_init(uint8_t num_rows) {}

bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
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
            update_debounce_counters_and_transfer_if_expired(raw, cooked, MIN(elapsed_time, UINT8_MAX));
        }
    }

    if (changed) {
        if (!updated_last) {
            last_time = timer_read_fast();
        }

        start_debounce_counters(raw, cooked);
    }

    return cooked_changed;
}

/**
 * @brief Updates debounce counters and transfers debounced row states if the debounce period has expired.
 *
 * Iterates through each row in the matrix and checks its debounce counter. If the debounce period has expired
 * for a row, the debounced state is updated to match the raw state. Otherwise, the debounce counter is decremented
 * by the elapsed time and marked for further updates.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix to be updated.
 * @param elapsed_time The time elapsed since the last debounce update, in milliseconds.
 */
static void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t elapsed_time) {
    counters_need_update = false;
    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        if (debounce_counters[row] != DEBOUNCE_ELAPSED) {
            if (debounce_counters[row] <= elapsed_time) {
                debounce_counters[row] = DEBOUNCE_ELAPSED;
                cooked_changed |= cooked[row] ^ raw[row];
                cooked[row] = raw[row];
            } else {
                debounce_counters[row] -= elapsed_time;
                counters_need_update = true;
            }
        }
    }
}

/**
 * @brief Initializes debounce counters for rows with changed states.
 *
 * For each row in the matrix, this function checks if the raw state differs from the debounced state.
 * If a change is detected and the debounce counter has elapsed, the counter is set to the debounce period
 * and marked for update. Otherwise, the counter is cleared.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix.
 */
static void start_debounce_counters(matrix_row_t raw[], matrix_row_t cooked[]) {
    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        if (raw[row] != cooked[row]) {
            debounce_counters[row] = DEBOUNCE;
            counters_need_update   = true;
        } else {
            debounce_counters[row] = DEBOUNCE_ELAPSED;
        }
    }
}

#else
#    include "none.c"
#endif