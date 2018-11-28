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

#ifndef REV1_CONFIG_H
#define REV1_CONFIG_H


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    RGBKB
#define PRODUCT         Sol
#define DESCRIPTION     "An RGB, split, ortho-esque keyboard"


#define PREVENT_STUCK_MODIFIERS
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 150

#define USE_I2C
#define USE_SERIAL
#define USE_SERIAL_PD3

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
#define MATRIX_ROWS 12
#define MATRIX_ROW_PINS { C6, B6, B5, B4, D7, E6}

// wiring of each half
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, C7 }
// #define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4 } //uncomment this line and comment line above if you need to reverse left-to-right key order

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* ws2812 RGB LED */
#define RGB_DI_PIN B3
#define RGBLIGHT_TIMER
//#define RGBLED_NUM 12    // Number of LEDs. see ./keymaps/default/config.h
#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD

#define DRIVER_COUNT      2
#define DRIVER_LED_TOTAL  70
// #define RGB_MATRIX_KEYPRESSES
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 5

#ifdef LED_MIRRORED
  #define RGBLED_NUM 35
#else
  #define RGBLED_NUM 70
#endif

#define RGBLIGHT_RAINBOW_SWIRL_RANGE 1950

#ifdef IOS_DEVICE_ENABLE
  #define RGBLIGHT_LIMIT_VAL 40
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 40
#elif RGBLIGHT_FULL_POWER
  #define RGBLIGHT_LIMIT_VAL 255
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#else
  #define RGBLIGHT_LIMIT_VAL 120
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
#endif

#define RGBLIGHT_VAL_STEP (RGBLIGHT_LIMIT_VAL / 10)
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#define RGBLIGHT_ANIMATIONS

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value for Helix keyboard
//  120  RGBoff, OLEDoff
//  120  OLED
//  330  RGB 6
//  300  RGB 32
//  310  OLED & RGB 32
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
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION


#endif
