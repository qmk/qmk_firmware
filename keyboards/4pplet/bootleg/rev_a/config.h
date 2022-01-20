/*
Copyright 2020 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#define PRODUCT_ID      0x0004
#define DEVICE_VER      0x0001
#define MANUFACTURER    4pplet
#define PRODUCT         bootleg Rev A

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
// ROWS: Top to bottom, COLS: Left to right
#define MATRIX_ROW_PINS {D0,C2,C4,D4,D2}
#define MATRIX_COL_PINS {C5,C6,C7,B7,B6,B5,B4,B3,B2,B1,B0,D6,D5,D3,D1}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define QMK_ESC_OUTPUT C4 // usually COL
#define QMK_ESC_INPUT D0 // usually ROW
