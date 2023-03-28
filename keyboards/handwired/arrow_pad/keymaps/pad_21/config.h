/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#undef VENDOR_ID
#undef PRODUCT_ID
#undef DEVICE_VER
#undef MANUFACTURER
#undef PRODUCT
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x4097
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Nobody"
#define PRODUCT         "Arrow Pad 21"

#undef MATRIX_ROWS
#undef MATRIX_COLS
#define MATRIX_ROWS 2
#define MATRIX_COLS 11

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS { D3, D5 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, B6, B5, B4, D7, D4 }
