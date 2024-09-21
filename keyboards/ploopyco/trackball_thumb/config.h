/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT

// #define ROTATIONAL_TRANSFORM_ANGLE 0
#define POINTING_DEVICE_INVERT_Y

// If board has a debug LED, you can enable it by defining this
// #define DEBUG_LED_PIN F7

/* PMW3360 Settings */
#define POINTING_DEVICE_CS_PIN B0

#define ENCODER_BUTTON_COL 1
#define ENCODER_BUTTON_ROW 0

#define ENCODER_LOW_THRES_A 20
#define ENCODER_HIGH_THRES_A 75
#define ENCODER_LOW_THRES_B 20
#define ENCODER_HIGH_THRES_B 90
/* Custom encoder needs to specify just how many encoders we have */
#define NUM_ENCODERS 1

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F0 }
