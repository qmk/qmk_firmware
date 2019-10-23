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


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0002
#define MANUFACTURER    Salicylic_Acid
#define PRODUCT         naked60
#define DESCRIPTION     Ortholinear 60 Keys Keyboard

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 12

// Rows are doubled-up
#define MATRIX_ROW_PINS { B6, D1, D0, D4, C6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, D7, E6, B4, B5, D3 }
// When using Setta21
#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6, B2 }
#define MATRIX_COL_PINS_RIGHT { F4, F5, F6, F7, B1, B3, B2, B6, B4, B5, B2, B2 }
// When using Nafuda
//#define MATRIX_ROW_PINS_RIGHT { D1, D0, D4, C6, B6 }
//#define MATRIX_COL_PINS_RIGHT { F4, F5, F6, F7, B1, B3, B2, D7, E6, B4, B5, D3 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
