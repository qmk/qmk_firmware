/* Copyright 2021 eithanshavit
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

#pragma once

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

// wiring of each half
#define MATRIX_ROW_PINS { F5, F4, D0 }
#define MATRIX_COL_PINS { D1, D2, D3 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define DIODE_DIRECTION COL2ROW

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
