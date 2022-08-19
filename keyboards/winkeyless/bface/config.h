/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Copyright 2017 Sebastian Kaim <sebastian.kaim@sebb767.de>

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

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 15

//                        0   1   2   3   4   5   6   7   8   9   A   B   C   D   E
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, D7}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN D0
#define LED_CAPS_LOCK_PIN D1
#define LED_SCROLL_LOCK_PIN D6

#define RGBLED_NUM 16
#define RGBLIGHT_ANIMATIONS

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3
