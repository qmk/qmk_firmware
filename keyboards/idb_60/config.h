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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x6060 // 24672
#define PRODUCT_ID   0x6060 // 24672
#define DEVICE_VER   0x0001
#define MANUFACTURER    pngu
#define PRODUCT         idb 60
#define DESCRIPTION     QMK keyboard firmware for idb 60

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *         ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROW_PINS { C2, D0, D1, D2, D3, D4, D5, D6, B0, B1 }
#define MATRIX_COL_PINS { B2, B3, B4, C6, B6, B7, C7, B5 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
#define BACKLIGHT_LEVELS 0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

/*
 * Magic Key Options
 *
 * Magic keys are hotkey commands that allow control over firmware functions of
 * the keyboard. They are best used in combination with the HID Listen program,
 * found here: https://www.pjrc.com/teensy/hid_listen.html
 *
 * The options below allow the magic key functionality to be changed. This is
 * useful if your keyboard/keypad is missing keys and you want magic key support.
 *
 */

/* control how magic key switches layers */
//#define MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS true
//#define MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS true
//#define MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM false

/* override magic key keymap */
//#define MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS
//#define MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS
//#define MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM
//#define MAGIC_KEY_HELP1     H
//#define MAGIC_KEY_HELP2     SLASH
//#define MAGIC_KEY_DEBUG     D
//#define MAGIC_KEY_DEBUG_MATRIX  X
//#define MAGIC_KEY_DEBUG_KBD   K
//#define MAGIC_KEY_DEBUG_MOUSE  M
//#define MAGIC_KEY_VERSION    V
//#define MAGIC_KEY_STATUS     S
//#define MAGIC_KEY_CONSOLE    C
//#define MAGIC_KEY_LAYER0_ALT1  ESC
//#define MAGIC_KEY_LAYER0_ALT2  GRAVE
//#define MAGIC_KEY_LAYER0     0
//#define MAGIC_KEY_LAYER1     1
//#define MAGIC_KEY_LAYER2     2
//#define MAGIC_KEY_LAYER3     3
//#define MAGIC_KEY_LAYER4     4
//#define MAGIC_KEY_LAYER5     5
//#define MAGIC_KEY_LAYER6     6
//#define MAGIC_KEY_LAYER7     7
//#define MAGIC_KEY_LAYER8     8
//#define MAGIC_KEY_LAYER9     9
//#define MAGIC_KEY_BOOTLOADER   PAUSE
//#define MAGIC_KEY_LOCK      CAPS
//#define MAGIC_KEY_EEPROM     E
//#define MAGIC_KEY_NKRO      N
//#define MAGIC_KEY_SLEEP_LED   Z

/*
 * Feature disable options
 * These options are also useful to firmware size reduction.
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

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// EEPROM usage

// TODO: refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x451F
#define EEPROM_MAGIC_ADDR 34
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x08
#define EEPROM_VERSION_ADDR 36

// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR 37
// Dynamic macro starts after dynamic keymaps (37+(4*10*6*2)) = (37+480)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 677    // **** CHANGE THIS BASED ON MATRIX_ROWS & MATRIX_COLS ****
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 347    // **** CHANGE THIS BASED ON 1024-DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR ****
#define DYNAMIC_KEYMAP_MACRO_COUNT 16
