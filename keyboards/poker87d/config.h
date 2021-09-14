/* Copyright 2021 water <mfkiiyd@163.com>
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
#define VENDOR_ID       0x6D66 // "mf" - mfkiiyd
#define PRODUCT_ID      0x087D // "87D"
#define DEVICE_VER      0x0001
#define MANUFACTURER    mfkiiyd
#define PRODUCT         POKER-87D Hotswap

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { E6, B7, D4, F0, D6, D7 }
#define MATRIX_COL_PINS { D1, D0, F7, F6, F5, D5, D3, D2, C7, C6, B5, F4, F1, B4, B0 }

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B6
// #define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 125
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 180 /* The maximum brightness level */
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
    #define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
//     #define RGBLIGHT_EFFECT_BREATHING
//     #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//     #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//     #define RGBLIGHT_EFFECT_SNAKE
//     #define RGBLIGHT_EFFECT_KNIGHT
//     #define RGBLIGHT_EFFECT_CHRISTMAS
//     #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//     #define RGBLIGHT_EFFECT_RGB_TEST
//     #define RGBLIGHT_EFFECT_ALTERNATING
#endif

#define LED_NUM_LOCK_PIN B1
#define LED_CAPS_LOCK_PIN B3
#define LED_SCROLL_LOCK_PIN B2
