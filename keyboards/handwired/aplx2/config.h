/*
Copyright 2020 April Aplyard <alex.fragiou@gmail.com>

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
#define VENDOR_ID       0xE0E0
#define PRODUCT_ID      0x0030
#define DEVICE_VER      0x0001
#define MANUFACTURER    Aplyard
#define PRODUCT         Aplx2

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 2

/* pin-out */
#define MATRIX_ROW_PINS { D1 }
#define MATRIX_COL_PINS { B5, D3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

