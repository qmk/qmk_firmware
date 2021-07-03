/*
Copyright 2021 Marius Gavrilescu <marius@ieval.ro>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x5474
#define DEVICE_VER      0x0001
#define MANUFACTURER    TypeTheory
#define PRODUCT         Keyboard

#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define MATRIX_COL_PINS { B3, B2, B6, F0, F1, C7, B7, D5 }
#define MATRIX_COL_PINS_RIGHT { C7, F1, F0, B6, B2, B3, B7, D5 }
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1 }

#define SOFT_SERIAL_PIN D1
#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5

/* Make mod-tap more reasonable */
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD

#define USE_SERIAL
#define EE_HANDS
