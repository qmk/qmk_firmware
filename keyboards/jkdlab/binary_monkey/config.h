/*
 * Copyright 2021 JKDLAB. <jkdlab.co@gmail.com>
 * Copyright 2021 Jaehee <ljh34210329@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */
 
#pragma once

#include "config_common.h"

#define VENDOR_ID       0x4934
#define PRODUCT_ID      0x0101 
#define DEVICE_VER      0x0001
#define MANUFACTURER    JKDLAB.
#define PRODUCT         Binary_Monkey

#define MATRIX_ROWS 1
#define MATRIX_COLS 3
#define MATRIX_ROW_PINS { D0 }
#define MATRIX_COL_PINS { D1, D2, D3 }

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define USB_MAX_POWER_CONSUMPTION 100

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 2
