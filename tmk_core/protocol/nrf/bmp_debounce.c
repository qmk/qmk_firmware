
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

// modified for BMP by sekigon-gonnoc

#include "matrix.h"
#include "timer.h"
#include "quantum.h"

#define ROW_SHIFTER ((matrix_row_t)1)
#define EVENT_CNT_MAX 16

typedef uint8_t debounce_counter_t;

static debounce_counter_t  debounce_counters[MATRIX_ROWS * MATRIX_COLS];
static fast_timer_t        last_time;
static bool                counters_need_update;
static bool                matrix_need_update;

#define DEBOUNCE_ELAPSED 0

static void update_debounce_counters(uint8_t num_rows, uint8_t num_cols,
                                     uint8_t elapsed_time);
static int transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[],
                                   uint8_t num_rows, uint8_t num_cols,
                                   uint8_t              debounce_value,
                                   bmp_api_key_event_t *events);

// we use num_rows rather than MATRIX_ROWS to support split keyboards
void bmp_debounce_init(void) {
    int i = 0;
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            debounce_counters[i++] = DEBOUNCE_ELAPSED;
        }
    }
}

int bmp_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows,
             uint8_t num_cols, uint8_t debounce_value, bool changed,
             bmp_api_key_event_t *events) {
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
            update_debounce_counters(num_rows, num_cols, elapsed_time);
        }
    }

    if (changed || matrix_need_update) {
        if (!updated_last) {
            last_time = timer_read_fast();
        }

        return transfer_matrix_values(raw, cooked, num_rows, num_cols, debounce_value, events);
    }

    return 0;
}

// If the current time is > debounce counter, set the counter to enable input.
static void update_debounce_counters(uint8_t num_rows, uint8_t num_cols, uint8_t elapsed_time) {
    counters_need_update                 = false;
    matrix_need_update                   = false;
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        for (uint8_t col = 0; col < num_cols; col++) {
            if (*debounce_pointer != DEBOUNCE_ELAPSED) {
                if (*debounce_pointer <= elapsed_time) {
                    *debounce_pointer = DEBOUNCE_ELAPSED;
                    matrix_need_update = true;
                } else {
                    *debounce_pointer -= elapsed_time;
                    counters_need_update = true;
                }
            }
            debounce_pointer++;
        }
    }
}

// upload from raw_matrix to final matrix;
static int transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[],
                                   uint8_t num_rows, uint8_t num_cols,
                                   uint8_t debounce_value, bmp_api_key_event_t *events) {
    debounce_counter_t *debounce_pointer = debounce_counters;
    uint8_t event_count = 0;
    for (uint8_t row = 0; row < num_rows; row++) {
        matrix_row_t delta        = raw[row] ^ cooked[row];
        matrix_row_t existing_row = cooked[row];
        for (uint8_t col = 0; col < num_cols; col++) {
            matrix_row_t col_mask = (ROW_SHIFTER << col);
            if (delta & col_mask) {
                if (*debounce_pointer == DEBOUNCE_ELAPSED) {
                    *debounce_pointer    = debounce_value;
                    counters_need_update = true;
                    existing_row ^= col_mask;  // flip the bit.

                    events[event_count].row = row;
                    events[event_count].col = col;
                    events[event_count].state = (existing_row >> col) & 1;
                    if (event_count < EVENT_CNT_MAX - 1) event_count++;
                }
            }
            debounce_pointer++;
        }
        cooked[row] = existing_row;
    }

    return event_count;
}

// bool debounce_active(void) { return true; }
