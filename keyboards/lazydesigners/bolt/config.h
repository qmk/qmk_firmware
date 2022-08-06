/*
Copyright 2020 LAZYDESIGNERS

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { F0, C7, B6, D5 }
#define MATRIX_COL_PINS { F1, F4, F5, F6, F7, C6, B3, B7, D0, D3, D2, D1 }

#define DIODE_DIRECTION COL2ROW

/* RBG underglow */
#define RGB_DI_PIN E6
#ifdef RGB_DI_PIN
	#define RGBLIGHT_ANIMATIONS
	#define RGBLIGHT_SLEEP
	#define RGBLED_NUM 13
	/* #define RGBLIGHT_HUE_STEP 8 */
	/* #define RGBLIGHT_SAT_STEP 8 */
	/* #define RGBLIGHT_VAL_STEP 8 */
#endif
