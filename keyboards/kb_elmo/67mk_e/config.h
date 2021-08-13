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
#define VENDOR_ID    0xA68C
#define PRODUCT_ID   0xD03E
#define DEVICE_VER   0x0001
#define MANUFACTURER kb_elmo
#define PRODUCT      67mk_E

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D7, B4, D6, D5, B0 }
#define MATRIX_COL_PINS { B3, B2, B1, D4, D2, D3, C7, C6, B5, B6, F7, F6, F5, F0, F1, F4 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Indicator LEDs */
#define LED_CAPS_LOCK_PIN B7
