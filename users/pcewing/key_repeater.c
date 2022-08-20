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

#include "key_repeater.h"
#include <stdlib.h>
#include QMK_KEYBOARD_H

// State handler functions
void kr_waiting(struct key_repeater_t *kr);
void kr_button_down(struct key_repeater_t *kr);

// Utility functions
uint32_t get_rand(uint32_t min, uint32_t max);

typedef void (*kr_state_handler)(struct key_repeater_t *kr);
static kr_state_handler kr_state_handlers[] = {
    [KR_DISABLED] = NULL,
    [KR_WAITING] = kr_waiting,
    [KR_BUTTON_DOWN] = kr_button_down,
};

void kr_enable(struct key_repeater_t *kr) {
    if (kr->state != KR_DISABLED) {
        return;
    }
    kr->state = KR_WAITING;
    kr->previous_button_down = 0;
    kr->previous_button_up = 0;
    kr->key_duration = 0;
    kr->wait_duration = 0;
}

void kr_disable(struct key_repeater_t *kr) {
    if (kr->state == KR_BUTTON_DOWN) {
        unregister_code(kr->key);
    }
    kr->state = KR_DISABLED;
}

void kr_poll(struct key_repeater_t *kr) {
    kr_state_handler handler = kr_state_handlers[kr->state];
    if (handler) {
        (handler)(kr);
    }
}

void kr_waiting(struct key_repeater_t *kr) {
    uint32_t now = timer_read32();
    if (now > (kr->previous_button_up + kr->wait_duration)) {
        kr->state = KR_BUTTON_DOWN;
        kr->previous_button_down = now;
        kr->key_duration = get_rand(kr->key_duration_min, kr->key_duration_max);
        register_code(kr->key);
    }
}

void kr_button_down(struct key_repeater_t *kr) {
    uint32_t now = timer_read32();
    if (now > (kr->previous_button_down + kr->key_duration)) {
        kr->state = KR_WAITING;
        kr->previous_button_up = now;
        kr->wait_duration = get_rand(kr->wait_duration_min, kr->wait_duration_max);
        unregister_code(kr->key);
    }
}

// Return a random number between min and max; assumes that the random number
// generator has already been seeded
uint32_t get_rand(uint32_t min, uint32_t max) {
    return (rand() % (max - min)) + min;
}
