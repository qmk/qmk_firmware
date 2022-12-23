/*
Copyright 2021 kb-elmo<mail@elmo.space>

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

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

/* Keyboard Matrix Assignments */

#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4, A5 }
#define MATRIX_COL_PINS { C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Status LEDs */
#define LED_CAPS_LOCK_PIN B6
#define LED_SCROLL_LOCK_PIN B5

/* RGB */
#define RGB_DI_PIN B8
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


#define RGBLED_NUM 16
#define RGBLIGHT_SLEEP
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
