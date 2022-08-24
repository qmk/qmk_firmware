/*
Copyright 2020 adamws

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
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B2, B1, B0, F0, B4 }
#define MATRIX_COL_PINS { F7, C6, F6, B6, F5, F4, B5, F1, E6, D0, D7, D5, D1, D3, D2 }
#define UNUSED_PINS { B3, B7, C7, D4, D6 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
