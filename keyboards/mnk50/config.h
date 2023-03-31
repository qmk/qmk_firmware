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


#define MATRIX_ROW_PINS { B12, B13, A10, A6 }
#define MATRIX_COL_PINS { B14, B15, A8, A9, A13, A14, A15, B3, B4, B5, B6, B7, B8, B9 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Ensure we jump to bootloader if the QK_BOOT keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
