/*
Copyright 2021 Sife

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
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Sife
#define PRODUCT         Periboard 512

/* matrix properties */
#define MATRIX_COLS 19
#define MATRIX_ROWS 8
#define DEBOUNCE 5
#define DIODE_DIRECTION ROW2COL
#define MATRIX_HAS_GHOST
#define MATRIX_COL_PINS { B7, D0, D1, D2, D3, D4, D5, D6, D7, E0, E1, C0, C1, C2, C3, C4, C5, C6, C7 }
#define MATRIX_ROW_PINS { B6, B5, B4, B3, B2, B1, B0, E7 }
