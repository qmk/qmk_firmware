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

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_LED_COUNT RGBLED_NUM
#define RGB_MATRIX_KEYPRESSES
#endif
