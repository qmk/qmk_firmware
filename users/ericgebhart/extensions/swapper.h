#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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

#include QMK_KEYBOARD_H
#include USERSPACE_H

typedef struct {
    bool     active;
    uint16_t mod;
    uint16_t forward;
    uint16_t reverse;
    uint16_t forward_trigger;
    uint16_t reverse_trigger;
} swapper_state_t;
extern swapper_state_t swapper_states[];
extern uint8_t         NUM_SWAPPER_STATES;

#undef SWAPPER_KEY
#define SWAPPER_KEY(KC, REVERSE_IT_KC, FWD_KC, REV_KC, MOD)     \
  {false, MOD, FWD_KC, REV_KC, KC, REVERSE_IT_KC},

void process_swappers(uint16_t keycode, keyrecord_t *record);
