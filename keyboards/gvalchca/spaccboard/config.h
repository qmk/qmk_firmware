/*
Copyright 2021 Kirill Shkuretskiy

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

#pragma once


/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {B1,B2,B3,C7,F0}
#define MATRIX_COL_PINS {E6,B7,D5,D6,D7,B4,B5,B6,C6,F7,F6,F5,F4,F1,D3}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define QMK_ESC_OUTPUT E6 // usually COL
#define QMK_ESC_INPUT B1 // usually ROW
