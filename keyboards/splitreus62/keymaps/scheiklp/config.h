/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBEEF
#define PRODUCT_ID      0xFED0
#define DEVICE_VER      0x0001
#define MANUFACTURER    NaCly
#define PRODUCT         Splitreus62

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { D3, D2, D1, D4, C6, D7 }
#define MATRIX_COL_PINS { E6, B4, B5, B6, B2, B3 }

#define DIODE_DIRECTION ROW2COL

#define SPLIT_HAND_PIN F4

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define AUTO_SHIFT_TIMEOUT 100
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_NUMERIC

// require two taps for a TT layer switch (default 5)
#define TAPPING_TOGGLE 2

// Mouse control
// constant mode (velocity)
#define MK_3_SPEED
// KC_ACL0 < KC_ACL1 < unmodified < KC_ACL2

// Cursor offset per movement (unmodified)
#define MK_C_OFFSET_UNMOD 16
// Time between cursor movements (unmodified)
#define MK_C_INTERVAL_UNMOD 10
/* #define MK_C_INTERVAL_UNMOD 16 */

// Cursor offset per movement (KC_ACL0)
#define MK_C_OFFSET_0 1
// Time between cursor movements (KC_ACL0)
#define MK_C_INTERVAL_0 32

// Cursor offset per movement (KC_ACL1)
#define MK_C_OFFSET_1 4
// Time between cursor movements (KC_ACL1)
#define MK_C_INTERVAL_1 16

// Cursor offset per movement (KC_ACL2)
#define MK_C_OFFSET_2 20
/* #define MK_C_OFFSET_2 32 */
// Time between cursor movements (KC_ACL2)
#define MK_C_INTERVAL_2 16
