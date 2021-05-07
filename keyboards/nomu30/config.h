/*
Copyright 2019 Naoto Takai

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x524B // recompile keys
#define PRODUCT_ID      0x4E31 // Nomu30
#define DEVICE_VER      0x0001
#define MANUFACTURER    recompile keys
#define PRODUCT         Nomu30

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 12

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 11
