/*
Copyright 2019 Evy Dekkers

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
#define VENDOR_ID       0x7353
#define PRODUCT_ID      0x0160
#define DEVICE_VER      0x0001
#define MANUFACTURER    Evyd13
#define PRODUCT         Lex60
#define DESCRIPTION     A 60% PCB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {D5,D4,B0,D2,D3}
#define MATRIX_COL_PINS {B7,F7,C7,E6,C6,F0,B6,F1,B5,F4,B4,F5,D7,F6,D6}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define QMK_ESC_OUTPUT B7 // usually COL
#define QMK_ESC_INPUT D5 // usually ROW

#define RGB_DI_PIN D1
#define RGBLED_NUM 12
#define RGBLIGHT_ANIMATIONS
