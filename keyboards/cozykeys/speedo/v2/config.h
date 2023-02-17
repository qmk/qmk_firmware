/*
Copyright 2020 Paul Ewing

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


// Keyboard Matrix Assignments
#define MATRIX_ROW_PINS { D1, D2, D3, C6, C7 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, B6, B5, D0, B7, B3, B2, B1, B0 }
#define DIODE_DIRECTION COL2ROW

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE
