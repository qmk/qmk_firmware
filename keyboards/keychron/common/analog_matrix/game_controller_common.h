/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "stdint.h"
#include "analog_matrix_type.h"

/* Game controller axis */
enum {
    GC_AXIS_X = 0,
    GC_AXIS_Y,
    GC_AXIS_Z,
    GC_AXIS_RX,
    GC_AXIS_RY,
    GC_AXIS_RZ,
    GC_AXIS_MAX,
};

enum {
    GC_X_AXIS_LEFT = 0,
    GC_X_AXIS_RIGHT,
    GC_Y_AXIS_DOWN,
    GC_Y_AXIS_UP,
    GC_Z_AXIS_N,
    GC_Z_AXIS_P,
    GC_RX_AXIS_LEFT,
    GC_RX_AXIS_RIGHT,
    GC_RY_AXIS_DOWN,
    GC_RY_AXIS_UP,
    GC_RZ_AXIS_N,
    GC_RZ_AXIS_P,
    GC_MAX,
    GC_BUTTON_0,    // 13
    GC_BUTTON_31 = GC_BUTTON_0+31,
    GC_BUTTON_MAX,
};

enum {
    GC_MASK_XINPUT = 0x01 << 0,
    GC_MASK_TYPING = 0x01 << 1,
};

void game_controller_curve_init(point_t *pt);
void game_controller_mode_init(uint8_t mode);
bool game_controller_mode_get(uint8_t *data);
bool game_controller_mode_set(uint8_t mode);
bool game_controller_set_curve(point_t *pt);
bool game_controller_get_curve(uint8_t *data);
bool game_controller_xinput_enabled(void);
bool game_controller_type_enabled(void);
