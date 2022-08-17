/*
Copyright 2020 MisonoWorks

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

// matrix
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

// pins
#define MATRIX_ROW_PINS { D2, D3, D5, F0 }
#define MATRIX_COL_PINS { B3, D4, D6, D7, B4, B5, B6, C6, C7, F7, F6}

// diode mode
#define DIODE_DIRECTION COL2ROW

// debouncing, NKRO, mouse keys speed 
#define DEBOUNCE 5
#define FORCE_NKRO
#define MK_3_SPEED
#define TERMINAL_HELP

// encoders
#define ENCODERS_PAD_A { B2, F4 }
#define ENCODERS_PAD_B { B1, F5 }
#define ENCODER_RESOLUTION 3

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN D1
#ifdef RGB_DI_PIN
#define RGBLED_NUM 19
#define RGBLIGHT_ANIMATIONS
#endif
