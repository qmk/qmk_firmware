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
#define PRODUCT_ID      0xEA53
#define DEVICE_VER      0x0001
#define MANUFACTURER    Kikos Lab
#define PRODUCT         KL90
/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { F1, F3, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { F2, F0, A2, A1, A0, D2, D3, D4, D5, D6, D7, E0, E1, C0, C1, C2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { A3, C3 }
#define ENCODERS_PAD_B { A4, C4 }

#define EMCODER_DIRECTION_FLIP

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/*EEPROM for via*/
#define DYNAMIC_KEYMAP_LAYER_COUNT 3