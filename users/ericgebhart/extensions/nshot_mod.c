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
// Derived from nshot_mod by @possumvibes.
// Derived from one shot_mod by @Callum.

#include "nshot_mod.h"
#include USERSPACE_H

#undef NSHOT
#define NSHOT(KEYCODE, MOD, COUNT)              \
  {KEYCODE, MOD, COUNT, os_up_unqueued, 0},

#undef ONESHOT
#define ONESHOT(KEYCODE, MOD) NSHOT(KEYCODE, MOD, 1)
#define A_KEY(KEYCODE) case KEYCODE:
#define BLANK(...)

#define CANCEL_KEY BLANK
#define IGNORE_KEY BLANK
nshot_state_t  nshot_states[] = {
#include "nshot.def"
};
uint8_t        NUM_NSHOT_STATES = sizeof(nshot_states) / sizeof(nshot_state_t);

bool process_nshot_state(uint16_t keycode, keyrecord_t *record) {
  nshot_state_t *curr_state = NULL;

  switch(keycode){
  case CLEAR: {
    clear_oneshot_mods();
    clear_mods();
    return false;
  }
  case PANIC: {
    clear_oneshot_mods();
    clear_mods();
    if (get_oneshot_layer() != 0) {
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
    layer_move(0);
    return false;
  }
  }

  for (int i = 0; i < NUM_NSHOT_STATES; ++i) {
    curr_state = &nshot_states[i];

    if (keycode == curr_state->trigger) {
      if (record->event.pressed) {
        // Trigger keydown
        if (curr_state->state == os_up_unqueued) {
          register_code(curr_state->mod);
        }
        curr_state->state = os_down_unused;
        curr_state->count = 0;
      } else {
        // Trigger keyup
        switch (curr_state->state) {
        case os_down_unused:
          // If we didn't use the mod while trigger was held, queue it.
          curr_state->state = os_up_queued;
          break;
        case os_down_used:
          // If we did use the mod while trigger was held, unregister it.
          curr_state->state = os_up_unqueued;
          unregister_code(curr_state->mod);
          break;
        default:
          break;
        }
      }
} else {
       if (record->event.pressed) {
         if (is_nshot_cancel_key(keycode) && curr_state->state != os_up_unqueued) {
           // Cancel oneshot on designated cancel keydown.
           curr_state->state = os_up_unqueued;
           curr_state->count = 0;
           unregister_code(curr_state->mod);
         }
       } else {
         if (!is_nshot_ignored_key(keycode)) {
           // On non-ignored keyup, consider the oneshot used.
           switch (curr_state->state) {
           case os_down_unused:
             // The mod key is being held as a normal mod.
             curr_state->state = os_down_used;
             break;
           case os_up_queued:
             // The mod key is being used as an n-shot.
             // Increment the keys-used count.
             curr_state->count = curr_state->count + 1;

             // If the n-shot max has been reached, complete the n-shot.
             if (curr_state->count == curr_state->max_count) {
               curr_state->state = os_up_unqueued;
               curr_state->count = 0;
               unregister_code(curr_state->mod);
             }
             break;
           default:
             break;
           }
         }
       }
     }
   }
  return true;
}

// turn off the nshot/oneshot macros
#undef ONESHOT
#undef NSHOT
#define ONESHOT BLANK
#define NSHOT BLANK

#undef CANCEL_KEY
#undef IGNORE_KEY
#define IGNORE_KEY BLANK
#define CANCEL_KEY A_KEY
bool is_nshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
#include "nshot.def"
    return true;
  default:
    return false;
  }
}

#undef CANCEL_KEY
#undef IGNORE_KEY
#define CANCEL_KEY BLANK
#define IGNORE_KEY A_KEY
bool is_nshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
#include "nshot.def"
      return true;
    default:
            return false;
    }
}
