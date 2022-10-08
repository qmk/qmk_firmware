/*
Copyright 2020 Michael Pio "Coarse" Mayol  <mfmayol@up.edu.ph>

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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 18

#define MATRIX_COL_PINS { B13, B12, B1, B0, A7, A6, A5, A4, A3, B9, B8, B7, B6, B5, B4, F0, B3, A15 }
#define MATRIX_ROW_PINS { A8, B14, B11, B10, B2 }
#define DIODE_DIRECTION COL2ROW
/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define LED_CAPS_LOCK_PIN F1
#define LED_PIN_ON_STATE 0
