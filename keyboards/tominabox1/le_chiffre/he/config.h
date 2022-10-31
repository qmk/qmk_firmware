/* Copyright 2022 tominabox1
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

/* COL2ROW, ROW2COL*/
#undef DIODE_DIRECTION
#define DIODE_DIRECTION COL2ROW

#define MATRIX_ROW_PINS { B3, D4, F1, C6 }
#define MATRIX_COL_PINS { F4, F5, B0, B2, B1, B4, D7, C7, D2, F7 }

/* Define encoder pads */
#define ENCODERS_PAD_A { D5 }
#define ENCODERS_PAD_B { D3 }

/*
 * WS2812 Underglow Matrix options
 */
#define RGB_DI_PIN F0
