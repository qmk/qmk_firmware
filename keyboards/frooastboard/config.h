/* Copyright 2021 frooastside
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define MANUFACTURER    frooastside
#define PRODUCT         Frooastboard

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 2

#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 1

#define RGB_DI_PIN B4
#define RGBLED_NUM 8

#define RGBLIGHT_SLEEP

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#define RGBLIGHT_DEFAULT_HUE 234

#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_DEFAULT_VAL 190

#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_SNAKE

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD + 2
