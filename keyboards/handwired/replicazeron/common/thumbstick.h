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

#include <stdint.h>
#include "state.h"
#include "quantum.h"

int16_t xPos;
int16_t yPos;

typedef struct {
    uint16_t angle;
    uint16_t  distance;
} thumbstick_polar_position_t;

typedef struct {
    bool w;
    bool a;
    bool s;
    bool d;
    bool shift;
} wasd_state_t;

thumbstick_polar_position_t thumbstick_polar_position ;

wasd_state_t wasd_state;
wasd_state_t last_wasd_state;

void init_wasd_state(void);

thumbstick_polar_position_t get_thumbstick_polar_position(int16_t x, int16_t y);

bool update_keystate(uint16_t angle_from, uint16_t angle_to, uint16_t angle);

void update_keycode(uint16_t keycode, bool keystate, bool last_keystate);

void thumbstick(controller_state_t controller_state);
