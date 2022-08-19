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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 20

#define MATRIX_COL_PINS { B11, B10, B2, B1, B0, A7, A6, A5, A4, A3, A2, A1, F1, C15, B3, C14, C13, B9, B8, B7 }
#define MATRIX_ROW_PINS { B4, A15, A14, A0, F0 }
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B12
#define LED_NUM_LOCK_PIN B14
#define LED_PIN_ON_STATE 0


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { B6 }

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
