/* Copyright 2021 DZTECH <moyi4681@live.cn>
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

#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

#undef RGB_MATRIX_STARTUP_MODE
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL

#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 8

//#define QMK_KEYS_PER_SCAN 12nn

#define MOUSEKEY_DELAY 	0
#define MOUSEKEY_INTERVAL 	1
#define MOUSEKEY_MOVE_DELTA 	1
#define MOUSEKEY_MAX_SPEED 	25
#define MOUSEKEY_TIME_TO_MAX 	255
#define MOUSEKEY_WHEEL_DELAY 	0
#define MOUSEKEY_WHEEL_INTERVAL 	100
#define MOUSEKEY_WHEEL_MAX_SPEED 	100
#define MOUSEKEY_WHEEL_TIME_TO_MAX 	100
