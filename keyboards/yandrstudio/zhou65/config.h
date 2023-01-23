/* Copyright 2021 JasonRen(biu)
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

/* key matrix pins */
#define MATRIX_ROW_PINS { A2, A1, B8, B7, C15 }
#define MATRIX_COL_PINS { B9, B6, B5, B4, B3, B1, B0, A7, A6, A5, A4, A3, A8, B15, B14 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define LED_CAPS_LOCK_PIN A15
#define LED_PIN_ON_STATE    0

/* enable the nkro when using the VIA. */
#define FORCE_NKRO

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
