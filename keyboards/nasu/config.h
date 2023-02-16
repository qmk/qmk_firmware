/*
Copyright 2021 Yiancar-Designs

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
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { A13, A10, B10, B2, A6 }
#define MATRIX_COL_PINS { A9, A8, B15, B14, B13, B12, B11, B8, B7, B6, B5, B4, B3, A15, A14 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Ensure we jump to bootloader if the QK_BOOT keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/* Indicator LEDs */
#define LED_CAPS_LOCK_PIN B1
#define LED_NUM_LOCK_PIN B0
#define LED_SCROLL_LOCK_PIN A7
