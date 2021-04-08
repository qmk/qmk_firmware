/*
Copyright 2020 Hung DO <hungdohuy@gmail.com>

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

#define VENDOR_ID       0xFAAD
#define PRODUCT_ID      0x422D
#define DEVICE_VER      0x0200
#define MANUFACTURER    HNB
#define PRODUCT         DB63v1 Hotswap

#define MATRIX_ROWS 6
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define RGBLED_NUM 18
#define RGBLIGHT_ANIMATIONS

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3
