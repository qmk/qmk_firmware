/* Copyright 2021 Nix Keyboards
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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS \
    { B3, B7, F5, F4, F1 }
#define MATRIX_COL_PINS \
    { F0, F7, C7, C6, B6, B5, B4, D7, D6, D4, D5, D3, D2, D1, D0 }
#define DIODE_DIRECTION COL2ROW

/* encoder */
#define ENCODERS_PAD_A \
    { B0 }
#define ENCODERS_PAD_B \
    { B1 }
#define ENCODER_RESOLUTION 4

/* Debounce reduces chatter */
#define DEBOUNCE 5

/* Set the Bootmagic key to the escape key (default key doesn't exist 0,0) */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1
