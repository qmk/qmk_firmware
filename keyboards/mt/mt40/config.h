/*
Copyright 2017 REPLACE_WITH_YOUR_NAME

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

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 15

#define RGB_DI_PIN C0
#define RGBLED_NUM 12
#define RGBLIGHT_ANIMATIONS

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
/* #define CC6 0x63 // C3 */
/* #define CB6 0x37 // B7 */
/* #define CC7 0x62 // C2 */

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B6, B7 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, D7 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN D2

/* number of backlight levels */
#define BACKLIGHT_LEVELS 3

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
/* #define DEBOUNCE 5 */

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
/* #define LOCKING_SUPPORT_ENABLE */
/* Locking resynchronize hack */
/* #define LOCKING_RESYNC_ENABLE */

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is userful for the Windows task manager shortcut (ctrl+shift+esc).
 */
// #define GRAVE_ESC_CTRL_OVERRIDE

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
