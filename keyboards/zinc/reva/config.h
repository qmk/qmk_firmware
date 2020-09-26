/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x9991
#define DEVICE_VER      0x0001
#define MANUFACTURER    monksoffunk
#define PRODUCT         zinc rev.A
#define DESCRIPTION     A split keyboard

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

/* Use I2C or Serial */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

/* Select hand configuration */
#define MASTER_LEFT
//#define MASTER_RIGHT
//#define EE_HANDS

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }

// wiring of each half
#define MATRIX_COLS 6
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3}

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

// RGB LED support
//#define RGBLIGHT_ANIMATIONS : see ./rules.mk: LED_ANIMATIONS = yes or no
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_SPLIT
  #ifdef RGBLED_BACK
    #ifdef RGBLED_CONT
      #define RGBLED_NUM 48
      #define RGBLED_SPLIT { 24, 24 }
    #else
      #define RGBLED_NUM 24
    #endif
  #else
    #ifdef RGBLED_BOTH
      #ifdef RGBLED_CONT
        #define RGBLED_NUM 60
        #define RGBLED_SPLIT { 30, 30 }
//      #define RGBLIGHT_LED_MAP {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29}
      #else
        #define RGBLED_NUM 30
      #endif
    #else
      #ifdef RGBLED_CONT
        #define RGBLED_NUM 12
        #define RGBLED_SPLIT { 6, 6 }
      #else
        #define RGBLED_NUM 6
      #endif
    #endif
  #endif
#endif

#ifndef IOS_DEVICE_ENABLE
  #if (RGBLED_NUM <= 6) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 12))
    #define RGBLIGHT_LIMIT_VAL 255
  #else
    #if (RGBLED_NUM <= 16) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 32))
      #define RGBLIGHT_LIMIT_VAL 130
    #else
      #define RGBLIGHT_LIMIT_VAL 120
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 17
#else
  #if (RGBLED_NUM <= 6) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 12))
    #define RGBLIGHT_LIMIT_VAL 90
  #else
    #if (RGBLED_NUM <= 16) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 32))
      #define RGBLIGHT_LIMIT_VAL 45
    #else
      #define RGBLIGHT_LIMIT_VAL 35
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 4
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
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
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
