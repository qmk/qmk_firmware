/*
Copyright 2018 listofoptions <listofoptions@gmail.com>

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

#define VENDOR_ID           0xFEED
#define PRODUCT_ID          0x6060
#define DEVICE_VER          1
#define MANUFACTURER        QMK
#define PRODUCT             5291 keyboard converter
#define DESCRIPTION         5291 keyboard converter

#define MATRIX_ROWS         24
#define MATRIX_COLS         4

#define MATRIX_ROW_PINS   {B2, B3, B4, B5, B6}
#define MATRIX_COL_PINS   {B0, B1}
#define MATRIX_DATA_PIN   D0
#define MATRIX_STROBE_PIN D1
#define LED_PIN           D6


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE    0
