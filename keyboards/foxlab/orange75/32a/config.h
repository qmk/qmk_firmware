/*
Copyright 2019 MechMerlin

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

#define VENDOR_ID    0xFEEB
#define PRODUCT_ID   0x6060
#define DEVICE_VER   0x0001
#define MANUFACTURER Fox-Lab
#define PRODUCT      Orange75
#define DESCRIPTION  A custom 75% keyboard

#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                         0   1   2   3   4   5   6   7   8   9   A   B   C   D  E
#define MATRIX_ROW_PINS { B5, B0, B1, B2, B3, B4 }
#define MATRIX_COL_PINS { C2, C4, C5, C6, C7, A7, A6, A5, A4, A3, A2, A1, A0, C3, D7 }
// #define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, C1, C0, D7 }
#define UNUSED_PINS {}

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define BACKLIGHT_LEVELS 1
#define RGBLIGHT_ANIMATIONS

#define NO_UART 1

/* disable these deprecated features by default */
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION
#endif

/* key combination for magic key command */
/* defined by default; to change, uncomment and set to the combination you want */
// #define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
