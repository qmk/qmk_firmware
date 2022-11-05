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

enum key_repeater_state {
    KR_DISABLED,
    KR_WAITING,
    KR_BUTTON_DOWN,

    __KR_STATE_COUNT
};

struct key_repeater_t {
    int key;
    uint32_t key_duration_min;
    uint32_t key_duration_max;
    uint32_t wait_duration_min;
    uint32_t wait_duration_max;

    enum key_repeater_state state;
    uint32_t previous_button_down;
    uint32_t previous_button_up;
    uint32_t key_duration;
    uint32_t wait_duration;
};

// Utility functions
uint32_t get_rand(uint32_t min, uint32_t max);

// State handler function table
void kr_waiting(struct key_repeater_t *kr);
void kr_button_down(struct key_repeater_t *kr);

typedef void (*kr_state_handler)(struct key_repeater_t *kr);
static kr_state_handler kr_state_handlers[] = {
    [KR_DISABLED] = NULL,
    [KR_WAITING] = kr_waiting,
    [KR_BUTTON_DOWN] = kr_button_down,
};

struct key_repeater_t* kr_new(struct key_repeater_config_t* cfg) {
    struct key_repeater_t* kr = (struct key_repeater_t*)malloc(sizeof(struct key_repeater_t));

    if (cfg) {
        kr->key = cfg->key;
        kr->key_duration_min = cfg->key_duration_min;
        kr->key_duration_max = cfg->key_duration_max;
        kr->wait_duration_min = cfg->wait_duration_min;
        kr->wait_duration_max = cfg->wait_duration_max;
    } else {
        kr->key = KC_NO;
        kr->key_duration_min = 0;
        kr->key_duration_max = 0;
        kr->wait_duration_min = 0;
        kr->wait_duration_max = 0;
    }
 
    kr->state = KR_DISABLED;
    kr->previous_button_down = 0;
    kr->previous_button_up = 0;
    kr->key_duration = 0;
    kr->wait_duration = 0;
    
    return kr;
}

void kr_free(struct key_repeater_t **kr) {
    if (kr && *kr) {
        free(*kr);
        *kr = NULL;
    }
}

void kr_enable(struct key_repeater_t *kr) {
    if (!kr || kr->key == KC_NO) {
        return;
    }

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
    if (!kr || kr->key == KC_NO) {
        return;
    }

    if (kr->state == KR_BUTTON_DOWN) {
        unregister_code(kr->key);
    }
    kr->state = KR_DISABLED;
}

void kr_poll(struct key_repeater_t *kr) {
    if (!kr || kr->key == KC_NO) {
        return;
    }

    kr_state_handler handler = kr_state_handlers[kr->state];
    if (handler) {
        (handler)(kr);
    }
}

void kr_waiting(struct key_repeater_t *kr) {
    if (!kr || kr->key == KC_NO) {
        return;
    }

    uint32_t now = timer_read32();
    if (now > (kr->previous_button_up + kr->wait_duration)) {
        kr->state = KR_BUTTON_DOWN;
        kr->previous_button_down = now;
        if (kr->key_duration_min == kr->key_duration_max) {
            kr->key_duration = kr->key_duration_min;
        } else {
            kr->key_duration = get_rand(kr->key_duration_min, kr->key_duration_max);
        }
        register_code(kr->key);
    }
}

void kr_button_down(struct key_repeater_t *kr) {
    if (!kr || kr->key == KC_NO) {
        return;
    }

    uint32_t now = timer_read32();
    if (now > (kr->previous_button_down + kr->key_duration)) {
        kr->state = KR_WAITING;
        kr->previous_button_up = now;
        if (kr->wait_duration_min == kr->wait_duration_max) {
            kr->wait_duration = kr->wait_duration_min;
        } else {
            kr->wait_duration = get_rand(kr->wait_duration_min, kr->wait_duration_max);
        }
        unregister_code(kr->key);
    }
}

// Return a random number between min and max; assumes that the random number
// generator has already been seeded
uint32_t get_rand(uint32_t min, uint32_t max) {
    return (rand() % (max - min)) + min;
}
