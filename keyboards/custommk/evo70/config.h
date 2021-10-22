/* Copyright 2021 customMK
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
#define VENDOR_ID       0xF35B
#define PRODUCT_ID      0xFAB5
#define DEVICE_VER      0x0001
#define MANUFACTURER    customMK
#define PRODUCT         EVO70

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { D3, D2, F7, F6, F5, F0 }
#define MATRIX_COL_PINS { F1, F4, E6, B1, B7, B0, E2, D4, D6, D7, B4, B3, B6, C6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define BACKLIGHT_PIN B5

#define BACKLIGHT_LIMIT_VAL 255
#define BACKLIGHT_ON_STATE 0
#define BACKLIGHT_LEVELS 17
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

#define ENCODERS_PAD_A { C7 }
#define ENCODERS_PAD_B { D5 }
#define ENCODER_RESOLUTION 2
#define TAP_CODE_DELAY 10

#define RGB_DI_PIN B2
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
#define RGBLED_NUM 48
#define RGBLIGHT_LAYERS
#define RGBLIGHT_HUE_STEP 4
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 4
#define RGBLIGHT_LIMIT_VAL 128
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL + 4