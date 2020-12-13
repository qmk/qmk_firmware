/*
Copyright 2019 JER

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

#define VENDOR_ID 0x20A0
#define PRODUCT_ID 0x422D
#define DEVICE_VER 0x0001
#define MANUFACTURER JER
#define PRODUCT J80

#define MATRIX_ROWS 7
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { B1, B2, B3, B5, B6, B7, B0 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, A0 }
#define UNUSED_PINS { B4, C1, C0, D0, D1, D2, D3, D4, D5, D6, D7 }

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_PIN D4

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* key combination for magic key command */
/* defined by default; to change, uncomment and set to the combination you want */
// #define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
