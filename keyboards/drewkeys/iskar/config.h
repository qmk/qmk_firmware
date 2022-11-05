/*
Copyright 2021 Drewkeys

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
#define VENDOR_ID    0xDE43
#define PRODUCT_ID   0x1284
#define DEVICE_VER   0x0001
#define MANUFACTURER Drewkeys
#define PRODUCT      Iskar

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

 //                       0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
#define MATRIX_ROW_PINS { D6, D7, B4, B5, D4 }
#define MATRIX_COL_PINS { B6, C6, C7, F6, F5, F4, F7, F1, F0, E6, B7, D0, D1, D2, D3, D5 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
