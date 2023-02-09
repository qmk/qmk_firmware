/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>, @possumvibes

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
// Derived from mod_lock by @possumvibes.

#include "mod_lock.h"

#undef MODL
#define MODL(KEYCODE, MODKC)                    \
  {false, MODKC, KEYCODE},

#define A_KEY(KEYCODE) case KEYCODE:
#define BLANK(...)

#undef IGNORE_KC
#define IGNORE_KC BLANK

mod_lock_state_t modlock_states[] = {
#ifdef MOD_LOCK_ENABLE
#include "mod_lock.def"
#endif
};
uint8_t        NUM_MODLOCK_STATES = sizeof(modlock_states) / sizeof(mod_lock_state_t);

void process_mod_lock(uint16_t keycode, keyrecord_t *record) {
#ifdef MOD_LOCK_ENABLE
  mod_lock_state_t *curr_state = NULL;

  for (int i = 0; i < NUM_MODLOCK_STATES; ++i) {
    curr_state = &modlock_states[i];

    if (keycode == curr_state->trigger) {
      if (record->event.pressed) {
        if (curr_state->locking) {
          unregister_code(curr_state->mod);
        } else {
          register_code(curr_state->mod);
        }

        curr_state->locking = !curr_state->locking;
      }
    } else {
      // check for cancel condition on keydown and keyup
      if (curr_state->locking && is_mod_lock_cancel_key(keycode)) {
        unregister_code(curr_state->mod);
        curr_state->locking = false;
      }
    }
  }
#endif
}

#undef MODL
#undef IGNORE_KC
#define MODL BLANK
#define IGNORE_KC A_KEY
bool is_mod_lock_cancel_key(uint16_t keycode) {
    // Mod locks are exclusively used on the nav layer.
    // any key besides nav keys should cancel the lock.
    switch (keycode) {
#ifdef MOD_LOCK_ENABLE
#include "mod_lock.def"
#endif
      return false;
    default:
            return true;
    }
}
