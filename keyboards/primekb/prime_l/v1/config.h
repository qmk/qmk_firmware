/*
Copyright 2018 Jumail Mundekkat
Copyright 2020 Holten Campbell

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

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D1, D0, B7, B3, B2 }
#define MATRIX_COL_PINS { D2, D3, D5, D4, D6, D7, B4, B5, C7, C6, F7, F6, F5, F4, F1, F0 }
#define UNUSED_PINS

#define BACKLIGHT_PIN B6
/*#define BACKLIGHT_BREATHING*/
#define BACKLIGHT_LEVELS 4
