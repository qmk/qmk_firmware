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

#define MATRIX_ROW_PINS { B7, B2, F1, F4, D6, D7, D5, D4, D3, D2 }
#define MATRIX_COL_PINS { F5, F6, F7, C6, B6, B5, B4, B3 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*RGB TINGS*/
#define RGB_DI_PIN E6
#define RGBLED_NUM 12
