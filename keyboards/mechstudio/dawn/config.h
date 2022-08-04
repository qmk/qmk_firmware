/* Copyright 2020 David Dejaeghere
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
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS {B1,B2,B3,D1,D6,D4}
#define MATRIX_COL_PINS {F0,F1,F4,F5,F6,F7,C7,C6,B6,B5,B4,D7,D5,D3,D2}
#define UNUSED_PINS {B0,B7,D0,E6}

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

#define QMK_ESC_OUTPUT F0 // usually COL
#define QMK_ESC_INPUT B1 // usually ROW
