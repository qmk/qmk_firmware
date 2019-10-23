/*
 * Copyright © 2009-2019 Benjamin Holt & Scott Perry <qmk@numist.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "matrix.h"
#include "timer.h"
#include "quantum.h"
#include <stdlib.h>

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

/*
 * This debouncer uses an overflowing stacked counter cribbed with permission
 * from https://github.com/numist/project-typewriter/blob/master/debounce.h
 */
#define DEBOUNCE_SAMPLES 4
typedef struct {
    matrix_row_t db0;    // counter bit 0
    matrix_row_t db1;    // counter bit 1
    matrix_row_t state;  // debounced state
} debounce_t;

static inline matrix_row_t debounce_single_row(debounce_t *d, matrix_row_t sample) {
    matrix_row_t changes, delta = sample ^ d->state;
    d->db1  = ((d->db1) ^ (d->db0)) & delta;
    d->db0  = ~(d->db0) & delta;
    changes = ~(~delta | (d->db0) | (d->db1));
    d->state ^= changes;
    return changes;
}

static debounce_t *debounce_state = 0;
static uint16_t    timer;
static bool        primed = false;
static uint8_t     iter;

void debounce_init(uint8_t num_rows) {
    if (debounce_state) {
        free(debounce_state);
    }
    debounce_state = (debounce_t *)calloc(num_rows, sizeof(debounce_t));
}

void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    if (!primed) {
        // Initialize debouncer state with current values
        for (int i = 0; i < num_rows; i++) {
            cooked[i] = debounce_state[i].state = raw[i];
        }
        timer  = timer_read();
        primed = true;
    }

    uint8_t fudge = (iter++ % DEBOUNCE_SAMPLES) < (DEBOUNCE % DEBOUNCE_SAMPLES) ? 1 : 0;
    if (timer_elapsed(timer) > (DEBOUNCE / DEBOUNCE_SAMPLES + fudge)) {
        for (int i = 0; i < num_rows; i++) {
            debounce_t *d = &debounce_state[i];
            cooked[i] ^= debounce_single_row(d, raw[i]);
        }
        timer = timer_read();
    }
}
