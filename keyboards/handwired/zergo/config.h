/*
Copyright 2020 E.Zelianin

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

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, D7, C3, D6, D5, D4 }
#define MATRIX_COL_PINS { C7, C6, C5, C4, C2, C1, B7, D3, D2, B6, B5, B4, B3, B2 }
#define UNUSED_PINS { A0, A1, A2, A3, A4, A5, A6, A7, B0, C0, E0, E1, E4, E5, F0, F1, F2, F3, F4, F5, F6, F7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

