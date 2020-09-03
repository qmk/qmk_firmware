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

/* pins for PCB v2 */
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }

#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { D1, D0, D4, B2 }

#undef ENCODERS_PAD_A
#undef ENCODERS_PAD_B
