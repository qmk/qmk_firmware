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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5845  // XE
#define PRODUCT_ID      0x5854  // XT
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         TrinityXTtkl

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 19

#define MATRIX_COL_PINS { A9, A8, B15, B14, B13, B12, B11, B10, B2, B1, B0, A7, A6, A5, A4, A3, A10, B9, B4 }
#define MATRIX_ROW_PINS { A14, A15, B3, A2, B6, B5 }
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
