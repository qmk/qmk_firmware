/*
Copyright 2020 MechMerlin 

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
#define VENDOR_ID       0x0159
#define PRODUCT_ID      0x0187
#define DEVICE_VER      0x0001
#define MANUFACTURER    Project Keyboard
#define PRODUCT         Signature87

/* key matrix size */
#define MATRIX_ROWS     12
#define MATRIX_COLS     9

//                         0   1     2    3    4   5    6   7   8   9    A   B
#define MATRIX_COL_PINS { A7,  A6,  A5,  A4,  A3, A2, A15, B3, B4 }
#define MATRIX_ROW_PINS { B13, B12, A8, B15, A10, A9, B9,  B8, B1, B0, B10, B2 }
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
