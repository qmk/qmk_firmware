/*
Copyright 2021-2022 Alin M Elena <alinm.elena@gmail.com>

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

#define LED_NUM_LOCK_PIN B12
#define LED_SCROLL_LOCK_PIN B13
#define LED_CAPS_LOCK_PIN C13

//                          0   1   2   3   4
#define MATRIX_ROW_PINS \
    { B10, A5, A6, A7, B0 }
//                         0    1   2   3   4   5   6   7   8    9  10  11   12
#define MATRIX_COL_PINS \
    { A10, A15, B3, B4, B5, B9, B8, B7, A1, A2, A3, A4, B1 }

#ifdef ENCODER_ENABLE
#define ENCODERS_PAD_A \
    { A0 }
#define ENCODERS_PAD_B \
    { B6 }
#define ENCODER_RESOLUTION 4
#endif

#ifdef RGBLIGHT_ENABLE

#define RGB_DI_PIN B15
#define RGBLIGHT_LAYERS
#undef RGBLED_NUM
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
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#endif

// you want to comment this if using stm32-dfu as bootloader
#define FEE_PAGE_BASE_ADDRESS 0x08008000
