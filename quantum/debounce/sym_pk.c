/*
Copyright 2017 Alex Ong<the.onga@gmail.com>
Copyright 2020 Andrei Purdea<andrei@purdea.ro>
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
Basic symmetric per-key algorithm. Uses an 8-bit counter per key.
When no state changes have occured for DEBOUNCE milliseconds, we push the state.
*/

#include "matrix.h"
#include "timer.h"
#include "quantum.h"
#include <stdlib.h>

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

#define ROW_SHIFTER ((matrix_row_t)1)

#define debounce_counter_t uint8_t

static debounce_counter_t *debounce_counters;
static bool                counters_need_update;

#define DEBOUNCE_ELAPSED 251
#define MAX_DEBOUNCE (DEBOUNCE_ELAPSED - 1)

static uint8_t wrapping_timer_read(void) {
    static uint16_t time = 0;
    static uint8_t  last_result = 0;
    uint16_t new_time = timer_read();
    uint16_t diff = new_time - time;
    time = new_time;
    last_result = (last_result + diff) % (MAX_DEBOUNCE + 1);
    return last_result;
}

void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t current_time);
void start_debounce_counters(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t current_time);

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
    uint8_t current_time = wrapping_timer_read();
    if (counters_need_update) {
        update_debounce_counters_and_transfer_if_expired(raw, cooked, num_rows, current_time);
    }

    if (changed) {
        start_debounce_counters(raw, cooked, num_rows, current_time);
    }
}

void update_debounce_counters_and_transfer_if_expired(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t current_time) {
    counters_need_update                 = false;
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (*debounce_pointer != DEBOUNCE_ELAPSED) {
                if (TIMER_DIFF(current_time, *debounce_pointer, MAX_DEBOUNCE) >= DEBOUNCE) {
                    *debounce_pointer = DEBOUNCE_ELAPSED;
                    cooked[row]       = (cooked[row] & ~(ROW_SHIFTER << col)) | (raw[row] & (ROW_SHIFTER << col));
                } else {
                    counters_need_update = true;
                }
            }
            debounce_pointer++;
        }
    }
}

void start_debounce_counters(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, uint8_t current_time) {
    debounce_counter_t *debounce_pointer = debounce_counters;
    for (uint8_t row = 0; row < num_rows; row++) {
        matrix_row_t delta = raw[row] ^ cooked[row];
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (delta & (ROW_SHIFTER << col)) {
                if (*debounce_pointer == DEBOUNCE_ELAPSED) {
                    *debounce_pointer    = current_time;
                    counters_need_update = true;
                }
            } else {
                *debounce_pointer = DEBOUNCE_ELAPSED;
            }
            debounce_pointer++;
        }
    }
}

bool debounce_active(void) { return true; }
