/*
Copyright 2018 QMK Contributors

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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x4260
#define DEVICE_VER      0x0001
#define MANUFACTURER    rs
#define PRODUCT         rs60

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { B5, B6, B4, B2, E6 }
#define MATRIX_COL_PINS { C6, D4, D0, D1, D2, D3,  F4, F5, F6, F7, B1, B3}
#define UNUSED_PINS { }

#define QMK_ESC_OUTPUT C6
#define QMK_ESC_INPUT  B4
#define QMK_LED        B0
// #define QMK_SPEAKER    C6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* key combination for command */
#define IS_COMMAND() ( \
    false \
)
