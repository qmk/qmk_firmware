/* Copyright 2021 DZTECH <moyi4681@live.cn>
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
#define VENDOR_ID       0x445A
#define PRODUCT_ID      0X1015
#define DEVICE_VER      0x0001
#define MANUFACTURER    dztech
#define PRODUCT         endless80

#define MATRIX_ROWS 6
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B7, B5 }
#define MATRIX_COL_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4, C6, C7, F5, F4, F1, F0 }
#define DIODE_DIRECTION COL2ROW

#define LED_PIN_ON_STATE 0
#define LED_CAPS_LOCK_PIN E6

#define RGB_DI_PIN F7
#ifdef RGB_DI_PIN
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
#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_EFFECT_RAINBOW_MOOD + 6) 
#define RGBLIGHT_DEFAULT_SPD 10
#define RGBLED_NUM 30
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_LIMIT_VAL 130 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#endif
#define DEBOUNCE 5