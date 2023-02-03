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


/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 18

#define MATRIX_ROW_PINS { B13, B12, A7, A6, A5 }
#define MATRIX_COL_PINS { B10, B2, B1, B0, B14, B15, A8, A9, A10, B9, B8, B7, B6, B5, B4, B3, A15, A14 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Ensure we jump to bootloader if the QK_BOOT keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is userful for the Windows task manager shortcut (ctrl+shift+esc).
 */
// #define GRAVE_ESC_CTRL_OVERRIDE

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
