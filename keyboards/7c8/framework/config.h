/* Copyright 2020 Steven Nguyen
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

#define MATRIX_ROW_PINS { B0, B1, D7, B2, D6, B3, D5, B4, D4, B5 }
#define MATRIX_COL_PINS { C0, C1, C2, C3, C4, C5 }

#define TAP_CODE_DELAY 16
#define DIODE_DIRECTION COL2ROW

#define LEADER_TIMEOUT 250
#define LEADER_PER_KEY_TIMING 150
