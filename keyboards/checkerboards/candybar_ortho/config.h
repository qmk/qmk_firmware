/* Copyright 2021 Nathan Spears
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 #pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x7070
#define PRODUCT_ID      0x3215
#define DEVICE_VER      0x0001
#define MANUFACTURER    Nasp
#define PRODUCT         CandyBar Ortho

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 9

/* key matrix pins */
#define MATRIX_ROW_PINS { B4, D4, D7, D6, B5, B6, C7, C6 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, D0, D1, D2 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN B7
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 18
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
