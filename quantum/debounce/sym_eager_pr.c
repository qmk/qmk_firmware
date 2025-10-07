// Copyright 2017 Alex Ong<the.onga@gmail.com>
// Copyright 2021 Simon Arlott
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Basic per-row algorithm. Uses an 8-bit counter per key.
// After pressing a key, it immediately changes state, and sets a counter.
// No further inputs are accepted until DEBOUNCE milliseconds have occurred.

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
static debounce_counter_t debounce_counters[MATRIX_ROWS_PER_HAND] = {DEBOUNCE_ELAPSED};
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
 * @brief Updates per-row debounce counters and determines if matrix needs updating.
 *
 * Iterates through each row in the matrix and checks its debounce counter. If the debounce
 * period has elapsed, the counter is reset and the matrix is marked for update. Otherwise,
 * the counter is decremented by the elapsed time and marked for further updates if needed.
 *
 * @param elapsed_time The time elapsed since the last debounce update, in milliseconds.
 */
static inline void update_debounce_counters(uint8_t elapsed_time) {
    counters_need_update = false;
    matrix_need_update   = false;

    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        if (debounce_counters[row] != DEBOUNCE_ELAPSED) {
            if (debounce_counters[row] <= elapsed_time) {
                debounce_counters[row] = DEBOUNCE_ELAPSED;
                matrix_need_update     = true;
            } else {
                debounce_counters[row] -= elapsed_time;
                counters_need_update = true;
            }
        }
    }
}

/**
 * @brief Transfers debounced key states from the raw matrix to the cooked matrix.
 *
 * For each row in the matrix, this function checks if its state has changed and if its
 * debounce counter has elapsed. If so, the debounce counter is reset, the cooked matrix
 * is updated to reflect the new state, and the matrix is marked for further updates.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix
 */
static inline void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[]) {
    matrix_need_update = false;

    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        matrix_row_t existing_row = cooked[row];
        matrix_row_t raw_row      = raw[row];

        // determine new value basd on debounce pointer + raw value
        if (existing_row != raw_row) {
            if (debounce_counters[row] == DEBOUNCE_ELAPSED) {
                debounce_counters[row] = DEBOUNCE;
                cooked_changed |= cooked[row] ^ raw_row;
                cooked[row]          = raw_row;
                counters_need_update = true;
            }
        }
    }
}

#else
#    include "none.c"
#endif
