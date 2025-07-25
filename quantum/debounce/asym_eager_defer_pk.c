/*
 * Copyright 2017 Alex Ong <the.onga@gmail.com>
 * Copyright 2020 Andrei Purdea <andrei@purdea.ro>
 * Copyright 2021 Simon Arlott
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

/*
Asymetric per-key algorithm. After pressing a key, it immediately changes state,
with no further inputs accepted until DEBOUNCE milliseconds have occurred. After
releasing a key, that state is pushed after no changes occur for DEBOUNCE milliseconds.
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

// Maximum debounce: 127ms
#if DEBOUNCE > 127
#    undef DEBOUNCE
#    define DEBOUNCE 127
#endif

typedef struct {
    bool    pressed : 1;
    uint8_t time : 7;
} debounce_counter_t;

#if DEBOUNCE > 0
// Uses MATRIX_ROWS_PER_HAND instead of MATRIX_ROWS to support split keyboards
static debounce_counter_t debounce_counters[MATRIX_ROWS_PER_HAND * MATRIX_COLS] = {0};
static bool               counters_need_update;
static bool               matrix_need_update;
static bool               cooked_changed;

#    define DEBOUNCE_ELAPSED 0

static void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t elapsed_time);
static void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[]);

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

    if (changed || matrix_need_update) {
        if (!updated_last) {
            last_time = timer_read_fast();
        }

        transfer_matrix_values(raw, cooked);
    }

    return cooked_changed;
}

/**
 * @brief Processes per-key debounce counters and updates the debounced matrix state.
 *
 * This function iterates through each key in the matrix and updates its debounce counter
 * based on the elapsed time. If the debounce period has expired, the debounced state is
 * updated accordingly for key-down (eager) and key-up (defer) events.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix to be updated.
 * @param elapsed_time The time elapsed since the last debounce update, in milliseconds.
 */
static void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t elapsed_time) {
    counters_need_update = false;
    matrix_need_update   = false;

    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t index = row * MATRIX_COLS + col;

            if (debounce_counters[index].time != DEBOUNCE_ELAPSED) {
                if (debounce_counters[index].time <= elapsed_time) {
                    debounce_counters[index].time = DEBOUNCE_ELAPSED;

                    if (debounce_counters[index].pressed) {
                        // key-down: eager
                        matrix_need_update = true;
                    } else {
                        // key-up: defer
                        matrix_row_t col_mask    = (MATRIX_ROW_SHIFTER << col);
                        matrix_row_t cooked_next = (cooked[row] & ~col_mask) | (raw[row] & col_mask);
                        cooked_changed |= cooked_next ^ cooked[row];
                        cooked[row] = cooked_next;
                    }
                } else {
                    debounce_counters[index].time -= elapsed_time;
                    counters_need_update = true;
                }
            }
        }
    }
}

/**
 * @brief Applies debounced changes to the matrix state based on per-key counters.
 *
 * This function compares the raw and cooked key state matrices to detect changes.
 * For each key, it updates the debounce counter and the debounced state according
 * to the debounce algorithm. Key-down events are handled eagerly, while key-up
 * events are deferred until the debounce period has elapsed.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix to be updated.
 */
static void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[]) {
    matrix_need_update = false;

    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        matrix_row_t delta = raw[row] ^ cooked[row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t index = row * MATRIX_COLS + col;

            matrix_row_t col_mask = (MATRIX_ROW_SHIFTER << col);
            if (delta & col_mask) {
                if (debounce_counters[index].time == DEBOUNCE_ELAPSED) {
                    debounce_counters[index].pressed = (raw[row] & col_mask);
                    debounce_counters[index].time    = DEBOUNCE;
                    counters_need_update             = true;

                    if (debounce_counters[index].pressed) {
                        // key-down: eager
                        cooked[row] ^= col_mask;
                        cooked_changed = true;
                    }
                }
            } else if (debounce_counters[index].time != DEBOUNCE_ELAPSED) {
                if (!debounce_counters[index].pressed) {
                    // key-up: defer
                    debounce_counters[index].time = DEBOUNCE_ELAPSED;
                }
            }
        }
    }
}

#else
#    include "none.c"
#endif
