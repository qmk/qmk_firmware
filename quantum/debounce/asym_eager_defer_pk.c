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
Basic symmetric per-key algorithm. Uses an 8-bit counter per key.
When no state changes have occured for DEBOUNCE milliseconds, we push the state.
*/

#include "matrix.h"
#include "timer.h"
#include "quantum.h"
#include <stdlib.h>

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

#define ROW_SHIFTER ((matrix_row_t)1)

typedef struct {
    bool pressed : 1;
    uint8_t time : 7;
} debounce_counter_t;

#if DEBOUNCE > 0
static debounce_counter_t *debounce_counters;
static fast_timer_t last_time;
static bool counters_need_update;
static bool matrix_need_update;

#define DEBOUNCE_ELAPSED 0

static void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t elapsed_time);
static void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows);

// we use num_rows rather than MATRIX_ROWS to support split keyboards
void debounce_init(uint8_t num_rows) {
    debounce_counters = malloc(num_rows * MATRIX_COLS * sizeof(debounce_counter_t));
    int i = 0;
    for (uint8_t r = 0; r < num_rows; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            debounce_counters[i++].time = DEBOUNCE_ELAPSED;
        }
    }
}

void debounce_free(void) {
    free(debounce_counters);
    debounce_counters = NULL;
}

void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    bool updated_last = false;

    if (counters_need_update) {
        fast_timer_t now = timer_read_fast();
        fast_timer_t elapsed_time = TIMER_DIFF_FAST(now, last_time);

        last_time = now;
        updated_last = true;
        if (elapsed_time > UINT8_MAX) {
            elapsed_time = UINT8_MAX;
        }

        if (elapsed_time > 0) {
            update_debounce_counters_and_transfer_if_expired(raw, cooked, num_rows, elapsed_time);
        }
    }

    if (changed || matrix_need_update) {
        if (!updated_last) {
            last_time = timer_read_fast();
        }

        transfer_matrix_values(raw, cooked, num_rows);
    }
}

static void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t elapsed_time) {
    debounce_counter_t *debounce_pointer = debounce_counters;

    counters_need_update = false;
    matrix_need_update = false;

    for (uint8_t row = 0; row < num_rows; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            matrix_row_t col_mask = (ROW_SHIFTER << col);

            if (debounce_pointer->time != DEBOUNCE_ELAPSED) {
                if (debounce_pointer->time <= elapsed_time) {
                    debounce_pointer->time = DEBOUNCE_ELAPSED;

                    if (debounce_pointer->pressed) {
                        // key-down: eager
                        matrix_need_update = true;
                    } else {
                        // key-up: defer
                        cooked[row] = (cooked[row] & ~col_mask) | (raw[row] & col_mask);
                    }
                } else {
                    debounce_pointer->time -= elapsed_time;
                    counters_need_update = true;
                }
            }
            debounce_pointer++;
        }
    }
}

static void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows) {
    debounce_counter_t *debounce_pointer = debounce_counters;

    for (uint8_t row = 0; row < num_rows; row++) {
        matrix_row_t delta = raw[row] ^ cooked[row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            matrix_row_t col_mask = (ROW_SHIFTER << col);

            if (delta & col_mask) {
                if (debounce_pointer->time == DEBOUNCE_ELAPSED) {
                    debounce_pointer->pressed = (raw[row] & col_mask);
                    debounce_pointer->time = DEBOUNCE;
                    counters_need_update = true;

                    if (debounce_pointer->pressed) {
                        // key-down: eager
                        cooked[row] ^= col_mask;
                    }
                }
            } else if (debounce_pointer->time != DEBOUNCE_ELAPSED) {
                if (!debounce_pointer->pressed) {
                    // key-up: defer
                    debounce_pointer->time = DEBOUNCE_ELAPSED;
                }
            }
            debounce_pointer++;
        }
    }
}

bool debounce_active(void) { return true; }
#else
#    include "none.c"
#endif
