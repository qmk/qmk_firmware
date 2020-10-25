/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

// place overrides here
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS \
    { A3, A2, A1, A0, B13, B14, B15, B9, B3, B2, B4, A10, A9 }
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS \
    { B7, B1, B0 }

#define RGB_DI_PIN B10
#define RGBLED_NUM 15

#define SOLENOID_PIN B11
