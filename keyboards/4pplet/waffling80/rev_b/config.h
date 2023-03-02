/*
Copyright 2022 Stefan Sundin "4pplet" <mail@4pplet.com>

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


// ROWS: Top to bottom, COLS: Left to right
#define MATRIX_ROW_PINS {B13,B12,A5,A4,A2,A1,F0,C15,C13,C14,F1,A0}
#define MATRIX_COL_PINS {B2,B1,B0,A7,A6,A3,B9,B8}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define RGBLED_NUM 2
#define WS2812_EXTERNAL_PULLUP
#define RGB_DI_PIN A8

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
