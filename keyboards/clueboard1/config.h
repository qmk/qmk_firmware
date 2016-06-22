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
#define VENDOR_ID       0xC1ED
#define PRODUCT_ID      0x2301
#define DEVICE_VER      0x0003
#define MANUFACTURER    Clueboard
#define PRODUCT         Clueboard
#define DESCRIPTION     QMK keyboard firmware for Clueboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

// ROWS: Top to bottom, COLS: Left to right
/* Column pin configuration
* col: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
* pin: B3 F1 F4 F5 F6 C7 C6 B6 B5 B4 D7 D6 D4 F7 B0 B1
*/
#define MATRIX_COL_PINS { B3, F1, F4, F5, F6, C7, C6, B6, B5, B4, D7, D6, D4, F7, B0, B1 }
/* Row pin configuration
* row: 0  1  2  3  4
* pin: D1 D0 D2 D5 D3
*/
#define MATRIX_ROW_PINS { D1, D0, D2, D5, D3 }
#define UNUSED_PINS

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

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* Underlight configuration
 */
 #define ws2812_PORTREG PORTB
 #define ws2812_DDRREG DDRB
 #define ws2812_pin 2
 #define RGBLED_NUM 14     // Number of LEDs
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
