/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
#define MANUFACTURER    EVE
#define PRODUCT         Meteor

#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                        0   1   2   3   4   5   6   7   8   9   A   B   C   D   E
#define MATRIX_ROW_PINS { B5, B0, B1, B2, B3, B4 }
#define MATRIX_COL_PINS { C2, C3, C4, C5, C6, C7, A7, A6, A5, A4, A3, A2, A1, A0, D7}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define BACKLIGHT_LEVELS 1
