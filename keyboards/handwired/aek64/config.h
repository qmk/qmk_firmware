/*
Copyright 2015 Jun Wako <wakojun@gmail.com> <4sStylZ@protonmail.ch>

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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001
#define MANUFACTURER    4sStylZ and others makers
#define PRODUCT         AEK64
#define DESCRIPTION     QMK keyboard firmware for AEK64 handwired

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

// Originally made for a Teensy 2++
#define MATRIX_COL_PINS { F0, E6, E7, B0, B1, B2, B3, B4, B5, B6, B7, D0, D1, D2 }
#define MATRIX_ROW_PINS { E0, E1, C0, C1, C2 }
#define UNUSED_PINS

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* Enable the space-cadet options */
#define RSPC_KEYS KC_RSFT, KC_TRNS, KC_PGUP
#define RCPC_KEYS KC_RCTL, KC_TRNS, KC_PGDOWN
#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_HOME
#define LCPO_KEYS KC_LCTL, KC_TRNS, KC_END

/* Enable double tab */
#define TAPPING_TERM 175

#define COMBO_COUNT 1

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
