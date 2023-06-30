/*
Copyright 2020 Takeshi Nishio

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


/* key matrix size */
// Same size for Jones' custom Round-Robin matrix.
#define MATRIX_ROWS 11
#define MATRIX_COLS 11

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
// Same pins for Jones' custom Round-Robin matrix.
#define MATRIX_ROW_PINS { D4, D7, C7, F1, F4, F5, D6, D5, E6, B0, B1 }
#define MATRIX_COL_PINS { D4, D7, C7, F1, F4, F5, D6, D5, E6, B0, B1 }

/* COL2ROW, ROW2COL*/
// No need to define DIODE_DIRECTION for Jones' custom Round-Robin matrix.
//#define DIODE_DIRECTION COL2ROW

/* Audio */
#ifdef AUDIO_ENABLE
  #define AUDIO_PIN C6
  #define AUDIO_PIN_ALT B7  // 2nd pin for simultaneous audio.
  #define AUDIO_CLICKY
#endif

  #define RGBLED_NUM 14 // Left(4) + Right(2) + Under(8)
  #define RGBLIGHT_LED_MAP {0,1,2,3,13,12,4,5,6,7,8,9,10,11} // Left --> Right --> Under
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  // #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  /*== Lighting Layers ==*/
  #define RGBLIGHT_LAYERS
  // #define RGBLIGHT_MAX_LAYERS 2
  #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status
  // #define RGBLIGHT_EFFECT_BREATHING
  // #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  // #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_KNIGHT
  // #define RGBLIGHT_EFFECT_CHRISTMAS
  // #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  // #define RGBLIGHT_EFFECT_RGB_TEST
  // #define RGBLIGHT_EFFECT_ALTERNATING

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
