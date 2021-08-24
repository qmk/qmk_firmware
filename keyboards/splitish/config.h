/*
Copyright 2019 Reid Schneyer <reschneyer89@gmail.com>

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

#define VENDOR_ID      0xFEED
#define PRODUCT_ID     0x6464
#define DEVICE_VER     0x0001
#define MANUFACTIRER   Reid Schneyer
#define PRODUCT        Splitish

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_COL_PINS { F4 , F5 , F6 , F7 , B1 , B3 , C6 , D4 , D0 , D1 , D2 , D3 }
#define MATRIX_ROW_PINS { B4 , B5 , B2 , B6 }
#define DIODE_DIRECTION COL2ROW
#define UNUSED_PINS

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE

#define LOCKING_RESYNC_ENABLE


