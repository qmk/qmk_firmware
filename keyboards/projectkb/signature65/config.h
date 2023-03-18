/*
Copyright 2020 MechMerlin 

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

//                        1    2   3   4   5   6   7   8    9    10   11  12  13  14  15  16
#define MATRIX_COL_PINS { B14, A2, B9, B8, B5, B4, B3, A15, B11, B10, B2, A3, B1, B0, A4, A5 }
//                        1   2   3    4   5
#define MATRIX_ROW_PINS { A8, A9, B13, A6, A7 }
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
