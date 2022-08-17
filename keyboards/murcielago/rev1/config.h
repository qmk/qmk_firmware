/*
Copyright 2020 elagil

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
#define VENDOR_ID 0x6166  // af
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0002
#define MANUFACTURER elagil
#define PRODUCT Murciélago

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

/* split options, use EEPROM for side detection */
#define EE_HANDS
#define SPLIT_USB_DETECT

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
#define MATRIX_ROW_PINS { B4, D5, B3, B2, B1, B0 }
#define MATRIX_COL_PINS { C6, B6, B5, D7, D6, D4 }
#define MATRIX_ROW_PINS_RIGHT { B3, B7, D4, B6, C6, C7 }
#define MATRIX_COL_PINS_RIGHT { D6, D7, D3, B2, B1, B0 }

#define ENCODERS_PAD_A { F0 }
#define ENCODERS_PAD_B { F1 }
#define ENCODERS_PAD_A_RIGHT { F6 }
#define ENCODERS_PAD_B_RIGHT { F7 }


/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN E6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

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

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
