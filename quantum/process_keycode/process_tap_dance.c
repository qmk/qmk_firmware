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

static uint16_t active_td;
static uint16_t last_tap_time;

void qk_tap_dance_pair_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 2) {
        register_code16(pair->kc2);
        state->finished = true;
    }
}

void qk_tap_dance_pair_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    register_code16(pair->kc1);
}

void qk_tap_dance_pair_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        wait_ms(TAP_CODE_DELAY);
        unregister_code16(pair->kc1);
    } else if (state->count == 2) {
        unregister_code16(pair->kc2);
    }
}

void qk_tap_dance_dual_role_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *pair = (qk_tap_dance_dual_role_t *)user_data;

    if (state->count == 2) {
        layer_move(pair->layer);
        state->finished = true;
    }
}

void qk_tap_dance_dual_role_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *pair = (qk_tap_dance_dual_role_t *)user_data;

    if (state->count == 1) {
        register_code16(pair->kc);
    } else if (state->count == 2) {
        pair->layer_function(pair->layer);
    }
}

void qk_tap_dance_dual_role_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_dual_role_t *pair = (qk_tap_dance_dual_role_t *)user_data;

    if (state->count == 1) {
        wait_ms(TAP_CODE_DELAY);
        unregister_code16(pair->kc);
    }
}

static inline void _process_tap_dance_action_fn(qk_tap_dance_state_t *state, void *user_data, qk_tap_dance_user_fn_t fn) {
    if (fn) {
        fn(state, user_data);
    }
}

static inline void process_tap_dance_action_on_each_tap(qk_tap_dance_action_t *action) {
    action->state.count++;
    action->state.weak_mods = get_mods();
    action->state.weak_mods |= get_weak_mods();
#ifndef NO_ACTION_ONESHOT
    action->state.oneshot_mods = get_oneshot_mods();
#endif
    _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_each_tap);
}

static inline void process_tap_dance_action_on_reset(qk_tap_dance_action_t *action) {
    _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_reset);
    del_weak_mods(action->state.weak_mods);
#ifndef NO_ACTION_ONESHOT
    del_mods(action->state.oneshot_mods);
#endif
    send_keyboard_report();
    action->state = (const qk_tap_dance_state_t){0};
}

static inline void process_tap_dance_action_on_dance_finished(qk_tap_dance_action_t *action) {
    if (!action->state.finished) {
        action->state.finished = true;
        add_weak_mods(action->state.weak_mods);
#ifndef NO_ACTION_ONESHOT
        add_mods(action->state.oneshot_mods);
#endif
        send_keyboard_report();
        _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_dance_finished);
    }
    active_td = 0;
    if (!action->state.pressed) {
        // There will not be a key release event, so reset now.
        process_tap_dance_action_on_reset(action);
    }
}

bool preprocess_tap_dance(uint16_t keycode, keyrecord_t *record) {
    qk_tap_dance_action_t *action;

    if (!record->event.pressed) return false;

    if (!active_td || keycode == active_td) return false;

    action                             = &tap_dance_actions[TD_INDEX(active_td)];
    action->state.interrupted          = true;
    action->state.interrupting_keycode = keycode;
    process_tap_dance_action_on_dance_finished(action);

    // Tap dance actions can leave some weak mods active (e.g., if the tap dance is mapped to a keycode with
    // modifiers), but these weak mods should not affect the keypress which interrupted the tap dance.
    clear_weak_mods();

    // Signal that a tap dance has been finished due to being interrupted,
    // therefore the keymap lookup for the currently processed event needs to
    // be repeated with the current layer state that might have been updated by
    // the finished tap dance.
    return true;
}

bool process_tap_dance(uint16_t keycode, keyrecord_t *record) {
    qk_tap_dance_action_t *action;

    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            action = &tap_dance_actions[TD_INDEX(keycode)];

            action->state.pressed = record->event.pressed;
            if (record->event.pressed) {
                last_tap_time = timer_read();
                process_tap_dance_action_on_each_tap(action);
                active_td = action->state.finished ? 0 : keycode;
            } else {
                if (action->state.finished) {
                    process_tap_dance_action_on_reset(action);
                }
            }

            break;
    }

    return true;
}

void tap_dance_task() {
    qk_tap_dance_action_t *action;

    if (!active_td || timer_elapsed(last_tap_time) <= GET_TAPPING_TERM(active_td, &(keyrecord_t){})) return;

    action = &tap_dance_actions[TD_INDEX(active_td)];
    if (!action->state.interrupted) {
        process_tap_dance_action_on_dance_finished(action);
    }
}

void reset_tap_dance(qk_tap_dance_state_t *state) {
    active_td = 0;
    process_tap_dance_action_on_reset((qk_tap_dance_action_t *)state);
}
