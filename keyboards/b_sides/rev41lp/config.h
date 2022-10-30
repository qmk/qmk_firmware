/*
Copyright 2021 @cyril279

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
#define MATRIX_ROWS 7
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { F4, B2, F5, B3, F6, B1, F7 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B6
#define BACKLIGHT_ON_STATE 1
#define BACKLIGHT_LEVELS 7
#define BACKLIGHT_LIMIT_VAL 150

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
