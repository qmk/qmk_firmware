/*
Copyright 2019 Jianfei Wang

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
#define PRODUCT_ID 0x1960
#define DEVICE_VER 0x0001
#define MANUFACTURER YDKB
#define PRODUCT Just60
#define DESCRIPTION Just60 Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { E2, C7, B3, B2, B1 }
#define MATRIX_COL_PINS { D6, D7, B4, B6, B5, B7, F7, F6, F5, F4, F1, F0, E6, B0 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

#define QMK_ESC_OUTPUT D6 // usually COL
#define QMK_ESC_INPUT E2 // usually ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
