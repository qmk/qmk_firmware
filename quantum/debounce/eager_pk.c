/*
Copyright 2017 Alex Ong<the.onga@gmail.com>
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

#include "matrix.h"
#include "timer.h"
#include "quantum.h"
#include <stdlib.h>

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

#if (MATRIX_COLS <= 8)
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define ROW_SHIFTER ((uint32_t)1)
#endif

#define debounce_counter_t uint8_t

static debounce_counter_t *debounce_counters;
static bool                counters_need_update;
static bool                matrix_need_update;

#define DEBOUNCE_ELAPSED 251
#define MAX_DEBOUNCE (DEBOUNCE_ELAPSED - 1)

static uint16_t custom_wrap_timer_reference = 0;
static uint8_t custom_wrap_timer_last_value = 0;

static uint8_t custom_wrap_timer_read(void) {
    uint16_t custom_wrap_timer_new_reference = timer_read();
    uint16_t diff = custom_wrap_timer_new_reference - custom_wrap_timer_reference;
    custom_wrap_timer_reference = custom_wrap_timer_new_reference;
    custom_wrap_timer_last_value = (custom_wrap_timer_last_value + diff) % (MAX_DEBOUNCE + 1);
    return custom_wrap_timer_last_value;
}

void update_debounce_counters(uint8_t num_rows, uint8_t current_time);
void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t current_time);

// we use num_rows rather than MATRIX_ROWS to support split keyboards
void debounce_init(uint8_t num_rows) {
    debounce_counters = (debounce_counter_t *)malloc(num_rows * MATRIX_COLS * sizeof(debounce_counter_t));
    int i             = 0;
    for (uint8_t r = 0; r < num_rows; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            debounce_counters[i++] = DEBOUNCE_ELAPSED;
        }
    }
}

void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    uint8_t current_time = custom_wrap_timer_read();
    if (counters_need_update) {
        update_debounce_counters(num_rows, current_time);
    }

    if (changed || matrix_need_update) {
        transfer_matrix_values(raw, cooked, num_rows, current_time);
    }
}

// If the current time is > debounce counter, set the counter to enable input.
void update_debounce_counters(uint8_t num_rows, uint8_t current_time) {
    counters_need_update                 = false;
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (*debounce_pointer != DEBOUNCE_ELAPSED) {
                if (TIMER_DIFF(current_time, *debounce_pointer, MAX_DEBOUNCE) >= DEBOUNCE) {
                    *debounce_pointer = DEBOUNCE_ELAPSED;
                } else {
                    counters_need_update = true;
                }
            }
            debounce_pointer++;
        }
    }
}

// upload from raw_matrix to final matrix;
void transfer_matrix_values(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t current_time) {
    matrix_need_update                   = false;
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        matrix_row_t delta        = raw[row] ^ cooked[row];
        matrix_row_t existing_row = cooked[row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            matrix_row_t col_mask = (ROW_SHIFTER << col);
            if (delta & col_mask) {
                if (*debounce_pointer == DEBOUNCE_ELAPSED) {
                    *debounce_pointer    = current_time;
                    counters_need_update = true;
                    existing_row ^= col_mask;  // flip the bit.
                } else {
                    matrix_need_update = true;
                }
            }
            debounce_pointer++;
        }
        cooked[row] = existing_row;
    }
}

bool debounce_active(void) { return true; }
