/*
Copyright 2017 Balz Guenat

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
#define VENDOR_ID       0x4853
#define PRODUCT_ID      0x980C
#define DEVICE_VER      0x0100
#define MANUFACTURER    Hasu
#define PRODUCT         FC980C

/* Maximum dynamic keymap layers (constrained by EEPROM space) */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

// #define MATRIX_ROW_PINS { B0, B2, B4, B5, B6 }
// #define MATRIX_COL_PINS { F5, B1, F0, F1, F4, B3, D7, D6, D4, D5, D3, D2, D1, D0 }
// #define UNUSED_PINS

//#define DIODE_DIRECTION

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS  1

/* mapping backlight LEDs to correct Pin */
// #define BACKLIGHT_PIN B7

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE  0

#define LED_NUM_LOCK_PIN B4
#define LED_CAPS_LOCK_PIN B5
#define LED_SCROLL_LOCK_PIN B6

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

#define USE_I2C

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// higher value means deeper actuation point, less sensitive
// be careful and only make small adjustments (steps of 1 or 2).
// too high and keys will fail to actuate. too low and keys will actuate spontaneously.
// test all keys before further adjustment.
// this should probably stay in the range +/-5.
// #define ACTUATION_DEPTH_ADJUSTMENT 0
