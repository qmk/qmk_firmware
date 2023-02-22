/*
 * Copyright (C) 2020 Longnald <support@longnald.com>
 * Copyright (C) 2020 Seaton Jiang <seaton@vtrois.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { F4, F0, B2, B3, D5 }
#define MATRIX_COL_PINS { F7, F6, F1, F5, B1, E6, D4, B7, D1, D2, D0, B4, B6, C6, C7 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 64
#    define RGBLIGHT_HUE_STEP 20
#    define RGBLIGHT_SAT_STEP 20
#    define RGBLIGHT_VAL_STEP 40
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#endif
