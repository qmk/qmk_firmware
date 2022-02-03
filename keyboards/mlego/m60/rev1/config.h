/* Copyright 2021-2022 alin m elena <alinm.elena@gmail.com>
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

/* USB Device descriptor parameter */
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001

#define MATRIX_ROW_PINS \
    { A6, A7, B0, B1, B10 }
#define MATRIX_COL_PINS \
    { A10, A15, B3, B4, B5, B7, B6, A1, A2, A3, A4, A5 }

#define ENCODERS_PAD_A \
    { A0 }
#define ENCODERS_PAD_B \
    { B8 }

#define LED_NUM_LOCK_PIN B12
#define LED_SCROLL_LOCK_PIN B13
#define LED_CAPS_LOCK_PIN C13

#define RGB_DI_PIN B15

#define UNUSED_PINS
#define RGBLIGHT_LAYERS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define MATRIX_IO_DELAY 5

#define RGBLED_NUM 20
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
