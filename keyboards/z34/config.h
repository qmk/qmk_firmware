/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>

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
#define VENDOR_ID       0x7A74
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    zigotica
#define PRODUCT         z34

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

/*Keyboard Matrix Assignments */

#define DIRECT_PINS { \
    { C6, F7, F6, F5, F4 }, \
    { D7, B6, B2, B3, B1 }, \
    { E6, D4, D0, D1, D3 }, \
    { B4, B5, NO_PIN, NO_PIN, NO_PIN } \
}

#define DIRECT_PINS_RIGHT { \
    { F4, F5, F6, F7, C6 }, \
    { B1, B3, B2, B6, D7 }, \
    { D3, D1, D0, D4, E6 }, \
    { B5, B4, NO_PIN, NO_PIN, NO_PIN } \
}

#define UNUSED_PINS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Serial settings */
#define USE_SERIAL
/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

// EE_HANDS MASTER_RIGHT MASTER_LEFT
#define MASTER_RIGHT

