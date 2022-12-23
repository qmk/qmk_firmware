/* Copyright 2022 PJB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define MATRIX_ROW_PINS { B2, B1, B0, D7, B7, D1 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, C7, C6, B6, B5, D4, D5, B4, D3, D2, E6, B3 }

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN D6
#define LED_SCROLL_LOCK_PIN D0
#define LED_PIN_ON_STATE 0
