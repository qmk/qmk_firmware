/* Copyright 2021 MechBrewery
 * Author: tuananhnguyen204 (https://github.com/AnthonyNguyen168) (tuananhnguyen204@gmail.com)
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
#define VENDOR_ID       0x4252	//BR
#define PRODUCT_ID      0x3635	//65
#define DEVICE_VER      0x0001
#define MANUFACTURER    MechBrewery
#define PRODUCT         MB65S

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { B7, D0, F0, F1, F4 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, D1, D2, D3, D6, D7, B4, B6, C6, C7, F7, F6, F5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debouncing reduces chatter */
#define DEBOUNCE 5

/* indicators */
#define LED_CAPS_LOCK_PIN D4
#define LED_PIN_ON_STATE 0

/* number of backlight levels */
#define BACKLIGHT_PIN B5
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif


#define RGB_DI_PIN E2
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
#define RGBLED_NUM 16
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 240
#define RGBLIGHT_SLEEP
#endif
