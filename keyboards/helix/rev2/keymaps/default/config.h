/*
This is the c configuration file for the keymap

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Use I2C or Serial */

#define USE_I2C
#define USE_SERIAL
//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// Helix keyboard OLED support
//      see ./rules.mk: OLED_ENABLE=yes or no
#ifdef OLED_ENABLE
  #define SSD1306OLED
#endif

/* Select rows configuration */
// Rows are 4 or 5
// #define HELIX_ROWS 5 see ./rules.mk

/* key matrix size */
// Rows are doubled-up
#if  HELIX_ROWS == 4
  #define MATRIX_ROWS 8
  #define MATRIX_COLS 7
  #define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#elif HELIX_ROWS == 5
  #define MATRIX_ROWS 10
  #define MATRIX_COLS 7
  #define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#else
  #error "expected HELIX_ROWS 4 or 5"
#endif

#define USE_SERIAL_PD2

#define PREVENT_STUCK_MODIFIERS
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

// Helix keyboard RGB LED support
//#define RGBLIGHT_ANIMATIONS : see ./rules.mk: LED_ANIMATIONS = yes or no
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#ifdef RGBLED_BACK
  #if HELIX_ROWS == 4
    #define RGBLED_NUM 25
  #elif HELIX_ROWS == 5
    #define RGBLED_NUM 32
  #endif
#else
  #define RGBLED_NUM 6
#endif

#ifndef IOS_DEVICE_ENABLE
  #if RGBLED_NUM <= 6
    #define RGBLIGHT_LIMIT_VAL 255
  #else
    #if HELIX_ROWS == 5
      #define RGBLIGHT_LIMIT_VAL 120
    #else
      #define RGBLIGHT_LIMIT_VAL 130
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 17
#else
  #if RGBLED_NUM <= 6
    #define RGBLIGHT_LIMIT_VAL 90
  #else
    #if HELIX_ROWS == 5
      #define RGBLIGHT_LIMIT_VAL 35
    #else
      #define RGBLIGHT_LIMIT_VAL 45
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 4
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value for Helix keyboard
//  120  RGBoff, OLEDoff
//  120  OLED
//  330  RGB 6
//  300  RGB 32
//  310  OLED & RGB 32
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif

#endif /* CONFIG_USER_H */
