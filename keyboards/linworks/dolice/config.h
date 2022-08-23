/*
Copyright 2021 Moritz Plattner
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

/* Force USB NKRO */
#define FORCE_NKRO

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS { F5, F4, F6, F7, B0, B7, D7, D6, D4 }
#define MATRIX_COL_PINS { E6, F0, F1, B4, D5, D3, D2, B2 }
#define UNUSED_PINS { B1, B3, D0, D1, E2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Backlight */
#define BACKLIGHT_PIN B5 // Timer 1 on mega32u4
#define BACKLIGHT_BREATHING
#define BACKLIGHT_ON_STATE 1

/* Indicator LEDs */
#define LED_NUM_LOCK_PIN B6
#define LED_CAPS_LOCK_PIN C7
#define LED_SCROLL_LOCK_PIN C6
#define LED_PIN_ON_STATE 0