/* Copyright 2020-2022 Lorenzo Leonini
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

/* Microchip ADM42 sublicensing */
#define VENDOR_ID				0x04D8
#define PRODUCT_ID			0xE873

#define DEVICE_VER      0x0001
#define MANUFACTURER    Lorenzo Leonini
#define PRODUCT         ADM42

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define DIODE_DIRECTION ROW2COL

#define TAP_CODE_DELAY 1
#define DEBOUNCE 10

#if defined(CONSOLE_ENABLE)
	#define DEBUG_MATRIX_SCAN_RATE
#endif
