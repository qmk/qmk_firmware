/*
Copyright 2022 Mechlovin'

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

#include "config_common.h"

#define MATRIX_ROWS 5
#define MATRIX_COLS 15


#define MATRIX_ROW_PINS { B13, B14, A8, A1, A0 }
#define MATRIX_COL_PINS { B11, B12, B10, B2, B1, B0, A7, A6, A5, A4, A3, A2, B3, A15, B5 }

#define LED_CAPS_LOCK_PIN C14

// Number of encoders

#define ENCODERS_PAD_A { B4, B6 }
#define ENCODERS_PAD_B { B8, B9 }


#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 10