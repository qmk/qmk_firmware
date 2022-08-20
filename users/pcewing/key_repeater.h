/*
 * Copyright 2022 Paul Ewing
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

enum key_repeater_state {
    KR_DISABLED,
    KR_WAITING,
    KR_BUTTON_DOWN,

    __KR_STATE_COUNT
};

struct key_repeater_t {
    int key;

    enum key_repeater_state state;
    uint32_t previous_button_down;
    uint32_t previous_button_up;

    uint32_t key_duration;
    const uint32_t key_duration_min;
    const uint32_t key_duration_max;

    uint32_t wait_duration;
    const uint32_t wait_duration_min;
    const uint32_t wait_duration_max;
};

void kr_enable(struct key_repeater_t *kr);
void kr_disable(struct key_repeater_t *kr);
void kr_poll(struct key_repeater_t *kr);
