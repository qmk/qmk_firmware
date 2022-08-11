/*
Copyright 2019 Neil Kettle

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

#define MATRIX_ROWS 6
#define MATRIX_COLS 15

#define RIGHT_HALF

/* LED indicator lights */
#define LED_CAPS_LOCK_PIN D1
#define LED_NUM_LOCK_PIN D0
#define LED_SCROLL_LOCK_PIN D6

/* RGB underglow */
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 250 /* The maximum brightness level */
#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_ANIMATIONS
