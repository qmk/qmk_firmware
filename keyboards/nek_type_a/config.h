/*
Copyright 2018 Mike Roberts

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
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

/* left columns are all onboard, right columns all on expander */
#define COL_EXPANDED { false, false, false, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true}
#define NEK_MATRIX_COL_PINS { C6, D7, B5, B6, B7, D6, D3, GPA0, GPA1, GPA2, GPA3, GPA4, GPA5, GPA6, GPA7, GPB0, GPB1, GPB2 }
#define NEK_MATRIX_ROW_PINS { F7, F6, F5, F4, F1, F0 }

#define DIODE_DIRECTION ROW2COL
