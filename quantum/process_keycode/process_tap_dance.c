/* Copyright 2016 Jack Humbert
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
#include "action_tapping.h"

static uint16_t last_td;
static int8_t highest_td = -1;

void qk_tap_dance_pair_finished (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

  if (state->count == 1) {
    register_code16 (pair->kc1);
  } else if (state->count == 2) {
    register_code16 (pair->kc2);
  }
}

void qk_tap_dance_pair_reset (qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

  if (state->count == 1) {
    unregister_code16 (pair->kc1);
  } else if (state->count == 2) {
    unregister_code16 (pair->kc2);
  }
}

static inline void _process_tap_dance_action_fn (qk_tap_dance_state_t *state,
                                                 void *user_data,
                                                 qk_tap_dance_user_fn_t fn)
{
  if (fn) {
    fn(state, user_data);
  }
}

static inline void process_tap_dance_action_on_each_tap (qk_tap_dance_action_t *action)
{
  _process_tap_dance_action_fn (&action->state, action->user_data, action->fn.on_each_tap);
}

static inline void process_tap_dance_action_on_dance_finished (qk_tap_dance_action_t *action)
{
  if (action->state.finished)
    return;
  action->state.finished = true;
  add_mods(action->state.oneshot_mods);
  send_keyboard_report();
  _process_tap_dance_action_fn (&action->state, action->user_data, action->fn.on_dance_finished);
}

static inline void process_tap_dance_action_on_reset (qk_tap_dance_action_t *action)
{
  _process_tap_dance_action_fn (&action->state, action->user_data, action->fn.on_reset);
  del_mods(action->state.oneshot_mods);
  send_keyboard_report();
}

bool process_tap_dance(uint16_t keycode, keyrecord_t *record) {
  uint16_t idx = keycode - QK_TAP_DANCE;
  qk_tap_dance_action_t *action;

  if (last_td && last_td != keycode) {
    (&tap_dance_actions[last_td - QK_TAP_DANCE])->state.interrupted = true;
  }

  switch(keycode) {
  case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
    if ((int16_t)idx > highest_td)
      highest_td = idx;
    action = &tap_dance_actions[idx];

    action->state.pressed = record->event.pressed;
    if (record->event.pressed) {
      action->state.keycode = keycode;
      action->state.count++;
      action->state.timer = timer_read();
      action->state.oneshot_mods = get_oneshot_mods();
      process_tap_dance_action_on_each_tap (action);

      if (last_td && last_td != keycode) {
        qk_tap_dance_action_t *paction = &tap_dance_actions[last_td - QK_TAP_DANCE];
        paction->state.interrupted = true;
        process_tap_dance_action_on_dance_finished (paction);
        reset_tap_dance (&paction->state);
      }

      last_td = keycode;
    }

    break;

  default:
    if (!record->event.pressed)
      return true;

    if (highest_td == -1)
      return true;

    for (int i = 0; i <= highest_td; i++) {
      action = &tap_dance_actions[i];
      if (action->state.count == 0)
        continue;
      action->state.interrupted = true;
      process_tap_dance_action_on_dance_finished (action);
      reset_tap_dance (&action->state);
    }
    break;
  }

  return true;
}

void matrix_scan_tap_dance () {
  if (highest_td == -1)
    return;

for (int i = 0; i <= highest_td; i++) {
    qk_tap_dance_action_t *action = &tap_dance_actions[i];

    if (action->state.count && timer_elapsed (action->state.timer) > TAPPING_TERM) {
      process_tap_dance_action_on_dance_finished (action);
      reset_tap_dance (&action->state);
    }
  }
}

void reset_tap_dance (qk_tap_dance_state_t *state) {
  qk_tap_dance_action_t *action;

  if (state->pressed)
    return;

  action = &tap_dance_actions[state->keycode - QK_TAP_DANCE];

  process_tap_dance_action_on_reset (action);

  state->count = 0;
  state->interrupted = false;
  state->finished = false;
  last_td = 0;
}
