/* Copyright 2019 Jeremy Bernhardt
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
#include "faunchpad.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_scan_kb(void) {
#ifdef DEBUG_MATRIX
    for (uint8_t c = 0; c < MATRIX_COLS; c++)
			for (uint8_t r = 0; r < MATRIX_ROWS; r++)
		  	if (matrix_is_on(r, c)) xprintf("r:%d c:%d \n", r, c);
#endif
  matrix_scan_user();
}
