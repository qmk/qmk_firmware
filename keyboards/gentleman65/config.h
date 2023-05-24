/*
Copyright 2021 Omar Afzal

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
#define VENDOR_ID       0x00FA
#define PRODUCT_ID      0x2020
#define DEVICE_VER      0x0001
#define MANUFACTURER    JJ48_24 & Omar Afzal
#define PRODUCT         Gentleman 65

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* key matrix pins */
#define MATRIX_ROW_PINS { D3, D2, D1, F7, F1 }
#define MATRIX_COL_PINS { D4, D6, D7, B4, B5, B6, C6, D5, C7, F0, B2, B1, B3, B0, B7, D0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN F4
#define RGBLED_NUM 14
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

#define ENCODERS_PAD_A { F6 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTION 3

#define DRIVER_LED_TOTAL 14