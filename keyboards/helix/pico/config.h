/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2018 MakotoKurauchi

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

#define QUICK_TAP_TERM 0

#define SERIAL_SLAVE_BUFFER_LENGTH  ((MATRIX_ROWS)/2)
#define SERIAL_MASTER_BUFFER_LENGTH ((MATRIX_ROWS)/2)

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }

// wiring of each half
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }
// #define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4 } //uncomment this line and comment line above if you need to reverse left-to-right key order

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Audio */
#ifdef AUDIO_ENABLE
  #define AUDIO_PIN B5
#endif

// Helix keyboard RGB LED support
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#ifdef RGBLED_BACK
  #define RGBLIGHT_LED_COUNT 25
#else
  #define RGBLIGHT_LED_COUNT 6
#endif

#ifndef IOS_DEVICE_ENABLE
  #if RGBLIGHT_LED_COUNT <= 6
    #define RGBLIGHT_LIMIT_VAL 255
  #else
    #define RGBLIGHT_LIMIT_VAL 130
  #endif
  #define RGBLIGHT_VAL_STEP 17
#else
  #if RGBLIGHT_LED_COUNT <= 6
    #define RGBLIGHT_LIMIT_VAL 90
  #else
    #define RGBLIGHT_LIMIT_VAL 45
  #endif
  #define RGBLIGHT_VAL_STEP 4
#endif

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value for Helix keyboard
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
//  310  OLED & RGB 32
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
