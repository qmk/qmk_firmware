/*
Copyright 2020 Swiftrax <swiftrax@gmail.com>

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
#define PRODUCT_ID      0xEB0E
#define DEVICE_VER      0x0001
#define MANUFACTURER    Swiftrax
#define PRODUCT         Pandamic

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { D1, D2, B5, B7, D3, D5, D6, D4, D7, B4 }
#define MATRIX_COL_PINS { B6, C6, C7, F7, F6, F5, F4, F1, F0, D0 }

#define ENCODERS_PAD_A { E6 }
#define ENCODERS_PAD_B { B0 }


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/*EEPROM for via*/
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
