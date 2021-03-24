/*
Copyright 2020 Adam Honse <calcprogrammer1@gmail.com>
Copyright 2020 Dimitris Mantzouranis <d3xter93@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Backlight configuration
#define BACKLIGHT_LEVELS 8

#define LED_MATRIX_ROWS 5
#define LED_MATRIX_ROW_CHANNELS 3
#define LED_MATRIX_ROWS_HW (LED_MATRIX_ROWS * LED_MATRIX_ROW_CHANNELS)
#define LED_MATRIX_ROW_PINS { C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, B13, D3, B15, B14 }

#define LED_MATRIX_COLS 16
#define LED_MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7 }

#define DRIVER_LED_TOTAL (LED_MATRIX_ROWS * LED_MATRIX_COLS)