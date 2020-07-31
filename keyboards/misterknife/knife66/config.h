/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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
#define VENDOR_ID       0xAC11
#define PRODUCT_ID      0x4172
#define DEVICE_VER      0x0001
#define MANUFACTURER    MisterKnife
#define PRODUCT         Knife66

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { B2, B1, B0, A7, A6, A5, A4, B9, B8, B7, B6, B5, B4, B3, A15 }
#define MATRIX_ROW_PINS { B15, A8, A3, A2, A1 }
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN A9

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
#define RGBLED_NUM 6
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 200
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5
