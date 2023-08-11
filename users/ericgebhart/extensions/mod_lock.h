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

#include USERSPACE_H

typedef struct {
    bool          locking;
    uint16_t      mod;
    uint16_t      trigger;
} mod_lock_state_t;

extern mod_lock_state_t mod_lock_states[];
extern uint8_t          NUM_MODLOCK_STATES;

// Custom mod-locking functionality that registers the mod and
// keeps it registered until the trigger key is tapped again
// or until a specified cancel key is tapped.
void process_mod_lock(uint16_t keycode, keyrecord_t *record);

bool is_mod_lock_cancel_key(uint16_t keycode);

#undef IGNORE_KC
#define IGNORE_KC(KC)                           \
  case KC:
