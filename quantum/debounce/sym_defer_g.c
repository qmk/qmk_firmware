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
Basic global debounce algorithm. Used in 99% of keyboards at time of implementation
When no state changes have occured for DEBOUNCE milliseconds, we push the state.
*/
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

typedef uint8_t debounce_counter_t;

#if DEBOUNCE > 0

#    define DEBOUNCE_ELAPSED 0

static debounce_counter_t debounce_counter = DEBOUNCE_ELAPSED;

static fast_timer_t last_time;

void debounce_init(uint8_t num_rows) {}

bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    bool cooked_changed = false;

    if (changed) {
        debounce_counter = DEBOUNCE;
        last_time        = timer_read_fast();
    } else if (debounce_counter != DEBOUNCE_ELAPSED) {
        if (debounce_counter <= timer_elapsed_fast(last_time)) {
            debounce_counter   = DEBOUNCE_ELAPSED;
            size_t matrix_size = num_rows * sizeof(matrix_row_t);
            if (memcmp(cooked, raw, matrix_size) != 0) {
                memcpy(cooked, raw, matrix_size);
                cooked_changed = true;
            }
        }
    }

    return cooked_changed;
}

void debounce_free(void) {}
#else // no debouncing.
#    include "none.c"
#endif
