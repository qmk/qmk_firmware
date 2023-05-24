/*
Copyright 2021 KapCave

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
#define VENDOR_ID       0x4B43
#define PRODUCT_ID      0x4152
#define DEVICE_VER      0x0001
#define MANUFACTURER    KapCave
#define PRODUCT         Arya

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 8

#define MATRIX_COL_PINS { B0, B5, B4, B2, C13, F1, F0, A14}
#define MATRIX_ROW_PINS { B8, A13, B1, A15, B9, B10, B11, A0, A8 }
#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define ENCODERS_PAD_A { B12, B14, C15 }
#define ENCODERS_PAD_B { B13, B15, C14 }

#define ENCODER_RESOLUTION 2
#define TAP_CODE_DELAY 25 

#define DYNAMIC_KEYMAP_LAYER_COUNT 3

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
