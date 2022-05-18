/* 
Copyright 2021 owlab

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

/* USB Device descriptor parameter*/
#define VENDOR_ID       0x4F53  //0x4F53 OS for owl studio
#define PRODUCT_ID      0x4A53  //0x4A4C JL for jelly, 0x4A53 JS for jelly solder
#define DEVICE_VER      0x0001 
#define MANUFACTURER    OwLab 
#define PRODUCT         Jelly Epoch

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B0, B1, B2, B3, A15, B10 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, B11, B8, B9, C13 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* NKRO */
#ifdef NKRO_ENABLE
#    define FORCE_NKRO
#endif

/* RGB Strip*/
#define RGB_DI_PIN B15
#ifdef RGB_DI_PIN
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLED_NUM 24
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 10
#    define RGBLIGHT_LIMIT_VAL 255    
#endif
