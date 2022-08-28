/*
Copyright 2021 Altain

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

/* Matrix Size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/* Matrix Pinouts */
//                         0   1   2   3   4   5   6   7   8   9   A   B   C   D   E
#define MATRIX_ROW_PINS { F0, F1, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { B0, B4, B5, B6, B7, C6, C7, D0, D1, D2, D3, D4, D5, D6, D7 } 

/* Diode Direction */
#define DIODE_DIRECTION COL2ROW

/* Debounce Setting */
#define DEBOUNCE 5


