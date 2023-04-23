/* Copyright 2020 Bpendragon
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


#define MATRIX_ROW_PINS { B10, B9, B15, B14, B13, B8}
#define MATRIX_COL_PINS { A9, A10, B11, B7, B6, B5, B4, B3, B2, B1, B0, C14, A4, A5, A6, A7, A8, A15, A13, A14, B12 }
#define RGB_DI_PIN A3
#define RGBLED_NUM 50


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
