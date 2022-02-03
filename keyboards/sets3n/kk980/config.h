/* Copyright 2021 Sets3n
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
#define VENDOR_ID       0x404A
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    Sets3n
#define PRODUCT         kk980

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */

/* key matrix pins */
#define MATRIX_ROW_PINS { B2, B3, D3, D4, D5, D6 }
#define MATRIX_COL_PINS { E6, F0, F1, F4, F5, F6, F7, C7, C6, B6, B5, B4, D7, B1, B0, D0, D1 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 8
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

#define RGB_DI_PIN B7
#ifdef RGB_DI_PIN
#define RGBLED_NUM 102
#define RGBLIGHT_LED_MAP { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,\
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, \
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, \
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, \
	54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, \
	68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, \
	82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, \
	96, 97, 98, 99, 100, 101, 102 }	// 1 --> ScollLock 2 --> CapsLock 3 --> Bluetooth 4 --> NumLock
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 230
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#endif

#ifdef RGB_MATRIX_ENABLE
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGB_MATRIX_KEYPRESSES
#endif

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

