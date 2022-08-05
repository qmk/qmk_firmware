/*
Copyright 2019 niltea

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
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { B6, B2, B3 }
#define MATRIX_COL_PINS { C6, D7, E6, B4, B5 }
#define UNUSED_PINS { D2, D3, D4, B1 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Encoders */
#define ENCODERS_PAD_A { F4, F6 }
#define ENCODERS_PAD_B { F5, F7 }
#define ENCODER_RESOLUTION 2
// if you want to reverse encoder direction
// #define ENCODER_DIRECTION_FLIP

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Register custom font file */
#ifdef OLED_ENABLE
  #define OLED_FONT_H "lib/glcdfont.c"
#endif

/* Feature disable options */
#define NO_DEBUG
#define NO_PRINT
