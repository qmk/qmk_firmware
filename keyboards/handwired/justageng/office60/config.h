/* Copyright 2022 Jia Geng (@JiaGengChang)
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

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001

#define MANUFACTURER "Jia Geng"
#define PRODUCT "Office60"

#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS \
    { A8, B11, B10, B15, A10, A1, A2, A3, A4, A5, A6, A7, B0, B1 }
#define MATRIX_ROW_PINS \
    { B4, B3, A15, B13, B5 }
#define UNUSED_PINS \
    { A0, A9, A11, A12, C13, C14, C15 }

// the following is incompatible with link time optimization
// activated by including "-flto" in rules.mk
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// disable more qmk features
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define IGNORE_MOD_TAP_INTERRUPT
