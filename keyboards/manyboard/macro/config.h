/*
Copyright 2020 William Ehman

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

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D2, D3 }
#define MATRIX_COL_PINS { D4, D5, D6, D7 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* RGB Pins */
#define RGB_DI_PIN B6
#define RGBLED_NUM 2
#define RGBLIGHT_LIMIT_VAL 10
