/*
Copyright 2021 kuriatsu <kuriatsubayashi712@gmail.com>

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
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER kuriatsu
#define PRODUCT      tsubasa

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// #define EE_HANDS
#define MASTER_RIGHT
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
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define SOFT_SERIAL_PIN D3  // or D1, D2, D3, E6

#define RGB_DI_PIN D2
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 12
#    define RGBLIGHT_SPLIT
#    define RGBLED_SPLIT {6, 6}
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 1
#    define RGBLIGHT_VAL_STEP 1
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
// #    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }

#define SPLIT_WPM_ENABLE
#define SPLIT_TRANSPORT_MIRROR
