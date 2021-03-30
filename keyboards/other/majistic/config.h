
/*
Copyright 2020 yossiyossy

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
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6E55
#define DEVICE_VER 0x0001
#define MANUFACTURER yossiyossy
#define PRODUCT maJIStic

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5, F4, F5 }  // F4, F5 is dummy
#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS_RIGHT { B6, B2, B3, B1, F7, F6, F5, F4 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
