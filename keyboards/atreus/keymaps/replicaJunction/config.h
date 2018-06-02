/*
Config file - Atreus QMK with replicaJunction layout

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
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Technomancy
#define PRODUCT         Atreus
#define DESCRIPTION     q.m.k. keyboard firmware for Atreus

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

// Change this to how you wired your keyboard
// COLS: Left to right, ROWS: Top to bottom
#if defined(ATREUS_ASTAR)
#   define MATRIX_ROW_PINS { D0, D1, D3, D2 }
#   define MATRIX_COL_PINS { D7, C6, B5, B4, E6, D4, B6, F6, F7, D6, B7 }
#   define UNUSED_PINS
#elif defined(ATREUS_TEENSY2)
#   define MATRIX_ROW_PINS { D0, D1, D2, D3 }
#   define MATRIX_COL_PINS { F6, F5, F4, B7, B6, B5, B4, B3, B2, B1, B0 }
#   define UNUSED_PINS
#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
//#define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
// Default: 5
#define DEBOUNCING_DELAY 6

// I don't have any locking keys, so I don't need these features

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* Prevent modifiers from sticking when switching layers */
#define PREVENT_STUCK_MODIFIERS

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
