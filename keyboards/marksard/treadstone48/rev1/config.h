/*
Copyright 2020 marksard

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
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, B3, B2, B6 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
  #ifndef RS_EXTRA_LED
    #define RGBLED_NUM 12
    #define RGBLED_SPLIT {12, 0}
  #else
    #define RGBLED_NUM 32
    #define RGBLED_SPLIT {12, 20}
  #endif
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 180 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
//   #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//   #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
#endif

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
