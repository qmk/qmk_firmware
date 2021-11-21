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
#define VENDOR_ID       0x4245  //BE
#define PRODUCT_ID      0x544C  //TL
#define DEVICE_VER      0x0001
#define MANUFACTURER    Bathroom Epiphanies
#define PRODUCT         tiger_lily

/*
 * Frosty Flake Rev. 20140521 made by Bathroom Ephiphanies
 * Ported from the Bathroom Epiphanies TMK Firmware:
 * https://github.com/BathroomEpiphanies/epiphanies_tmk_keyboard/tree/master/be_controllers
 *
 */

/* key matrix size */
#define MATRIX_ROWS 8   // Row0 - Row7 in the schematic
#define MATRIX_COLS 18  // ColA - ColR in the schematic

/*
 * Keyboard Matrix Assignments
 *
 * MATRIX_ROW_PINS and MATRIX_COL_PINS aren't actually used and are included
 * for data driven compatibility.
 */
#define MATRIX_ROW_PINS { C2, B3, B4, B2, B1, C7, B6, B5 }
#define MATRIX_COL_PINS { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }
#define UNUSED_PINS { B0, C4, D3 }

#define LED_NUM_LOCK_PIN C5
#define LED_CAPS_LOCK_PIN C6
#define LED_SCROLL_LOCK_PIN B7
#define LED_PIN_ON_STATE 0

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

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
