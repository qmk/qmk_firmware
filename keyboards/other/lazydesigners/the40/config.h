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
#define PRODUCT_ID      0x0042
#define DEVICE_VER      0x0001
#define MANUFACTURER    LAZYDESIGNERS
#define PRODUCT         THE40

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { D0, D1, B6, F5 }
#define MATRIX_COL_PINS { F4, F6, F7, B5, B4, D7, D6, D4, D5, D3, D2, B0 }

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B7
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3

#define RGB_DI_PIN C7
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 8
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_SLEEP 
    #define RGBLIGHT_ANIMATIONS
#endif
