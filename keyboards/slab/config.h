/*
Copyright 2021 tjcampie

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
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { C7, C6 }
#define MATRIX_COL_PINS { B6, B5, B4, D7 }

/* Define encoder pads */
#define ENCODERS_PAD_A { B0 }
#define ENCODERS_PAD_B { B1 }
// #define ENCODERS_PAD_C { B2 }
#define ENCODER_RESOLUTION 1

// #define ENCODER_DEFAULT_POS 0x3

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW
