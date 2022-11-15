/* Copyright 2022 JasonRen(biu)
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
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

#define MATRIX_COL_PINS { C13, C14, C15, A3,   A4,  A5,  A6,  B12, B13, B14, B15,  A8,  A9, A10, B8 }
#define MATRIX_ROW_PINS { B0,  B1,  B2,  B10,  B11, B9 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 4
#    define RGBLIGHT_LIMIT_VAL 180

#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL

#   define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#   define WS2812_PWM_CHANNEL 2     // default: 2
#   define WS2812_PWM_PAL_MODE 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#   define WS2812_DMA_CHANNEL 3

#endif
