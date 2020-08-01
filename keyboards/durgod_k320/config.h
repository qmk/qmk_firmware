/*
Copyright 2020 kuenhlee

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

#include "config_common.h"

#define TKL_DURGOD_K320

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0xFACE
#define DEVICE_VER      0x0002
#define MANUFACTURER    Durgod-QMK 
#define PRODUCT         K320
#define DESCRIPTION     "A QMK Enabled Durgod TKL"

/* Unicode Input Mode */
#define UNICODE_SELECTED_MODES UC_WINC

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4, A5, A6 }
#define MATRIX_COL_PINS { C4, C5, B0, B1, B2, B10, B11, B12, B13, B14, B15, C6, C7, C10, C11, C12 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#define BOOTMAGIC_LITE_ROW                 0
#define BOOTMAGIC_LITE_COLUMN              0

