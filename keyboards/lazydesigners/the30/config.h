/*
Copyright 2019 Erovia

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
#define VENDOR_ID       0x4C44 // "LD"
#define PRODUCT_ID      0x0030
#define DEVICE_VER      0x0001
#define MANUFACTURER    LazyDesigners
#define PRODUCT         THE30
#define DESCRIPTION     A 30% keyboard

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 10

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D2 }
#define MATRIX_COL_PINS { B1, B2, B3, D4, D6, D7, B4, B5, B6, C6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3
