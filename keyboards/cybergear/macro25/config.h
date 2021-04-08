/* Copyright 2021 CyberGear Marius Kavoliunas
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0x69A1
#define DEVICE_VER      0x0001
#define MANUFACTURER    CyberGear
#define PRODUCT         Macro25 (mk-macro-01)

#define MATRIX_ROWS 2
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { E6, B4 }
#define MATRIX_COL_PINS { B1, F7, F6, F5, F4 }

#define DIODE_DIRECTION COL2ROW

