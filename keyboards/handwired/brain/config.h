/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 James Smith <bronzegears@gmail.com> @klackygears


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
/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x3060
#define DEVICE_VER 0x0001
#define MANUFACTURER klackygears
#define PRODUCT Brain
#define DESCRIPTION A split ergonomic keyboard with sculpted shell

#define SPLIT_USB_DETECT

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

// wiring of each half

#define MATRIX_COL_PINS \
    { D1, D4, C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7, B1 }

#define MATRIX_COL_PINS_RIGHT \
    { B5, B4, E6, D7, C6, D4, D1 }

#define DIODE_DIRECTION COL2ROW

/* mouse config */
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

/* Set 0 if debouncing isn't needed */


/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0
#define EE_HANDS

//#define SPLIT_HAND_PIN B7

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Enables This makes it easier for fast typists to use dual-function keys */
#define PERMISSIVE_HOLD

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

#define RGBLED_NUM 28  // Number of LEDs


#define RGBLIGHT_LIMIT_VAL 120

#define RGBLIGHT_SPLIT

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

//#define PREVENT_STUCK_MODIFIERS
//#define TAPPING_TERM 150
//#define IGNORE_MOD_TAP_INTERRUPT
//#define TAPPING_FORCE_HOLD

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 6
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0
