/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID 0xC2AB
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define MANUFACTURER Pierre
#define PRODUCT Ferris the keeb

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 10

#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS_PER_SIDE (MATRIX_COLS / 2)

#define UNUSED_MCU 14
#define UNUSED_MCP 7

// wiring
#define MATRIX_ROW_PINS_MCU \
    { B3, B2, B1, F0 }
#define MATRIX_COL_PINS_MCU \
    { D6, D7, B4, B5, B6 }
#define UNUSED_PINS_MCU \
    { B0, B7, C6, C7, D2, D3, D4, D5, E6, F1, F4, F5, F6, F7 }
#define MATRIX_ROW_PINS_MCP \
    { B0, B1, B2, B3 }
#define MATRIX_COL_PINS_MCP \
    { A0, A1, A2, A3, A4 }
#define UNUSED_PINS_MCP \
    { B4, B5, B6, B7, A5, A6, A7 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

