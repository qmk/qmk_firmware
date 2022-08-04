/* Copyright 2021 Mach Keyboards

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

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* key pins */
#define MATRIX_ROW_PINS { D1, D0, D4 }
#define MATRIX_COL_PINS { E6, B4, B5 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* backlight */
#define BACKLIGHT_PIN B6
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 5

/* debounce */
#define DEBOUNCE 5