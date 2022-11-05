/*
Copyright 2019 Thomas Baart

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
#define MATRIX_ROWS  4
#define MATRIX_COLS  3

/*
 * Keyboard Matrix Assignments
 */
#define DIRECT_PINS { \
    { C6, D6, D5 }, \
    { C7, F7, D4 }, \
    { E6, F5, F6 }, \
    { F0, F1, F4 }, \
}

#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { D7 }

// #define QMK_ESC_OUTPUT B7
// #define QMK_ESC_INPUT C6
// #define QMK_SPEAKER B6

#define AUDIO_PIN B6
#define AUDIO_CLICKY
#define NO_MUSIC_MODE

#define RGB_DI_PIN         B5
#define RGBLED_NUM         5
#define RGBLIGHT_HUE_STEP  8
#define RGBLIGHT_SAT_STEP  8
#define RGBLIGHT_VAL_STEP  8
#define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#define RGBLIGHT_SLEEP         /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE           5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

#define FB_ERM_LRA         0
#define FB_BRAKEFACTOR     3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define FB_LOOPGAIN        1 /* For  Low:0, Medium:1, High:2, Very High:3 */

/* Please refer to your datasheet for the optimal setting for your specific motor. */
#define RATED_VOLTAGE      3
#define V_PEAK             5

#define DRV_GREETING       alert_750ms
#define DRV_MODE_DEFAULT   buzz
// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2
