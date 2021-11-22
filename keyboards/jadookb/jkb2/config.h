 /* Copyright 2021 Wizard-GG
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

#define VENDOR_ID       0x4A4B // "JK"
#define PRODUCT_ID      0x3225 // "2%"
#define DEVICE_VER      0x0001
#define MANUFACTURER JadooKB
#define PRODUCT      JKB2

#define MATRIX_ROWS 1
#define MATRIX_COLS 2

#define MATRIX_ROW_PINS { B1 }
#define MATRIX_COL_PINS { B3 ,B2}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
