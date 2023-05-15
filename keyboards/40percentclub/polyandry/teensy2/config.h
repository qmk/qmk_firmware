/* Copyright 2021
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


/* key matrix pins */

// Note from original contributor (ryjelsum):
// Untested - don't have teensy2. if some keys do not function or are in wrong place,
// please check the pin definitions. I may have screwed up. :) 

#define MATRIX_ROW_PINS { D3 }
#define MATRIX_COL_PINS { B7, D0, D1, D2, C6, C7, F6, F7, B6, B5, D7, D6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
