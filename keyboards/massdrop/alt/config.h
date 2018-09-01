/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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
#define VENDOR_ID           0x04D8
#define PRODUCT_ID          0xEED3
#define DEVICE_VER          0x0101

#define MANUFACTURER        "Massdrop Inc."
#define PRODUCT             "ALT Keyboard"
#define SERIAL_NUM          "Unavailable"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define PA 0
#define PB 1

#define MATRIX_ROW_PORTS PA, PA, PA, PA, PA
#define MATRIX_ROW_PINS   0,  1,  2,  3,  4

#define MATRIX_COL_PORTS PB, PB, PB, PB, PB, PB, PB, PB, PB, PB, PA, PA, PA, PA, PA
#define MATRIX_COL_PINS   4,  5,  6,  7,  8,  9, 10, 11, 12, 13,  5,  6,  7, 10, 11

/* Print boot debug codes using debug LED when M28 and M30 shorted */
#define DEBUG_BOOT_TRACING

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* Force boot in NKRO mode */
//#define FORCE_NKRO

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
