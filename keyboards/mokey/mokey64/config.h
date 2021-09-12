/*
Copyright 2021 Kyle McCreery
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

#define VENDOR_ID 0x6653
#define PRODUCT_ID 0x001A
#define DEVICE_VER 0x0001

#define MANUFACTURER rhmokey
#define PRODUCT MOKEY64

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { A1, A2, A3, A4, A5 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define RGB_DI_PIN A7
#define RGBLED_NUM 68

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE