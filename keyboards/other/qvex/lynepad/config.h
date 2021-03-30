/*
Copyright 2020 KemoNine

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
#define VENDOR_ID       0x5156
#define PRODUCT_ID      0x4C50
#define DEVICE_VER      0x0001
#define MANUFACTURER    QVEX
#define PRODUCT         Lynepad

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 4

/* Basic matrix config */
#define MATRIX_ROW_PINS { C7, F7, F6}
#define MATRIX_COL_PINS { F0, F1, F4, F5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Encoders */
#define ENCODERS_PAD_A { D0, B5 }
#define ENCODERS_PAD_B { D1, D6 }

/* LEDs */
#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#undef RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 4
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 240
#endif

/* Definitions for encoder tilt/press support */
#define ENC_TILT_THRESHOLD 1
#define PIN_TW_SW D2 // Center
#define PIN_RJ_SW C6 // Center
#define PIN_RJ_DIR_A D4 // Up
#define PIN_RJ_DIR_B D7 // Left
#define PIN_RJ_DIR_C B6 // Down
#define PIN_RJ_DIR_D B4 // Right
