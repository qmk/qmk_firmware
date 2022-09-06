/*
Copyright 2020 Jan Christoph Ebersbach

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

#define PRODUCT_ID      0x3536
#define DEVICE_VER      0x0003
#define PRODUCT         Dactyl-Manuform (5x6+2)
// #define PRODUCT         Dactyl-Manuform (5x6+2) BLE

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
// ../../../../docs/proton_c_conversion.md

// left half pro-mirco
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2, B6 }

// // right half adafruit feather
// #define MATRIX_COL_PINS { F1, F0, B1, B2, B3, D2 }
// #define MATRIX_ROW_PINS { D6, B7, B6, B5, D7, C6 }
// #define AdafruitBleResetPin D4
// #define AdafruitBleCSPin    B4
// #define AdafruitBleIRQPin   E6

#define DIODE_DIRECTION COL2ROW

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

// WS2812 RGB LED strip input and number of LEDs
// #define RGB_DI_PIN D3
// #define RGBLED_NUM 12

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3
