/*
Copyright 2022 Swiftrax <swiftrax@gmail.com>

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
#define PRODUCT_ID      0xE785
#define DEVICE_VER      0x0001
#define MANUFACTURER    Kikos Lab
#define PRODUCT         Formula1800
/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 10

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { F6, F7, C0, C1, E0, E1, D6, D7, D4, D5, D3, D2 }
#define MATRIX_COL_PINS { A3, A4, B5, B4, B3, B2, F0, F1, F2, F3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define ENCODERS_PAD_A { A2, F4 }
#define ENCODERS_PAD_B { A1, F5 }

//#define ENCODER_DIRECTION_FLIP

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* bootmagic row col assignment */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 2