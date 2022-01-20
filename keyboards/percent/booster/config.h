/*
Copyright 2019 MechMerlin

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
#define VENDOR_ID       0x5053 /* PS */
#define PRODUCT_ID      0x4253
#define DEVICE_VER      0x0001
#define MANUFACTURER    Percent Studio
#define PRODUCT         Booster

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { D1, D6, D7, B4, B5 }
#define MATRIX_COL_PINS { C7, D4, D2, D0 }

#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 10
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 255
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_ANIMATIONS
#endif

