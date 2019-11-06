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
#define MANUFACTURER    Yushakobo
#define PRODUCT         Helix Beta
#define DESCRIPTION     A split keyboard for the cheap makers

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

/* Use I2C or Serial */
#define USE_I2C
#define USE_SERIAL
//#define USE_MATRIX_I2C

/* Soft Serial defines */
#define SOFT_SERIAL_PIN D2
#define SERIAL_USE_MULTI_TRANSACTION

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
  #define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#else
  #define MATRIX_ROWS 10
  #define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#endif

// wiring of each half
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }
// #define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4 } //uncomment this line and comment line above if you need to reverse left-to-right key order

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

//#define RGBLED_NUM 12    // Number of LEDs. see ./keymaps/default/config.h

// Helix keyboard RGB LED support
//#define RGBLIGHT_ANIMATIONS : see ./rules.mk: LED_ANIMATIONS = yes or no
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#ifdef RGBLIGHT_ENABLE
#ifdef RGBLED_BACK
  #if MATRIX_ROWS == 8 // HELIX_ROWS == 4
    #define RGBLED_NUM 25
  #else
    #define RGBLED_NUM 32
  #endif
#else
  #define RGBLED_NUM 6
#endif

#ifndef IOS_DEVICE_ENABLE
  #if RGBLED_NUM <= 6
    #define RGBLIGHT_LIMIT_VAL 255
  #else
    #if MATRIX_ROWS == 8 // HELIX_ROWS == 4
      #define RGBLIGHT_LIMIT_VAL 130
    #else
      #define RGBLIGHT_LIMIT_VAL 120
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 17
#else
  #if RGBLED_NUM <= 6
    #define RGBLIGHT_LIMIT_VAL 90
  #else
    #if MATRIX_ROWS == 8 // HELIX_ROWS == 4
      #define RGBLIGHT_LIMIT_VAL 45
    #else
      #define RGBLIGHT_LIMIT_VAL 35
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 4
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#endif  // end of RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
  #if MATRIX_ROWS == 8 // HELIX_ROWS == 4
    #define RGBLED_NUM 50
    #error RGB_MATRIX_ENABLE does not yet support HELIX_ROWS == 4.
  #else
    #define RGBLED_NUM 64
  #endif
  #define DRIVER_LED_TOTAL RGBLED_NUM

  #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
//#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
//#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
  #define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
  #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
//#define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
//#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
  #define RGB_MATRIX_HUE_STEP 8
  #define RGB_MATRIX_SAT_STEP 8
  #define RGB_MATRIX_VAL_STEP 8
  #define RGB_MATRIX_SPD_STEP 10
#endif  // end of RGB_MATRIX_ENABLE

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

