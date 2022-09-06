/*
Copyright 2021 Dino Fizzotti 

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

#define VENDOR_ID       0xD1F1
#define PRODUCT_ID      0x0100
#define DEVICE_VER      0x0001
#define MANUFACTURER    Dino Fizzotti
#define PRODUCT         FnRow v1

#define MATRIX_ROWS 2
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { A0, A1 }
#define MATRIX_COL_PINS {B0, B1, B3, B4, B5, B6, B7 }

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5
