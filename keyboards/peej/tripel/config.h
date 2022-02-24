/*
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
#define VENDOR_ID       0x706A
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    Peej
#define PRODUCT         Tripel

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 8
#define MATRIX_ROW_PINS { C6, D4, D0, B4, E6, D7, D1, D2, D3 }
#define MATRIX_COL_PINS { B5, B6, B2, B3, B1, F7, F6, F5 }
#define UNUSED_PINS { F4 }

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
