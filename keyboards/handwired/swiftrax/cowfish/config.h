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
#define PRODUCT_ID      0xEB53
#define DEVICE_VER      0x0001
#define MANUFACTURER    Swiftrax
#define PRODUCT         CowFish
#define DESCRIPTION     TKL with F13

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { D0, D1, B7, E6, D4, D6 }
#define MATRIX_COL_PINS { B3, B2, B1, F0, F1, F4, F5, F6, F7, B5, B6, B4, C6, D7, C7, D2, D3, D5}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/*EEPROM for via*/
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
