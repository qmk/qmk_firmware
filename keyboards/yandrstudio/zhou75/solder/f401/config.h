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
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

//                        0    1    2    3     4    5    6   7    8    9    10   11   12  13   14   15   16   17
#define MATRIX_COL_PINS { A8,  B15, B14, B13,  B12, B1,  B0, A7,  B7,  B6,  B5,  B4,  B3, A15, B10, B8 }
#define MATRIX_ROW_PINS { B9,  A6,  A5,  A4,   A3,  A2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL


#ifdef ENCODER_ENABLE

#define ENCODERS_PAD_A { A0, A9 }
#define ENCODERS_PAD_B { A1, A10 }

#define ENCODER_RESOLUTIONS { 4, 4 }

#endif


#define LED_CAPS_LOCK_PIN    C13
#define LED_PIN_ON_STATE     0
