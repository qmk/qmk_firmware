/*
Copyright 2018 monksoffunk

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
#define VENDOR_ID       0x04D8
#define PRODUCT_ID      0xEA3B
#define DEVICE_VER      0x0001
#define MANUFACTURER    25KEYS
#define PRODUCT         zinc rev.1

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
#define MATRIX_ROW_PINS { F6, F7, B1, B3 }

// wiring of each half
#define MATRIX_COLS 6
#define MATRIX_COL_PINS { F4, D4, C6, D7, E6, B4 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

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
