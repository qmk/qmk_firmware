// Copyright 2017 Alex Ong<the.onga@gmail.com>
// Copyright 2020 Andrei Purdea<andrei@purdea.ro>
// Copyright 2021 Simon Arlott
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Basic symmetric per-key algorithm. Uses an 8-bit counter per key.
// When no state changes have occured for DEBOUNCE milliseconds, we push the state.

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
static bool               cooked_changed;

static inline void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t elapsed_time);
static inline void start_debounce_counters(matrix_row_t raw[], matrix_row_t cooked[]);

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
 * @brief Updates debounce counters and transfers debounced key states if the debounce period has expired.
 *
 * Iterates through each key in the matrix and checks its debounce counter. If the debounce period has expired
 * for a key, the debounced state is updated to match the raw state. Otherwise, the debounce counter is decremented
 * by the elapsed time and marked for further updates.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix to be updated.
 * @param elapsed_time The time elapsed since the last debounce update, in milliseconds.
 */
static inline void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t elapsed_time) {
    counters_need_update = false;
    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        uint16_t row_offset = row * MATRIX_COLS;

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t index = row_offset + col;

            if (debounce_counters[index] != DEBOUNCE_ELAPSED) {
                if (debounce_counters[index] <= elapsed_time) {
                    debounce_counters[index] = DEBOUNCE_ELAPSED;
                    matrix_row_t col_mask    = (MATRIX_ROW_SHIFTER << col);
                    matrix_row_t cooked_next = (cooked[row] & ~col_mask) | (raw[row] & col_mask);
                    cooked_changed |= cooked[row] ^ cooked_next;
                    cooked[row] = cooked_next;
                } else {
                    debounce_counters[index] -= elapsed_time;
                    counters_need_update = true;
                }
            }
        }
    }
}

/**
 * @brief Initializes debounce counters for keys with changed states.
 *
 * For each key in the matrix, this function checks if the raw state differs from the debounced state.
 * If a change is detected and the debounce counter has elapsed, the counter is set to the debounce period
 * and marked for update. Otherwise, the counter is cleared.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix.
 */
static inline void start_debounce_counters(matrix_row_t raw[], matrix_row_t cooked[]) {
    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; row++) {
        uint16_t     row_offset = row * MATRIX_COLS;
        matrix_row_t delta      = raw[row] ^ cooked[row];

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t index = row_offset + col;

            if (delta & (MATRIX_ROW_SHIFTER << col)) {
                if (debounce_counters[index] == DEBOUNCE_ELAPSED) {
                    debounce_counters[index] = DEBOUNCE;
                    counters_need_update     = true;
                }
            } else {
                debounce_counters[index] = DEBOUNCE_ELAPSED;
            }
        }
    }
}

#else
#    include "none.c"
#endif
