/*
Copyright 2020 2Moons

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
#define VENDOR_ID       0x04D8
#define PRODUCT_ID      0xEC17
#define DEVICE_VER      0x0002
#define MANUFACTURER    2Moons
#define PRODUCT         Slice

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 9

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, B5 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

/* Select hand configuration */
//#define EE_HANDS
#define MASTER_LEFT
//#define MASTER_RIGHT

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
