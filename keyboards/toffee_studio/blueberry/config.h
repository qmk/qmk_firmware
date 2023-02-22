/* Copyright 2023 Toffee Studio
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

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 8

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { E6, B0, B1, F6, F5, F1, F7, F0, F4 }
#define MATRIX_COL_PINS { B6, D4, D6, D7, B4, B5, C6, C7 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D0
#ifdef RGB_DI_PIN
#   define RGBLED_NUM 22

/* RGB LED logical order map */
/* Top->Bottom, Right->Left */
#define RGBLIGHT_LED_MAP {      \
  19, 18, 17, 16, 15, 14, 13, 12, 11,   \
  20,                             10,   \
  21,			                   9,   \
   0,  1,  2,  3,  4,  5,  6,  7,  8    }

/* The maximum brightness level up to 255 */
#define RGBLIGHT_LIMIT_VAL 192    //limited to 75% brightness
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_ALTERNATING
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
