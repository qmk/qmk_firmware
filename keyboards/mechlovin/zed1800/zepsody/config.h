/*
Copyright 2022 Mechlovin'

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
#define MATRIX_ROWS 6
#define MATRIX_COLS 20

#define MATRIX_ROW_PINS { B8, B7, B6, B5, B4, B3}
#define MATRIX_COL_PINS { A10, A9, A8, A15, B14, B13, B12, B11, B10, B2, B1, B0, A7, A6, A5, A4, A3, A2, A1, A0}

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN B15
#define RGBLIGHT_LAYERS
#define RGBLED_NUM 6
#endif
