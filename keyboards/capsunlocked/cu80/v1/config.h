/*
Copyright 2020 Andy Holland

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


#define MATRIX_ROW_PINS { B1, B5, B4, F7, D7, D6 }
#define MATRIX_COL_PINS { F6, F5, F4, F1, F0, C7, C6, B6, B0, E6, B7, B3, B2, D2, D3, D5, D4}

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
