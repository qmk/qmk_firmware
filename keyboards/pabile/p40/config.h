/*
Copyright 2020 Pabile

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


/* pin-out
for PCB ver0.01 452019 */
#define MATRIX_ROW_PINS { F6, B3, B2, B6 }
#define MATRIX_COL_PINS { F4, F5, B5, B4, E6, D7, C6, D4, D0, D1 }
/*
for pro micro facing back of pcb
#define MATRIX_ROW_PINS { D4, E6, B4, B5 }
#define MATRIX_COL_PINS { D1, D0, B6, B2, B3, B1, F7, F6, F5, F4 }
*/

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
