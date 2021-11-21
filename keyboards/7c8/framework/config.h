/* Copyright 2020 Steven Nguyen
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

#define VENDOR_ID 0x77C8
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0000
#define MANUFACTURER 7c8
#define PRODUCT Framework

#define MATRIX_ROWS 10
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { B0, B1, D7, B2, D6, B3, D5, B4, D4, B5 }
#define MATRIX_COL_PINS { C0, C1, C2, C3, C4, C5 }
#define ENCODERS_PAD_A  { D0 }
#define ENCODERS_PAD_B  { D1 }

#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 16
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LEADER_TIMEOUT 250
#define LEADER_PER_KEY_TIMING 150
