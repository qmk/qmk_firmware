/*
Copyright 2020 Holten Campbell

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


/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D2, D6, B4, F1, E6, F0, F4, B5, D7, D3 }
#define MATRIX_COL_PINS { F5, F6, F7, C7, C6, B6, B7, B3, D1, D0 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D4
#define RGBLED_NUM 10
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

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
