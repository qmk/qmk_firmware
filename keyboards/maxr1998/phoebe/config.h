/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Maxr1998
#define PRODUCT         Phoebe
#define DESCRIPTION     A 5x12 ortolinear keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12

/* Planck PCB default pin-out */
#define MATRIX_ROW_PINS { B7, B3, B2, B1, D6 }
#define MATRIX_COL_PINS { D7, B4, B5, B6, C6, C7, B0, F1, F4, F5, F6, F7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* RGB LED Setup */
#define RGB_DI_PIN          F0 // pin the DI on the WS2812B is hooked-up to
#define RGBLIGHT_ANIMATIONS    // run RGB animations
#define RGBLED_NUM          8  // number of LEDs

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
