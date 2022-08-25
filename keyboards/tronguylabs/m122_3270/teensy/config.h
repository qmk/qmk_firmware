/* Copyright 2021 James R. Maynard III <jaymaynard@gmail.com>
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

// Teensy pin assignments: I'm wiring things a bit more straightforwardly, and
//    avoiding the LED on PD6
#define MATRIX_COL_PINS { B5, B6, B7, D0, D1, D2, D3, D4, D5, D7, E0, E1, C0, C1, C2, C3, C4, C5, C6, C7 }
#define MATRIX_ROW_PINS { F0, F1, F2, F3, F4, F5, F6, F7 }
