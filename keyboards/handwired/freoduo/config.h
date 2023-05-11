/*
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


/* wiring of each half */
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { B2, B6, F6, B3, B1, F7 }
#define EE_HANDS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* ws2812 RGB LED */
#define RGB_DI_PIN D4
#if !defined(RGBLED_NUM)
#    define RGBLED_NUM 30
#    define RGBLIGHT_SPLIT
#    define RGBLED_SPLIT { 16, 14 }
// Switch RGB sides with LED MAP.
#    define RGBLIGHT_LED_MAP { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}
#    define RGBLIGHT_LAYERS
#endif
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
#define RGBLIGHT_SLEEP
#define RGBLIGHT_HUE_STEP 16
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
