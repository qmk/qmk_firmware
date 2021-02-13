/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
#define VENDOR_ID       0x4705
#define PRODUCT_ID      0xA71C
#define DEVICE_VER      0x0003
#define MANUFACTURER    Evyd13
#define PRODUCT         Wonderland

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {B0,D1,D2,D3,D5}
#define MATRIX_COL_PINS {F0,F1,F4,F5,F6,F7,E6,C7,C6,B6,B5,B4,D7,D6,D4}
#define UNUSED_PINS


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Backlight configuration
 */
#define RGB_DI_PIN B7
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12

#define QMK_ESC_OUTPUT F0 // usually COL
#define QMK_ESC_INPUT B0 // usually ROW
#define QMK_LED B1
