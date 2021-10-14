/*
Copyright 2021 @Yowkees
Copyright 2021 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include <stdint.h>

// trackball_init initializes trackball related resources.
void trackball_init(void);

void trackball_secondary_availablity(bool available);

// trackball_has should returns status of trackball availability.  it delegates
// is_keyboard_master() as default, but it can be overridden by keyboards or
// keymaps.
bool trackball_has(void);

typedef struct {
    int16_t x;
    int16_t y;
} trackball_delta_t;

// These functions are design to be called by firmware.

bool trackball_fetch_sensor(trackball_delta_t *p);

void trackball_apply_delta(int8_t num, const trackball_delta_t *delta);

void trackball_reset_delta(int8_t num);

bool trackball_consume_delta(int8_t num, int16_t div, trackball_delta_t *out);
