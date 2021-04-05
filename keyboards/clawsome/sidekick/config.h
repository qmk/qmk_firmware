/*
Copyright 2020 AAClawson (AlisGraveNil)

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
#define PRODUCT_ID      0xDB9F
#define DEVICE_VER      0x0001
#define MANUFACTURER    AlisGraveNil
#define PRODUCT         Sidekick

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { D0, C6, B2, B6, B5 }
#define MATRIX_COL_PINS { F6, F5, B1, B3, E6, D7, D4 }

#define DIODE_DIRECTION COL2ROW
