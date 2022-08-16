/*
Copyright 2022 DmNosachev

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

#define DEVICE_VER 0x0002

#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

//v.1.0
//#define MATRIX_ROW_PINS { B8, B9, C13, B7, B6, B4, B3 }
//v.1.1
#define MATRIX_ROW_PINS { B8, B9, C13, B7, B6, B5, B4 }
#define MATRIX_COL_PINS { A6, A7, B0, B1, B10, B11, A0, A1, A2, A3, A4, A5 }

#define LED_PIN_ON_STATE 0
#define LED_NUM_LOCK_PIN B14
#define LED_CAPS_LOCK_PIN B13
#define LED_SCROLL_LOCK_PIN B15
#define LED4_PIN A8
