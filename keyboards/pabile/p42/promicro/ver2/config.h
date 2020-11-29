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
#define PRODUCT_ID      0x6670
#define DEVICE_VER      0x0002
#define MANUFACTURER    Pabile
#define PRODUCT         P42v2 Keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 7

/* pin-out for PROMICRO */
#define MATRIX_ROW_PINS { D1, D0, D4, C6, D7, E6 }
#define MATRIX_COL_PINS { B4, F7, B1, B6, B2, B3, F6 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Encoders */
#define ENCODERS_PAD_A { D3, F5 }
#define ENCODERS_PAD_B { D2, F4 }
