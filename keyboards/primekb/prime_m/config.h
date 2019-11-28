/*
Copyright 2018 Jumail Mundekkat

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
#define PRODUCT_ID      0x4024
#define DEVICE_VER      0x0001
#define MANUFACTURER    PrimeKB
#define PRODUCT         Prime_M
#define DESCRIPTION     6x5 Macropad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { C5, B5, B2, D5, D3 }
#define MATRIX_COL_PINS { B3, C7, C6, D2, D1, D0 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B7
/*#define BACKLIGHT_BREATHING*/
#define BACKLIGHT_LEVELS 4

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
