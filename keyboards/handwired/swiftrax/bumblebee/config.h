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
#define PRODUCT_ID      0xE881
#define DEVICE_VER      0x0001
#define MANUFACTURER    Swiftrax
#define PRODUCT         BumbleBee
/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { B0, B1, B2, B3, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { C7, D3, D5, D4, D6, D7, B4, B5 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Encoder */
#define ENCODERS_PAD_A { C6 }
#define ENCODERS_PAD_B { B6 }

/* RGB Indicators */
#define RGB_DI_PIN E6
#define RGBLED_NUM 3

/* Solenid Pin */
#define SOLENOID_PIN D2

/* Piezo Buzzer */
#define AUDIO_PIN B7