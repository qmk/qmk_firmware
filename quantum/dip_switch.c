/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2019 Drashna Jaelre (Christopher Courtney) <drashna@live.com>
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

#include "dip_switch.h"

// for memcpy
#include <string.h>

#if !defined(DIP_SWITCH_PINS)
#    error "No DIP switch pads defined by DIP_SWITCH_PINS"
#endif

#define NUMBER_OF_DIP_SWITCHES (sizeof(dip_switch_pad) / sizeof(pin_t))
static pin_t dip_switch_pad[]                              = DIP_SWITCH_PINS;
static bool  dip_switch_state[NUMBER_OF_DIP_SWITCHES]      = {0};
static bool  last_dip_switch_state[NUMBER_OF_DIP_SWITCHES] = {0};

__attribute__((weak)) void dip_switch_update_user(uint8_t index, bool active) {}

__attribute__((weak)) void dip_switch_update_kb(uint8_t index, bool active) { dip_switch_update_user(index, active); }

__attribute__((weak)) void dip_switch_update_mask_user(uint32_t state) {}

__attribute__((weak)) void dip_switch_update_mask_kb(uint32_t state) { dip_switch_update_mask_user(state); }

void dip_switch_init(void) {
    for (uint8_t i = 0; i < NUMBER_OF_DIP_SWITCHES; i++) {
        setPinInputHigh(dip_switch_pad[i]);
    }
    dip_switch_read(true);
}

void dip_switch_read(bool forced) {
    bool     has_dip_state_changed = false;
    uint32_t dip_switch_mask       = 0;

    for (uint8_t i = 0; i < NUMBER_OF_DIP_SWITCHES; i++) {
        dip_switch_state[i] = !readPin(dip_switch_pad[i]);
        dip_switch_mask |= dip_switch_state[i] << i;
        if (last_dip_switch_state[i] ^ dip_switch_state[i] || forced) {
            has_dip_state_changed = true;
            dip_switch_update_kb(i, dip_switch_state[i]);
        }
    }
    if (has_dip_state_changed) {
        dip_switch_update_mask_kb(dip_switch_mask);
    }
    memcpy(last_dip_switch_state, dip_switch_state, sizeof(&dip_switch_state));
}
