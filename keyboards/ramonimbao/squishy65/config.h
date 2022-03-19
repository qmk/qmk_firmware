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
#define VENDOR_ID       0xB16B
#define PRODUCT_ID      0x10B5
#define DEVICE_VER      0x0065
#define MANUFACTURER Ramon Imbao
#define PRODUCT Squishy65

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_COL_PINS { A9, B9, B7, B6, B5, B4, B2, B1, B0, A7, A6, A5, A4, A10, A3, A2 }
#define MATRIX_ROW_PINS { A15, B3, A0, B10, B11 }
#define DIODE_DIRECTION COL2ROW

// RGB B4
#define RGB_DI_PIN B15
#define RGBLED_NUM 18
#define RGBLIGHT_ANIMATIONS

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
