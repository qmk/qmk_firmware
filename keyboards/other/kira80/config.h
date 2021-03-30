/*
Copyright 2020 kb-elmo<mail@elmo.space>

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
#define VENDOR_ID 0x6986
#define PRODUCT_ID 0xC583
#define DEVICE_VER 0x0102
#define MANUFACTURER EVE
#define PRODUCT Kira80

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B1, B2, B3, B5, B6, B7, B0 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, A0, C2, D7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN D1
#define LED_SCROLL_LOCK_PIN D6

#define BACKLIGHT_PIN D4
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3
