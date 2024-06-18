/*
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

/* key matrix size */
#define MATRIX_ROWS 15
#define MATRIX_COLS 7


// wiring the whole kinesis keyboard
// #define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
// #define MATRIX_ROW_PINS { F6, F7, B1, B3, B2, B6 }
// #define MATRIX_COL_PINS { F0, F1, C7, D5, B7, B6, B2}
#define MATRIX_COL_PINS { B2, B6, B7, D5, C7, F1, F0 }
#define MATRIX_ROW_PINS { B3, B1, F7, F6, F5, F4, D3, D2, D1, D0, D4, C6, D7, E6, B4 }

#define DIODE_DIRECTION COL2ROW

// WS2812 RGB LED strip input and number of LEDs
// #define RGB_DI_PIN D3
// #define RGBLED_NUM 12

