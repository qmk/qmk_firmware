/* Copyright 2020 MelGeek <melgeek001365@gmail.com>
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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { F0, F1, F4, F5, F6 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B6, B5, B4, D7, D6, D4, D5, F7, D2, D1, D0 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN C7  
#define LED_PIN_ON_STATE  0

#define BACKLIGHT_PIN B7

#define RGB_DI_PIN    C6

#ifdef  BACKLIGHT_PIN
#	define BACKLIGHT_LEVELS    10
#	define BACKLIGHT_ON_STATE  1 
#	define BACKLIGHT_LIMIT_VAL 255
#endif

#ifdef RGB_DI_PIN
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_EFFECT_RAINBOW_MOOD + 6) 
#    define RGBLIGHT_DEFAULT_SPD 10
#	 define RGBLED_NUM        16
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SLEEP
#endif
