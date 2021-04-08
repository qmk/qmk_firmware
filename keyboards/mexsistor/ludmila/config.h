/*
Copyright 2020 Kevin M.

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
#define VENDOR_ID    0x69CC
#define PRODUCT_ID   0x6BF6
#define DEVICE_VER   0x0001
#define MANUFACTURER Kevin M.
#define PRODUCT      Ludmila Macropad

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 2

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { F0, C7, F7 }
#define MATRIX_COL_PINS { F4, F1 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D1
#define RGBLED_NUM 4
#define RGBLIGHT_SLEEP
#define RGBLIGHT_ANIMATIONS

// Encoder
#define ENCODERS_PAD_A { F6 }
#define ENCODERS_PAD_B { F5 }
