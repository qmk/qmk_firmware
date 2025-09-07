// Copyright 2017 Alex Ong<the.onga@gmail.com>
// Copyright 2021 Simon Arlott
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Basic global debounce algorithm. Used in 99% of keyboards at time of implementation
// When no state changes have occured for DEBOUNCE milliseconds, we push the state.

#include "debounce.h"
#include "timer.h"
#include <string.h>
#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

// Maximum debounce: 255ms
#if DEBOUNCE > UINT8_MAX
#    undef DEBOUNCE
#    define DEBOUNCE UINT8_MAX
#endif

#if DEBOUNCE > 0

void debounce_init(uint8_t num_rows) {}

bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    static fast_timer_t debouncing_time;
    static bool         debouncing     = false;
    bool                cooked_changed = false;

    if (changed) {
        debouncing      = true;
        debouncing_time = timer_read_fast();
    } else if (debouncing && timer_elapsed_fast(debouncing_time) >= DEBOUNCE) {
        size_t matrix_size = num_rows * sizeof(matrix_row_t);
        if (memcmp(cooked, raw, matrix_size) != 0) {
            memcpy(cooked, raw, matrix_size);
            cooked_changed = true;
        }
        debouncing = false;
    }

    return cooked_changed;
}

#else // no debouncing.
#    include "none.c"
#endif
