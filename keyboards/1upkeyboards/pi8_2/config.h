/* Copyright 2022 ziptyze
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
#define MATRIX_ROWS 2
#define MATRIX_COLS 6

#define VENDOR_ID    0x6F75
#define PRODUCT_ID   0x5601
#define DEVICE_VER   0x0001
#define MANUFACTURER 1upkeyboards
#define PRODUCT      pi8_2

/* Keyboard Matrix Assignments */
// clang-format off
#define DIRECT_PINS { \
     { GP29,    GP2,    GP3,    GP4,    GP5,    GP1 }, \
     { NO_PIN,  GP8,    GP9,   GP10,   GP11, NO_PIN }  \
}
// clang-format on

/* Encoders */
#define ENCODERS_PAD_A { GP16 }
#define ENCODERS_PAD_B { GP17 }

#define DEBOUNCE 5

#define RGB_DI_PIN GP0
#define RGBLED_NUM 16
#define NOP_FUDGE 0.4

#ifdef RGBLIGHT_ENABLE
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
#endif