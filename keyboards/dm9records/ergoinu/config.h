/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2018 Takuya Urakawa<twitter:@hsgw>

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

/* USB Device descriptor parameter
   VID & PID are lisenced from microchip sublisence program, Don't use other project! */
#define VENDOR_ID       0x04D8
#define PRODUCT_ID      0xEE60
#define DEVICE_VER      0x0001
#define MANUFACTURER    Dm9Records
#define PRODUCT         ergoinu

#define USE_SERIAL

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2 }

// wiring of each half
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { B4, E6, D7, C6, D4, F5, F4 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN B6

#define RGBLED_NUM 7

#ifndef IOS_DEVICE_ENABLE
  #if RGBLED_NUM <= 7
    #define RGBLIGHT_LIMIT_VAL 255
    #define RGBLIGHT_VAL_STEP 17
  #endif
#else
  #define RGBLIGHT_LIMIT_VAL 90
  #define RGBLIGHT_VAL_STEP 4
#endif

#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
  #define USB_MAX_POWER_CONSUMPTION 500
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
