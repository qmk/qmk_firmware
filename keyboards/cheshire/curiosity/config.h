/*
Copyright 2019 zvecr<git@zvecr.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCAFE
#define PRODUCT_ID      0x0FAD
#define DEVICE_VER      0x0001
#define MANUFACTURER    Nightingale Studios/Cheshire Designs
#define PRODUCT         Curiosity
#define DESCRIPTION     Curiosity

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { B13, B14, A4, A2, A1 }
#define MATRIX_COL_PINS { B11, B10, B2, B1, B0, A7, A6, A5, B9, B8, B7, B6, B5, B4, B3, A15 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B15
#define RGBLED_NUM 14

#define RGBLIGHT_ANIMATIONS

#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
