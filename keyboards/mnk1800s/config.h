/*
Copyright 2021 Yiancar-Designs

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published byß
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


#define MATRIX_ROW_PINS { B13, B12, A7, A6, A5 }
#define MATRIX_COL_PINS { B10, B2, B1, B0, B14, B15, A8, A9, A10, B9, B8, B7, B6, B5, B4, B3, A15, A14 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Ensure we jump to bootloader if the QK_BOOT keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
