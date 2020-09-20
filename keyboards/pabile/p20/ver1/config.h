/*
Copyright 2020 Pabile

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
#define VENDOR_ID       0x6666
#define PRODUCT_ID      0x6667
#define DEVICE_VER      0x0001
#define MANUFACTURER    Pabile
#define PRODUCT         P20 ver1

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* pin-out */
#define MATRIX_ROW_PINS { B3, B4, B5, D7, E6 }
#define MATRIX_COL_PINS { D0, B2, D4, B6 }
#define UNUSED_PINS
 
#define ENCODERS_PAD_A { F5, F7 }
#define ENCODERS_PAD_B { F6, B1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW