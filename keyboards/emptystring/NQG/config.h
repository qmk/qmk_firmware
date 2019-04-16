/*
Copyright 2019 Bernard Shih (twitter: @SA_EndlessGame)

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
#define VENDOR_ID       0x0076
#define PRODUCT_ID      0x0037
#define DEVICE_VER      0x0100
#define MANUFACTURER    emptystring
#define PRODUCT         NQG
#define DESCRIPTION     30% ortholinear keyboard

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

/* key matrix pins */
#define MATRIX_ROW_PINS {B6, B2, B3, B1}
#define MATRIX_COL_PINS {F7, F6, B5, B4, E6, D7, C6, D4, D0, D1}


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 200
