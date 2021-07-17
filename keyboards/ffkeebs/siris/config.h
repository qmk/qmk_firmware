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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x04D8
#define PRODUCT_ID      0xE96C
#define DEVICE_VER      0x0001
#define MANUFACTURER    Swiftrax
#define PRODUCT         Siris

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { B5, B4, D7, D6, D4 }
#define MATRIX_COL_PINS { D2, D1, D0, B7, B3, B2, F0, F1, F4, F5, F6, F7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

#define ENCODERS_PAD_A { D3, C6 }
#define ENCODERS_PAD_B { D5, B6 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
