/* Copyright 2020 Dimitris Papavasiliou <dpapavas@protonmail.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

#define EE_HANDS
#define SPLIT_USB_DETECT

/* key matrix size */
#define MATRIX_ROWS 14
#define MATRIX_COLS 6

/* pin-out */
#define MATRIX_ROW_PINS { E6, F1, F0, F4, F5, F6, F7 }
#define MATRIX_COL_PINS { B4, B5, D7, B6, C6, D6 }
#define MATRIX_ROW_PINS_RIGHT { B5, B4, D7, B6, C6, D6, D4 }
#define MATRIX_COL_PINS_RIGHT { C7, F7, F6, F5, F4, F1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN D1
#define LED_SCROLL_LOCK_PIN D2
