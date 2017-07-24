/* Copyright 2017 Peter Jones <pjones@devalot.com>
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
#include "quantum.h"

static qk_dual_role_state_t dual_role_state = {0, 0, 0, false};

// An existing dual role was interrupted.
static inline void dual_role_interrupted(void) {
  qk_dual_role_action_t *action;
  dual_role_state.interrupted = true;

  for (uint8_t i=0; i <= dual_role_state.max; i++) {
    action = &dual_role_keys[i];
    if (action->active) register_mods(action->mod);
  }
}

// Start tracking a dual role key.
static inline void dual_role_start(qk_dual_role_action_t *action) {
  if (dual_role_state.count && dual_role_state.interrupted) {
    // There is already an active modifier that has been interrupted.
    // Therefore this key will act like a normal, non-dual-role key.
    dual_role_interrupted();
    register_code(action->key);
    return;
  }

  action->active = true;
  dual_role_state.count++;
  dual_role_state.timer = timer_read();

  if (dual_role_state.count == 1) {
    dual_role_state.interrupted = false;
  }
}

// The dual role should end now.
static inline void dual_role_end(qk_dual_role_action_t *action) {
  if (!action->active) {
    // This key was acting like a normal key.
    unregister_code(action->key);
    return;
  }


  // Clean up after the key.
  action->active = false;
  dual_role_state.count--;

  // See if this dual role key should be used as a normal key or a
  // modifier.  When more than one dual-role keys is held down we need
  // to consider that releasing one of the dual-role keys might mean
  // it should have been used as a normal key.
  if (dual_role_state.count &&
      !dual_role_state.interrupted &&
      timer_elapsed(dual_role_state.timer) < TAPPING_TERM)
  {
    dual_role_interrupted();
    register_code(action->key);
    unregister_code(action->key);
  } else if (!dual_role_state.count &&
             !dual_role_state.interrupted &&
             timer_elapsed(dual_role_state.timer) < TAPPING_TERM)
  {
    register_code(action->key);
    unregister_code(action->key);
  }
  else {
    unregister_mods(action->mod);
  }
}

// Called for each key press.
bool process_dual_role(uint16_t keycode, keyrecord_t *record) {
  qk_dual_role_action_t *action;
  uint16_t index = 0;

  switch(keycode) {
  case QK_DUAL_ROLE ... QK_DUAL_ROLE_MAX:
    index = keycode - QK_DUAL_ROLE;
    action = &dual_role_keys[index];

    if (record->event.pressed) {
      if (index > dual_role_state.max) dual_role_state.max = index;
      dual_role_start(action);
    } else {
      dual_role_end(action);
    }

    return false;

  default:
    if (record->event.pressed && dual_role_state.count)
      dual_role_interrupted();
  }

  return true;
}
