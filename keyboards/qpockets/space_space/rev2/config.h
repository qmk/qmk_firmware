/* Copyright 2021 qpockets
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
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

#define MATRIX_ROW_PINS \
    { B1, B0, D5, B6 }
#define MATRIX_COL_PINS \
    { C6, F6, F1, F4, F5, E6, D6, B2, B5, D3, D2 }

#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* ROTARY ENCODERS */
#define ENCODERS_PAD_A \
    { B4, C7 }
#define ENCODERS_PAD_B \
    { D7, F7 }

#define ENCODER_RESOLUTION 3

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE

#define RGB_DI_PIN F0
#define RGBLED_NUM 4

#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGBLIGHT_DEFAULT_HUE 130
