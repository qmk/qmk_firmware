
/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "drashna.h"

__attribute__((aligned(8))) typedef struct {
    bool audio_enable;
    bool audio_clicky_enable;
    bool tap_toggling;
    bool unicode_mode;
    bool swap_hands;
} user_runtime_config_t;

extern user_runtime_config_t user_state;

void keyboard_post_init_transport_sync(void);
