/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2021 @Yowkees

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
#define VENDOR_ID 0x5957  // "YW" = Yowkees
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001
#define MANUFACTURER Yowkees
#define PRODUCT Keyball

// rev.1 uses PMW3360 as optical sensor
#define PMW_3360

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6
#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7 }
#define MATRIX_COL_PINS \
    { D4, C6, D7, E6, B4, B5 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define SOFT_SERIAL_PIN D2

// Detect master/slave configuration by USB instead of VBUS.
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 500

#define SPLIT_TRANSACTION_IDS_KB GET_TRACKBALL_DATA

#define NO_I2C  // no need to compile i2c_slave.c

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

// RGB Light settings for Keyball46 hardware
#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM 14  // Number of LEDs
#    define RGBLED_SPLIT \
        { 7, 7 }
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

// KEYBALL46_TRACKBALL is defined for custom split transport. it will be used
// by rev1/ball and rev1/noball firmware.
#define KEYBALL46_TRACKBALL
