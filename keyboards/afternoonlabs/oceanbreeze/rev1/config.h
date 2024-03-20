/* Copyright 2021 Afternoon Labs
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

// wiring of each half
#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7, B1, B6 }
#define MATRIX_COL_PINS \
    { B2, D1, D0, D4, C6, D7, E6, B4, B5 }

#define SPLIT_HAND_PIN B3

#define DIODE_DIRECTION COL2ROW
