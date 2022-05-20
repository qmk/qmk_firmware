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

#include "config_common.h"

#ifdef MANUFACTURER
 #undef MANUFACTURER
#endif
#define MANUFACTURER Schievel
#define PRODUCT_ID 0x3536
#define DEVICE_VER 0x0001
#define PRODUCT    Dactyl-Manuform r_track
#define DESCRIPTION A splitballer board

// disable some things to reduce firmware size
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_COL_PINS { D6, D7, B4, D3, C6, C7 }
#define MATRIX_ROW_PINS { D4, B7, F7, B6, B5, F6 }
#define PMW3360_CS_PIN B0

#define DIODE_DIRECTION COL2ROW

#define MASTER_RIGHT
//#define USE_I2C
#define SPLIT_USB_DETECT

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE
//#define MOUSEKEY_INTERVAL 250
//#define MOUSEKEY_DELAY 0
#define USB_POLLING_INTERVAL_MS 3
#define TAPPING_TERM 200
#define POLLING true

#define COMBO_COUNT 3
