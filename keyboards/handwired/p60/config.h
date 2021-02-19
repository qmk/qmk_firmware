/*
    Copyright (C) 2021  Adrian L Lange

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
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

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0001

#define MANUFACTURER p3lim
#define PRODUCT P60

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS {B0, B1, B2, B3, B7}
#define MATRIX_COL_PINS {F0, F1, F4, F5, F6, F7, B6, B5, B4, D7, D2, D3, C6, C7}

#define DIODE_DIRECTION COL2ROW
