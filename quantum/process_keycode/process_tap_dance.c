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

#ifndef NO_ACTION_ONESHOT
uint8_t get_oneshot_mods(void);
#endif

static uint16_t last_td;
static int8_t   highest_td = -1;

void qk_tap_dance_pair_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 2) {
        register_code16(pair->kc2);
        state->finished = true;
    }
}

void qk_tap_dance_pair_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        register_code16(pair->kc1);
    } else if (state->count == 2) {
        register_code16(pair->kc2);
    }
}

void qk_tap_dance_pair_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
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
        unregister_code16(pair->kc);
    }
}

static inline void _process_tap_dance_action_fn(qk_tap_dance_state_t *state, void *user_data, qk_tap_dance_user_fn_t fn) {
    if (fn) {
        fn(state, user_data);
    }
}

static inline void process_tap_dance_action_on_each_tap(qk_tap_dance_action_t *action) { _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_each_tap); }

static inline void process_tap_dance_action_on_dance_finished(qk_tap_dance_action_t *action) {
    if (action->state.finished) return;
    action->state.finished = true;
    add_mods(action->state.oneshot_mods);
    add_weak_mods(action->state.weak_mods);
    send_keyboard_report();
    _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_dance_finished);
}

static inline void process_tap_dance_action_on_reset(qk_tap_dance_action_t *action) {
    _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_reset);
    del_mods(action->state.oneshot_mods);
    del_weak_mods(action->state.weak_mods);
    send_keyboard_report();
}

void preprocess_tap_dance(uint16_t keycode, keyrecord_t *record) {
    qk_tap_dance_action_t *action;

    if (!record->event.pressed) return;

    if (highest_td == -1) return;

    for (int i = 0; i <= highest_td; i++) {
        action = &tap_dance_actions[i];
        if (action->state.count) {
            if (keycode == action->state.keycode && keycode == last_td) continue;
            action->state.interrupted          = true;
            action->state.interrupting_keycode = keycode;
            process_tap_dance_action_on_dance_finished(action);
            reset_tap_dance(&action->state);

            // Tap dance actions can leave some weak mods active (e.g., if the tap dance is mapped to a keycode with
            // modifiers), but these weak mods should not affect the keypress which interrupted the tap dance.
            clear_weak_mods();
        }
    }
}

bool process_tap_dance(uint16_t keycode, keyrecord_t *record) {
    uint16_t               idx = keycode - QK_TAP_DANCE;
    qk_tap_dance_action_t *action;

    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            if ((int16_t)idx > highest_td) highest_td = idx;
            action = &tap_dance_actions[idx];

            action->state.pressed = record->event.pressed;
            if (record->event.pressed) {
                action->state.keycode = keycode;
                action->state.count++;
                action->state.timer = timer_read();
#ifndef NO_ACTION_ONESHOT
                action->state.oneshot_mods = get_oneshot_mods();
#else
                action->state.oneshot_mods = 0;
#endif
                action->state.weak_mods = get_mods();
                action->state.weak_mods |= get_weak_mods();
                process_tap_dance_action_on_each_tap(action);

                last_td = keycode;
            } else {
                if (action->state.count && action->state.finished) {
                    reset_tap_dance(&action->state);
                }
            }

            break;
    }

    return true;
}

void matrix_scan_tap_dance() {
    if (highest_td == -1) return;
    uint16_t tap_user_defined;

    for (uint8_t i = 0; i <= highest_td; i++) {
        qk_tap_dance_action_t *action = &tap_dance_actions[i];
        if (action->custom_tapping_term > 0) {
            tap_user_defined = action->custom_tapping_term;
        } else {
#ifdef TAPPING_TERM_PER_KEY
            tap_user_defined = get_tapping_term(action->state.keycode, NULL);
#else
            tap_user_defined = TAPPING_TERM;
#endif
        }
        if (action->state.count && timer_elapsed(action->state.timer) > tap_user_defined) {
            process_tap_dance_action_on_dance_finished(action);
            reset_tap_dance(&action->state);
        }
    }
}

void reset_tap_dance(qk_tap_dance_state_t *state) {
    qk_tap_dance_action_t *action;

    if (state->pressed) return;

    action = &tap_dance_actions[state->keycode - QK_TAP_DANCE];

    process_tap_dance_action_on_reset(action);

    state->count                = 0;
    state->interrupted          = false;
    state->finished             = false;
    state->interrupting_keycode = 0;
    last_td                     = 0;
}
