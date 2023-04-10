/*
Copyright 2021 yushakobo

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
#define MATRIX_ROW_PINS       { D4, C6, D7, E6, B4, F4 }
#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS       { F5, F6, B2, B3, B1, F7, NO_PIN }
#define MATRIX_COL_PINS_RIGHT { F4, F5, F6, F7, B1, B3, B2 }

#define EE_HANDS

#ifdef RGB_DI_PIN
#    define RGBLIGHT_LED_MAP { 0, 1, 2, 3, 4, 5, 6, 8, 7, \//navpad side
                                   9, 10, 11, 12, 13, 14, \//helix side
                                  20, 19, 18, 17, 16, 15, \
                                  21, 22, 23, 24, 25, 26, \
                              33, 32, 31, 30, 29, 28, 27, \
                              34, 35, 36, 37, 38, 39, 40 }
#endif

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 9+32
#    define RGBLED_SPLIT { 9, 32 }
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 120 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
#endif

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 132
#define TAPPING_LAYER_TERM 90
