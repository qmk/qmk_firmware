/*
Copyright 2020 LAZYDESIGNERS

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
#define VENDOR_ID       0x4C44 // "LD"
#define PRODUCT_ID      0x0061
#define DEVICE_VER      0x0001
#define MANUFACTURER    LAZYDESIGNERS
#define PRODUCT         Dimpleplus

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { B3, F0, E6, F4, F5 }
#define MATRIX_COL_PINS { F1, D5, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4 }

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B7
// #define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3

/* RBG underglow */
#define RGB_DI_PIN D2
#ifdef RGB_DI_PIN
	#define RGBLIGHT_ANIMATIONS
	#define RGBLIGHT_SLEEP
	#define RGBLED_NUM 8
	/* #define RGBLIGHT_HUE_STEP 8 */
	/* #define RGBLIGHT_SAT_STEP 8 */
	/* #define RGBLIGHT_VAL_STEP 8 */
#endif
