/*
Copyright 2017 Ruari Armstrong <ukkeyboards@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x554B /* Ascii */
#define PRODUCT_ID      0x004E
#define DEVICE_VER      0x0002
#define MANUFACTURER    UK Keyboards
#define PRODUCT         UK78
#define DESCRIPTION     QMK keyboard firmware for UK78

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 19

/* key matrix pins */
#define MATRIX_ROW_PINS { F3, F2, F1, F0, A0 }
#define MATRIX_COL_PINS { A2, A1, F5, F4, E6, E7, E5, E4, B7, D0, D1, D2, D3, D4, D5, D6, D7, B5, E0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#define BACKLIGHT_PIN B6
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812b options */
#define RGB_DI_PIN F6
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 20
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#endif
