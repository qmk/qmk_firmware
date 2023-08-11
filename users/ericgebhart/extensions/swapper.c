/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com, @possumvibes,@Callum.

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
// Derived from swapper by @Possumvibes and @Callum

#include "swapper.h"

swapper_state_t swapper_states[] = {
#ifdef SWAPPER_ENABLE
#include "swapper.def"
#endif
};
uint8_t         NUM_SWAPPER_STATES = sizeof(swapper_states) / sizeof(swapper_state_t);

// Based on https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
void process_swappers(uint16_t keycode, keyrecord_t *record) {
#ifdef SWAPPER_ENABLE
  swapper_state_t *curr_state = NULL;
  for (int i = 0; i < NUM_SWAPPER_STATES; ++i) {
    curr_state = &swapper_states[i];

    if (keycode == curr_state->forward_trigger) {
      if (record->event.pressed) {
        if (!curr_state->active) {
          curr_state->active = true;
          register_code16(curr_state->mod);
        }
        register_code16(curr_state->forward);
      } else {
        unregister_code16(curr_state->forward);
        // Don't unregister curr_state->mod until some other key is hit or released.
      }
    } else if (curr_state->active && keycode == curr_state->reverse_trigger) {
      if (record->event.pressed) {
        register_code16(curr_state->reverse);
      } else {
        unregister_code16(curr_state->reverse);
      }
    } else if (curr_state->active) {
      unregister_code16(curr_state->mod);
      curr_state->active = false;
    }
  }
#endif
}
