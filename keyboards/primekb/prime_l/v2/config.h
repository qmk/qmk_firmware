/*
Copyright 2020 Holten Campbell

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
#define PRODUCT_ID      0x5042
#define DEVICE_VER      0x0002
#define PRODUCT         Prime_L V2

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { E6, B2, B1, B0, B6 }
#define MATRIX_COL_PINS { C6, C7, F7, F6, F5, F4, F1, F0, D4, D0, D1, D2, D3, D5, B7, B3 }
