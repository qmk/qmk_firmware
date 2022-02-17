/* Copyright 2020 Muhammad Galib (polycarbdiet) <pd.keyboards@gmail.com>

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
#define VENDOR_ID    0x5040 // PD = polycarbdiet
#define PRODUCT_ID   0x7320 // S20
#define DEVICE_VER   0x0001
#define MANUFACTURER polycarbdiet
#define PRODUCT      S20

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

//                         1   2   3   4   5
#define MATRIX_ROW_PINS { B7, E6, D0, D1, D5 }
#define MATRIX_COL_PINS { C6, C7, D4, D6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING

#define RGB_DI_PIN B3
#define RGBLED_NUM 4
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */

#define RGBLIGHT_ANIMATIONS

#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define FORCE_NKRO
