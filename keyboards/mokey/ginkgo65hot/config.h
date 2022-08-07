/*
Copyright 2021 Kyle McCreery
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
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B0, B1, B2, B3, F7 }
#define MATRIX_COL_PINS { C7, F6, F5, F4, F1, E6, D0, D1, D2, D3, D5, D4, D6, D7, B4 }
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 6
#define BACKLIGHT_CAPS_LOCK
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 5

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
