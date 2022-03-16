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

/* USB Device descriptor parameter */
#define VENDOR_ID    0x525C
#define PRODUCT_ID   0xE3EB
#define DEVICE_VER   0x0001
#define MANUFACTURER Axolstudio
#define PRODUCT      Foundation Gamma

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B2, B1, B0, F7, F6, F5 }
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, D7, D6, D4, D5, D3, D2, D1, D0, B3, F4, F1, F0 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* CAPS LED */
#define LED_CAPS_LOCK_PIN B7

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
