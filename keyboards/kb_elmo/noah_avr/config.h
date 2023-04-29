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


/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B4, B6, D7, D5, D0 }
#define MATRIX_COL_PINS { D1, D2, D3, D4, C6, C7, F7, F6, F5, F4, F0, F1, B3, B2, B1, B0 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* RGB */
#define RGB_DI_PIN B5
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
#define RGBLED_NUM 7
#define RGBLIGHT_SLEEP // RGB will turn off when PC is put to sleep
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_BGR // RGB on the Noah is different order
