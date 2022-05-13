/*
Copyright 2020 Team Mechlovin

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
#define VENDOR_ID     0x4D4C // ML
#define PRODUCT_ID    0x8802
#define DEVICE_VER    0x0001
#define MANUFACTURER  Team.Mechlovin
#define PRODUCT       Infinity 88

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

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
#define MATRIX_ROW_PINS { A10, B13, B12, B11, C14, C15 }
#define MATRIX_COL_PINS { C13, B9, B4, B7, B8, B5, B6, A9, A5, A6, A7,B1, B2, B10, B3, B14, B15 }

#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN A3
#define LED_CAPS_LOCK_PIN A4

#define BACKLIGHT_PIN B0
#define BACKLIGHT_BREATHING
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 3

#define RGB_DI_PIN A15
#define RGBLED_NUM 26
#define RGBLIGHT_LIMIT_VAL 255
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
