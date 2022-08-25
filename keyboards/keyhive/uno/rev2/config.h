/* Copyright 2020 Snipeye
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

#define RGBLIGHT_EFFECT_RAINBOW_MOOD

/* ENCODER */
#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B3 }

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* Uno default pinout */
#define DIRECT_PINS { \
    { D0 } \
}
#define UNUSED_PINS

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D1
#define RGBLED_NUM 1
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
