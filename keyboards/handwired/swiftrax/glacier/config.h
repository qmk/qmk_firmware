/*
Copyright 2021 Swiftrax <swiftrax@gmail.com>

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
#define MATRIX_ROWS 12
#define MATRIX_COLS 10

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { B1, B2, B3, B4, B5, B6, E5, E4, D4, D5, D7, D6 }
#define MATRIX_COL_PINS { F0, F1, F2, F3, F4, F5, F6, D0, D1, D2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/*EEPROM for via*/
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

/* RGB */
#define RGB_DI_PIN B0
#define RGBLED_NUM 12