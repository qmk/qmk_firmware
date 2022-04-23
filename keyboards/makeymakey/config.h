/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 6

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { D6, B4, C7, B1, E6, D7 }, \
    { C6, D4, D0, D1, D2, D2 }, \
    { F0, F1, F5, F5, F6, F7 }  \
}

/* LEDs Pins */
#define LED_PINS 5
#define LED_PINS_HW {B5, B6, B7, B3, B2}

#define DEBOUNCE 10
