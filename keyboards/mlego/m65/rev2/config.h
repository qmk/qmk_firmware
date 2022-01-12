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

#define DEVICE_VER 0x0002
#define PRODUCT_ID 0x6060

#define LED_NUM_LOCK_PIN B12
#define LED_SCROLL_LOCK_PIN B13
#define LED_CAPS_LOCK_PIN B2

//                          0   1   2    3   4
#define MATRIX_ROW_PINS \
    { B11, B0, B1, A2, A3 }
//                         0    1   2   3   4   5   6   7   8    9  10  11   12
#define MATRIX_COL_PINS \
    { A10, A15, B3, B4, B5, B9, B8, B7, B6, C15, A0, A7, B10 }

#define ENCODERS_PAD_A \
    { A8 }
#define ENCODERS_PAD_B \
    { A9 }

#define RGB_DI_PIN B15

#define UNUSED_PINS
#define RGBLIGHT_LAYERS

#define ENCODER_RESOLUTION 4

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

#define EEPROM_PAGE_SIZE
#define FEE_PAGE_SIZE 0x800
#define FEE_PAGE_COUNT 4

#define FEE_MCU_FLASH_SIZE_IGNORE_CHECK
#define FEE_MCU_FLASH_SIZE                                \
    ({                                                    \
        uint16_t flash_size = *(uint16_t*)FLASHSIZE_BASE; \
        (flash_size <= 512) ? flash_size : 512;           \
    })
