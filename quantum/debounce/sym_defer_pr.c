/*
Copyright 2021 Chad Austin <chad@chadaustin.me>
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
Symmetric per-row debounce algorithm. Changes only apply when
DEBOUNCE milliseconds have elapsed since the last change.
*/

#include "debounce.h"
#include "timer.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

static uint16_t last_time;
// Countdown timers for each matrix row, indexed by row.
static uint8_t countdowns[MATRIX_ROWS_PER_HAND] = {0};
// Last raw state for each matrix row, indexed by row.
static matrix_row_t last_raw[MATRIX_ROWS_PER_HAND] = {0};

void debounce_init(uint8_t num_rows) {}

/**
 * @brief Debounces the raw matrix state and updates the cooked (debounced) state.
 *
 * For each row in the matrix, this function tracks changes and applies a debounce period.
 * If a row's state changes, its countdown timer is reset. If the countdown timer expires,
 * the debounced state is updated to match the raw state.
 *
 * @param raw The current raw key state matrix.
 * @param cooked The debounced key state matrix to be updated.
 * @param num_rows Number of rows in the matrix.
 * @param changed True if the raw matrix has changed since the last call.
 * @return true if the debounced matrix has new key changes, false otherwise.
 */
bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    uint16_t now           = timer_read();
    uint16_t elapsed16     = TIMER_DIFF_16(now, last_time);
    last_time              = now;
    uint8_t elapsed        = (elapsed16 > 255) ? 255 : elapsed16;
    bool    cooked_changed = false;

    uint8_t* countdown = countdowns;

    for (uint8_t row = 0; row < MATRIX_ROWS_PER_HAND; ++row, ++countdown) {
        matrix_row_t raw_row = raw[row];

        if (raw_row != last_raw[row]) {
            *countdown    = DEBOUNCE;
            last_raw[row] = raw_row;
        } else if (*countdown > elapsed) {
            *countdown -= elapsed;
        } else if (*countdown) {
            cooked_changed |= cooked[row] ^ raw_row;
            cooked[row] = raw_row;
            *countdown  = 0;
        }
    }

    return cooked_changed;
}
