/* Copyright 2022 ItsFiremanSam

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

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

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
/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { E6, D7, B1, B3 }, \
    { B5, B4, B2, B6 } \
}

#define RGB_DI_PIN D3                   // LED data pin on controller
#define RGBLED_NUM 4                    // Number of LEDs connected

#define RGBLIGHT_HUE_STEP 10            // The number of steps to cycle through the hue by
#define RGBLIGHT_SAT_STEP 17            // The number of steps to increment the saturation by
#define RGBLIGHT_VAL_STEP 17            // The number of steps to increment the brightness by
#define RGBLIGHT_LIMIT_VAL 255          // Max brightness level
#define RGBLIGHT_SLEEP                  // RGB will switch off when host goes to sleep

#define RGBLIGHT_EFFECT_BREATHING       // Enable all additional RGB animation modes
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

#define OLED_TIMEOUT 20000              // Turns off OLED after said amount of milliseconds
#define OLED_BRIGHTNESS 128
#define OLED_DISPLAY_128X64


/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 0
