/*
Copyright 2022 Stefan Sundin "4pplet" <mail@4pplet.com>

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
#define VENDOR_ID       0x4444
#define PRODUCT_ID      0x0006
#define DEVICE_VER      0x0001
#define MANUFACTURER    4pplet
#define PRODUCT         waffling80 Rev A

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 8

// ROWS: Top to bottom, COLS: Left to right
#define MATRIX_ROW_PINS {C4,C5,B4,B3,B1,B0,D6,D5,D3,D4,D1,D2}
#define MATRIX_COL_PINS {C6,C7,B7,B6,B5,B2,D0,C2}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define QMK_ESC_OUTPUT C6 // usually COL
#define QMK_ESC_INPUT C4 // usually ROW

#define RGB_DI_PIN D7
#define RGBLED_NUM 2

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
