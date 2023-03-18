/* Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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
#define MATRIX_ROW_PINS \
    { GP7, GP0, GP8, GP25, GP11, GP12 }
#define MATRIX_COL_PINS \
    { GP6, GP5, GP4, GP3, GP2, GP1, GP20, GP21, GP16, GP17, GP18, GP19, GP15, GP14, GP13, GP10, GP9 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
