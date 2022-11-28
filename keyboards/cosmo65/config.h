/*
Copyright 2022 BentoBox Studio
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#pragma once

#include "config_common.h"

/* RGB Lighting */
#define RGB_DI_PIN F7
#define RGBLED_NUM 16
#define RGBLIGHT_ANIMATIONS

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* keyboard matrix assignments */
#define MATRIX_ROW_PINS { D5, D0, F0, F5, F4 }
#define MATRIX_COL_PINS { E6, D4, D6, D7, B4, B5, B6, C6, C7, D1, D2, D3, F1, F6 }
#define UNUSED_PINS {B0, B7}
#define DIODE_DIRECTION COL2ROW
