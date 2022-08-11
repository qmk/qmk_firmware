/*
Copyright 2021 kb-elmo<mail@elmo.space>

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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B4, B6, D7, D5, D0 }
#define MATRIX_COL_PINS { D1, D2, D3, D4, C6, C7, F7, F6, F5, F4, F0, F1, B3, B2, B1, B0 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Caps LED */
#define LED_CAPS_LOCK_PIN D6

/* RGB */
#define RGB_DI_PIN B5
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 7
#define RGBLIGHT_SLEEP // RGB will turn off when PC is put to sleep
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_BGR // RGB on the Noah is different order


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

