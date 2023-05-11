/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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


#define DIODE_DIRECTION COL2ROW

#ifdef LFK_TKL_REV_A
/* RevB Matrix config */
    #define MATRIX_ROWS 6
    #define MATRIX_COLS 17
    #define MATRIX_ROW_PINS {D2, D3, D4, D5, D6, D7 }
    #define MATRIX_COL_PINS {A0, A1, A2, A3, A4, A5, A6, A7, E6, E7,\
                             F0, F1, F2, F3, C0, C1, C2 }
    #define RGBLED_NUM 25     // Number of LEDs
#else
/* RevC/D Matrix config */
    #define MATRIX_ROWS 7
    #define MATRIX_COLS 16
    #define MATRIX_ROW_PINS {F2, D7, D6, D5, D4, D3, F3}
    #define MATRIX_COL_PINS {A0, A1, A2, A3, A4, A5, A6, A7, C7, C1, C0, E1, E0, C2, C3, C4}
    #define RGBLED_NUM 24     // Number of LEDs
#endif

#define AUDIO_VOICES
#define AUDIO_PIN C6

#define BACKLIGHT_PWM_MAP {2, 4, 8, 16, 40, 55, 70, 128, 200, 255}

#define RGB_DI_PIN F4  // Have to set it to something to get the ws2812 code to compile
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
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define TAPPING_TERM 200

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

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
