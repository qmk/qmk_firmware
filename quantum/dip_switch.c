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

// for mmcpy
#include <string.h>


#if !defined(DIP_SWITCH_PINS)
#   error "No DIP switch pads defined by DIP_SWITCH_PINS"
#endif

#define NUMBER_OF_DIP_SWITCHES (sizeof(dip_switch_pad)/sizeof(pin_t))
static pin_t dip_switch_pad[] = DIP_SWITCH_PINS;
static bool dip_switch_state[NUMBER_OF_DIP_SWITCHES] = { 0 };
static bool last_dip_switch_state[NUMBER_OF_DIP_SWITCHES] = { 0 };


__attribute__((weak))
void dip_switch_update_user(uint8_t index, bool active) {}

__attribute__((weak))
void dip_switch_update_kb(uint8_t index, bool active) { dip_switch_update_user(index, active); }

void dip_switch_init(void) {
  for (uint8_t i = 0; i < NUMBER_OF_DIP_SWITCHES; i++) {
    setPinInputHigh(dip_switch_pad[i]);
  }
}


void dip_switch_read(void) {
    for (uint8_t i = 0; i < NUMBER_OF_DIP_SWITCHES; i++) {
        dip_switch_state[i] = !readPin(dip_switch_pad[i]);
        if (last_dip_switch_state[i] ^ dip_switch_state[i]) {
            dip_switch_update_kb(i, dip_switch_state[i]);
        }
    }
    memcpy(last_dip_switch_state, dip_switch_state, sizeof(&dip_switch_state));
}
