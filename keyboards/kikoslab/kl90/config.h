/*
Copyright 2021 Swiftrax <swiftrax@gmail.com>

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


// ROWS: Top to bottom, COLS: Left to right

#define MATRIX_ROW_PINS { F1, F3, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { F2, F0, A2, A1, A0, D2, D3, D4, D5, D6, D7, E0, E1, C0, C1, C2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define EMCODER_DIRECTION_FLIP

/*EEPROM for via*/
#define DYNAMIC_KEYMAP_LAYER_COUNT 3