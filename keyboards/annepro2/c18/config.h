/*
 * Copyright (c) 2018 Charlie Waters
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

/* USB Device descriptor parameter */
#define VENDOR_ID 0xfeed
#define PRODUCT_ID 0xac18
#define DEVICE_VER 0x1337
#define MANUFACTURER Obins
#define PRODUCT Anne Pro 2(c18)QMK
// key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
// layer size: MATRIX_ROWS * MATRIX_COLS * sizeof(uint16_t) = 140 bytes
