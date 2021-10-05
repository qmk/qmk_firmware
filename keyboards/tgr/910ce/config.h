/*
Copyright 2020 mechmerlin

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

#define VENDOR_ID 0x5447 // TG
#define PRODUCT_ID 0x910C
#define DEVICE_VER 0x0001
#define MANUFACTURER TGR
#define PRODUCT 910CE

#define RGBLED_NUM 18

#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                         0   1   2   3   4   5   6   7   8   9   A   B   C   D   E
#define MATRIX_ROW_PINS { B1, B2, B3, B4, B5, B6 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, D7 }
#define UNUSED_PINS {}

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN D1

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3
#define RGBLIGHT_ANIMATIONS

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

