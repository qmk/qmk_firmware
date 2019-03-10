/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef REV1_CONFIG_H
#define REV1_CONFIG_H

#include "../config.h"

#define DEVICE_VER      0x0001

/* Let's Macro V2 pin-out */
#define MATRIX_ROW_PINS { C6, B1, B3, D7 }
#define MATRIX_COL_PINS { D2, F7 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#endif
