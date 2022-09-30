/*
Copyright 2021 Koobaczech

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
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

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
#define MATRIX_ROW_PINS { D3, F7, F0, E6 }
#define MATRIX_COL_PINS { D2, F1, F4, F5, F6, C7, B6, B5, B4, D7, D6, D4, D5 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Audio Function */
#define AUDIO_CLICKY
#define AUDIO_PIN C6

/* Haptic feedback */
#define FB_ERM_LRA 0
#define FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
#define FB_LOOPGAIN 1 // For  Low:0, Medium:1, High:2, Very High:3
/* Motor settings */
#define RATED_VOLTAGE 3
#define V_PEAK 5

/*== all animations enabled ==*/
/* If RGBLIGHT_SLEEP defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGB_DI_PIN B3
#ifdef RGB_DI_PIN
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLED_NUM 10
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SLEEP
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 4

/* Indicator Led's*/
#define LED_CAPS_LOCK_PIN B0
#define LED_NUM_LOCK_PIN B1
#define LED_SCROLL_LOCK_PIN B2
#define LED_PIN_ON_STATE 0
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
