/*
Copyright 2019 Andy Poos <andpoos@gmail.com>

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

#include "octapoos.h"

userspace_config_t userspce_config;

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__((weak))
void matrix_init_keymap(void) {}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
  matrix_init_keymap();
}


__attribute__((weak))
void shutdown_keymap(void) {}

void shutdown_user(void) {
  shutdown_keymap();
}


__attribute__((weak))
void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
  suspend_power_down_keymap();
}

__attribute__((weak))
void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
  suspend_wakeup_init_keymap();
}


__attribute__((weak))
void matrix_scan_keymap(void) {}

// No global matrix scan code, so just run keymap's matrix
// scan function
void matrix_scan_user(void) {
  static bool has_ran_yet;
  if (!has_ran_yet) {
    has_ran_yet = true;
    startup_user();
  }
}

  __attribute__((weak))
  uint32_t layer_state_set_keymap(uint32_t state) {
    return state;
  }

  // on layer change, no matter where the change was initiated
  // Then runs keymap's layer change check
  uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return layer_state_set_keymap(state);
  }


  __attribute__((weak))
    uint32_t default_layer_state_set_keymap(uint32_t state) {
    return state;
  }

  // Runs state check and changes underglow color and animation
  uint32_t default_layer_state_set_user(uint32_t state) {
    state = default_layer_state_set_keymap(state);
    return state;
  }
