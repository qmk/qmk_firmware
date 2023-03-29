/* Copyright 2020 qpockets
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


#define MATRIX_ROW_PINS \
    { F1, F4, F5, C7 }
#define MATRIX_COL_PINS \
    { D4, B4, B5, B6, C6, F7, F6, F0, B0, E6, B1 }


/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define LOCKING_SUPPORT_ENABLE
