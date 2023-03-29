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

#define MATRIX_ROW_PINS { F4, F1, F0, C6 }
#define MATRIX_COL_PINS { F7, F6, F5, D3, D5, D4, D6, D7, B4, B5, B6, C7, B0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*EEPROM for via*/
#define DYNAMIC_KEYMAP_LAYER_COUNT 5