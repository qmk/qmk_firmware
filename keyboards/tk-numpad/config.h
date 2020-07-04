/*
Copyright 2020

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





/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4


// #define MATRIX_ROW_PINS { C2, C4, C5, C6, C7 }
// #define MATRIX_COL_PINS { D7, D6, D5, D4 }
#define MATRIX_ROW_PINS {C6, B6, B5, B4, D7}
#define MATRIX_COL_PINS {F1, F4, F5, F6}
#define DIODE_DIRECTION COL2ROW



#define BACKLIGHT_LEVELS 24
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6




//Encoder stuff
#define ENCODERS_PAD_A { F7 }
// #define ENCODERS_PAD_B { B13 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define ENCODER_RESOLUTION 2


#define BACKLIGHT_PIN C7
//#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 10

