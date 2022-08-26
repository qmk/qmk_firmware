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
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

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
#define MATRIX_ROW_PINS { D6, E1, C0, C4, E3 }
#define MATRIX_COL_PINS { D5, D4, C1, C2, C3, C5, C7, A7, A6, A5, A4, A3, A2, A1, A0, F7 }
#define UNUSED_PINS { E4, E5, E6, E7, F0, F1, F2, F3, B0, B4, B5, B7 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Encoder Function */
#define ENCODERS_PAD_A { E0 }
#define ENCODERS_PAD_B { D7 }
//#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 1

/* Audio Function */
#define AUDIO_CLICKY
#define AUDIO_PIN C6

/* Haptic feedback */
#define FB_ERM_LRA 0
#define FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
#define FB_LOOPGAIN 3 // For  Low:0, Medium:1, High:2, Very High:3
/* Motor settings */
#define RATED_VOLTAGE 3
#define V_PEAK 5

/*== all animations enabled ==*/
/* If RGBLIGHT_SLEEP defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGB_DI_PIN B6
#ifdef RGB_DI_PIN
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLED_NUM 8
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Indicator Led's*/
#define LED_CAPS_LOCK_PIN F4
#define LED_NUM_LOCK_PIN F5
#define LED_SCROLL_LOCK_PIN F6
#define LED_PIN_ON_STATE 0
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
