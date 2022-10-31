/*
Copyright 2019 Holten Campbell

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


#undef MATRIX_ROWS 
#undef MATRIX_COLS 
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

/* key matrix size */
#define MATRIX_ROWS 5 
#define MATRIX_COLS 15

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { E6, C7, B5, B4, C6 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, D6, D4, D5, D3, D2, D1, D0, B6, D7} 

// Babble config
#define USE_BABBLEPASTE
#define BABL_MODSWAP
#define BABL_READMUX
#define BABL_KITTY
#define BABL_MAC
#define BABL_LINUX
