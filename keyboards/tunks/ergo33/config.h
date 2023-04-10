/* Copyright 2020 Mika Kuitunen
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


/*
 * Keyboard Matrix Assignments
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
*/
#define MATRIX_ROW_PINS { F0, F1, B5, B4, D7 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, C7, C6, B6 }

#define DIODE_DIRECTION COL2ROW

/* Underglow + top RGB configuration */
#define RGB_DI_PIN D4
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

#if !defined(RGBLED_NUM)
/* RGB LED count
 * No external LED PCB: 10
 * External LED PCB: 14
 */
#    define RGBLED_NUM 14
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT
