/*
Copyright 2021 Alin M Elena <alinm.elena@gmail.com>

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

#define DEVICE_VER      0x0001
#define PRODUCT_ID      0x6060

#define LED_NUM_LOCK_PIN B12
#define LED_SCROLL_LOCK_PIN B13
#define LED_CAPS_LOCK_PIN C13

//                          0   1   2    3   4
#define MATRIX_ROW_PINS { B11, B0, B1,  A2, A3 }
//                         0    1   2   3   4   5   6   7   8    9  10  11   12
#define MATRIX_COL_PINS {A10, A15, B3, B4, B5, B9, B8, B7, B6, C15, A0, A7, B10 }

#define UNUSED_PINS
