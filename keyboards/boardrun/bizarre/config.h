/*
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
#define VENDOR_ID       0xCDCD
#define PRODUCT_ID      0x5339
#define DEVICE_VER      0x0001
#define MANUFACTURER    shensmobile
#define PRODUCT         Boardrun Bizarre

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROW_PINS { F0, F1, F4, F5, F6 }
#define MATRIX_COL_PINS { F7, C7, C6, B6, B5, B4, D7, D6, D4, D5, D3, D2, D1, D0, B3, B2, B1 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

// #define BACKLIGHT_PIN F5
// #define BACKLIGHT_LEVELS 6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 10

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

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

// ws2812 options
#define RGB_DI_PIN B7 // pin the DI on the ws2812 is hooked-up to
#define RGBLIGHT_ANIMATIONS // run RGB animations
#define RGBLED_NUM 15 // number of LEDs
#define RGBLIGHT_HUE_STEP 12 // units to step when in/decreasing hue
#define RGBLIGHT_SAT_STEP 25 // units to step when in/decresing saturation
#define RGBLIGHT_VAL_STEP 12 // units to step when in/decreasing value (brightness)
