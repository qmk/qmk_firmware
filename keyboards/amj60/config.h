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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6066
#define DEVICE_VER      0x0001
#define MANUFACTURER    Han Chen
#define PRODUCT         AMJ60
#define DESCRIPTION     qmk port of AMJ60 PCB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { F7, F6, F5, F4, D5}
#define MATRIX_COL_PINS { F1, F0, E6, C7, C6, B0, D4, B1, B7, B5, B4, D7, D6, B3}
#define UNUSED_PINS

#define BACKLIGHT_PIN B6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Backlight configuration
 */
#define BACKLIGHT_LEVELS 4

/* Underlight configuration
 */

#define RGB_DI_PIN E2
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8     // Number of LEDs
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

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

#endif
