// Copyright 2021 HuangJuanLr <huangjuanlr@gmail.com>
/*
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
// #define VENDOR_ID       0x4C52 // 2021 HuangJuanLR
// #define PRODUCT_ID      0x4C80 // Leon Rev.alpha 80% TKL
// #define DEVICE_VER      0x210A // 2021 Rev.a
// #define MANUFACTURER    ZooKeeper
// #define PRODUCT         Leon

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define MATRIX_COL_PINS { A5, A9, A8, B15, B14, B13, B12, B5, B10, B2, B1, B0, A7, A6, A15, B3, B4 }
#define MATRIX_ROW_PINS { B7, B8, B9, A2, A3, A4 }
#define DIODE_DIRECTION COL2ROW


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

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
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION