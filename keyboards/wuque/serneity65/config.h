/* Copyright 2021 wuque
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


#define MATRIX_ROW_PINS { B0, F0, B1, D2, D3 }
#define MATRIX_COL_PINS { B6, B5, D5, D4, D6, B4, D7, F1, F4, F5, F6, F7, C7, E6, B7 }

#define DIODE_DIRECTION COL2ROW

// Note:  array is { col, row )
#define ENCODERS_CW_KEY  { { 3, 4 } }
#define ENCODERS_CCW_KEY { { 5, 4 } }
