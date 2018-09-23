/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

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

// #define MATRIX_ROW_PINS { A7, A6, A5, A4 }
// #define MATRIX_COL_PINS { D7, C2, C3, C4, C5, C6, C7, A3, A2, A1, A0, B0 }

// #define DIODE_DIRECTION COL2ROW

#define TAPPING_TOGGLE 3

#define NO_UART 1

#undef C6_AUDIO
#define D5_AUDIO
