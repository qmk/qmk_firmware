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

// Represents the four states an n-shot key can be in (from users/callum)
typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_down_unused,
    os_down_used,
} oneshot_state;

typedef struct {
    uint16_t      trigger;
    uint16_t      mod;
    uint8_t       max_count;
    oneshot_state state;
    uint8_t       count;
} nshot_state_t;

extern nshot_state_t nshot_states[];
extern uint8_t             NUM_NSHOT_STATES;


// Keys that should cancel the n-shot mod if tapped
bool is_nshot_cancel_key(uint16_t keycode);

// Keys that should not count towards n-shot usage (e.g., layer toggles)
bool is_nshot_ignored_key(uint16_t keycode);
