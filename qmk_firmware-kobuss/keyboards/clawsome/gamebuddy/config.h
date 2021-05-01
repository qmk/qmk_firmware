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
#define PRODUCT_ID      0x17B9
#define DEVICE_VER      0x0001
#define MANUFACTURER    AlisGraveNil
#define PRODUCT         GameBuddy
#define DESCRIPTION     A 26-key QMK-powered macropad designed for gaming!

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { D1, D0, E6, B3, B2 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, C6, D7, B6 }

#define DIODE_DIRECTION COL2ROW
