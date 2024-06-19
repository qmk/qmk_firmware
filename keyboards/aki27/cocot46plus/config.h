/*
Copyright 2022 aki27

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

// These do not seem to have keyboard.json support yet.
#define ADNS5050_SCLK_PIN         B2
#define ADNS5050_SDIO_PIN         B4
#define ADNS5050_CS_PIN           B5

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, D7, E6, NO_PIN }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3 }

#define DIODE_DIRECTION COL2ROW

#define POINTING_DEVICE_ROTATION_180
#define OLED_FONT_H "keyboards/aki27/cocot46plus/glcdfont.c"
