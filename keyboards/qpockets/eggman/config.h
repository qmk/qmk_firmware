/* Copyright 2021 Alan Lehners
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 7
 
#define MATRIX_ROW_PINS { C4, C5, C2, D0, B5, B6, D6 }
#define MATRIX_COL_PINS { B7, B4, B3, B2, D3, D2, D1 }


/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* ROTARY ENCODERS */
#define ENCODERS_PAD_A { C6, D4 }
#define ENCODERS_PAD_B { C7, D5 }

#define ENCODER_RESOLUTION 4
//#define ENCODER_DIRECTION_FLIP

#define DEBOUNCE 5

