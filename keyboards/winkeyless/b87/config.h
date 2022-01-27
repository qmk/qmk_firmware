/* Copyright 2021 Joah Nelson (Jels)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,   either version 2 of the License, or
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

/* USB Device descriptor paramater */
#define VENDOR_ID       0x20A0   // 
#define PRODUCT_ID      0x0B87  // B87
#define DEVICE_VER      0x0001
#define MANUFACTURER    Winkeyless
#define PRODUCT         B87 // QMK PORT

/* Define Matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 15

/*Define Matrix Pins */
#define MATRIX_ROW_PINS {B5, B4, B3, B2, B1, B0, B6, B7}
#define MATRIX_COL_PINS {A0, A1, A2, A3, A4, A5, C5, C4, C3, C2, D7, C6, C7, A7, A6}
    
#define RGBLED_NUM 20  // Number of LEDs
// RGB effects
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

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3

#define LED_CAPS_LOCK_PIN D1 
#define LED_SCROLL_LOCK_PIN D6 
