/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    ZealPC
#define PRODUCT         Zeal60
#define DESCRIPTION     Zeal60 (QMK Firmware)

// key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

// Zeal60 PCB default pin-out
#define MATRIX_ROW_PINS { F0, F1, F4, F6, F7 }
#define MATRIX_COL_PINS { F5, D5, B1, B2, B3, D3, D2, C7, C6, B6, B5, B4, D7, D6 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCING_DELAY 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// key combination for command
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

// disable debug print
//#define NO_DEBUG

// disable print
//#define NO_PRINT

// disable action features
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

// enable/disable LEDs based on layout
#define BACKLIGHT_USE_SPLIT_BACKSPACE 0
#define BACKLIGHT_USE_SPLIT_LEFT_SHIFT 0
#define BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 0
#define BACKLIGHT_USE_7U_SPACEBAR 0
#define BACKLIGHT_USE_ISO_ENTER 0
#define BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS 0

// disable backlight when USB suspended (PC sleep/hibernate/shutdown)
#define BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED 0

// disable backlight after timeout in minutes, 0 = no timeout
#define BACKLIGHT_DISABLE_AFTER_TIMEOUT 0

// These define which keys in the matrix are alphas/mods
// Used for backlight effects so colors are different for
// alphas vs. mods
// Each value is for a row, bit 0 is column 0
// Alpha=0 Mod=1
#define BACKLIGHT_ALPHAS_MODS_ROW_0 0b0010000000000001
#define BACKLIGHT_ALPHAS_MODS_ROW_1 0b0000000000000001
#define BACKLIGHT_ALPHAS_MODS_ROW_2 0b0001000000000001
#define BACKLIGHT_ALPHAS_MODS_ROW_3 0b0011000000000001
#define BACKLIGHT_ALPHAS_MODS_ROW_4 0b0011110000000111

#define USE_KEYMAPS_IN_EEPROM 1

#endif
