/* Copyright 2022 lexbrugman
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

#define MATRIX_ROW_PINS { A10, A9, A8, B14, B13, A2 }
#define MATRIX_COL_PINS { A3, A4, A5, A6, A7, B0, B1, B2, B12, A15, B3, B4, B5, B6, B7, B8, C13, C14, C15, A0}

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B15

#ifdef RGB_DI_PIN
    #define RGBLED_NUM 4
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_BREATHING

    #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL

    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 180
    #define RGBLIGHT_SLEEP
#endif
