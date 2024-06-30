/* Copyright 2023 9R
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

#include "replicazeron.h"

#include <stdint.h>
#include "state.h"
#include "thumbstick.h"

uint8_t shiftbits;

char stringbuffer[8];

void draw_oled(controller_state_t controller_state);

void draw_mode(controller_state_t controller_state);

void draw_thumb_debug(thumbstick_polar_position_t thumbstick_polar_position);

void draw_wasd_key(wasd_state_t wasd_state);
