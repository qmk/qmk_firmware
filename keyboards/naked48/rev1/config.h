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
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Salicylic_Acid
#define PRODUCT         naked48
#define DESCRIPTION     Ortholinear 48 Keys Keyboard

/* Use I2C or Serial */
//#define USE_I2C
#define USE_SERIAL
//#define USE_MATRIX_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// OLED support
//      see ./rules.mk: OLED_ENABLE=yes or no
#ifdef OLED_ENABLE
  #define SSD1306OLED
#endif

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 14

// Rows are doubled-up
#define MATRIX_ROW_PINS { D1, D0, D4, C6 }

// wiring of each half
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, D7, E6, B4, B5 }
// #define MATRIX_COL_PINS { B5, B4, E6, D7, D6, B2, B3, B1, F7, F6, F5, F4 } //uncomment this line and comment line above if you need to reverse left-to-right key order

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
#define RGB_DI_PIN D3
#define RGBLIGHT_TIMER
#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD

// naked48 keyboard RGB LED support
//#define RGBLIGHT_ANIMATIONS : see ./rules.mk: LED_ANIMATIONS = yes or no
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#define RGBLED_NUM 48

#ifndef IOS_DEVICE_ENABLE
  #define RGBLIGHT_LIMIT_VAL 180
  #define RGBLIGHT_VAL_STEP 17
#else
  #define RGBLIGHT_LIMIT_VAL 50
  #define RGBLIGHT_VAL_STEP 4
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value for naked48 keyboard
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
