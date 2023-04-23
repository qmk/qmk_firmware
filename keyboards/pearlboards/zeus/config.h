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
#define MATRIX_ROW_PINS { F0, C1, E1, E0, D7, D6 }
#define MATRIX_COL_PINS { F1, F2, F3, F4, F5, F6, F7, A0, A1, A2, A3, A4, A5, A6, A7, C7, C2, C0 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Audio Function */
#define AUDIO_CLICKY
#define AUDIO_PIN C6
#ifdef AUDIO_ENABLE
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10
#endif

/* Haptic feedback */
#define FB_ERM_LRA 0
#define FB_BRAKEFACTOR 1 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
#define FB_LOOPGAIN 3 // For  Low:0, Medium:1, High:2, Very High:3
/* Motor settings */
#define RATED_VOLTAGE 2
#define V_PEAK 5

/*== all animations enabled ==*/
/* If RGBLIGHT_SLEEP defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGB_DI_PIN D5
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
#define RGBLED_NUM 2
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
