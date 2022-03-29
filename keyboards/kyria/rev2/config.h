/*
Copyright 2019 Thomas Baart <thomas@splitkb.com>

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
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    splitkb
#define PRODUCT         Kyria Keyboard
#define DESCRIPTION     Split 40 percent ergonomic keyboard rev 2

#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

#define DIODE_DIRECTION COL2ROW

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define DEBOUNCE 5

// wiring
#define MATRIX_ROW_PINS { B4, E6, D7, D4 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4 }
#define UNUSED_PINS

#define ENCODERS_PAD_A { C6 }
#define ENCODERS_PAD_B { B5 }
#define ENCODERS_PAD_A_RIGHT { B5 }
#define ENCODERS_PAD_B_RIGHT { C6 }

#define RGB_DI_PIN D3
#define RGBLED_SPLIT { 10, 10 }
#define RGBLED_NUM 20

