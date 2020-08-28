/*
Copyright 2018 Cole Markham

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0x2328
#define DEVICE_VER      0x0205
#define MANUFACTURER    K.T.E.C.
#define PRODUCT         Staryu
#define DESCRIPTION     5-key macropad

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/* key matrix pins */
#define DIRECT_PINS { \
    { NO_PIN, D0,     D1 }, \
    { D4,     D3,     D2 }, \
}
#define UNUSED_PINS

#define RGB_DI_PIN C6
#define RGBLED_NUM 1     // Number of LEDs
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 200
// #ifdef RGB_DI_PIN
//   #define RGBLIGHT_HUE_STEP 8
//   #define RGBLIGHT_SAT_STEP 8
//   #define RGBLIGHT_VAL_STEP 8
//   #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
//   #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
// /*== all animations enable ==*/
//   #define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
//   #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//   #define RGBLIGHT_EFFECT_SNAKE
//   #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
// #endif

#undef BACKLIGHT_PIN
#define BACKLIGHT_PINS { C2, C7, D5, D6, B0 }
#define BACKLIGHT_LED_COUNT 5
#define BACKLIGHT_LEVELS 10

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1
