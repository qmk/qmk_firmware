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


#define MATRIX_ROWS     5
#define MATRIX_COLS     14
#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS \
    { B12, B13, B14, A8, A9, A10, A15, B3, B4, B5, B6, B7, B8, B9 }
#define MATRIX_ROW_PINS \
    { A0, A1, A2, A3, A4 }
#define UNUSED_PINS \
    { A5, A6, A7, A13, A14, B0, B1, B2, B10, B11, B15, C13, C14, C15 }


// disable more qmk features
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define IGNORE_MOD_TAP_INTERRUPT

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
