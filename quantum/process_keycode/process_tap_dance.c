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

#include "process_tap_dance.h"
#include "quantum.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "action_util.h"
#include "timer.h"
#include "wait.h"
#include "keymap_introspection.h"

static uint16_t active_td;

#ifndef TAP_DANCE_MAX_SIMULTANEOUS
#    define TAP_DANCE_MAX_SIMULTANEOUS 3
#endif

static tap_dance_state_t tap_dance_states[TAP_DANCE_MAX_SIMULTANEOUS];

static uint16_t last_tap_time;

static tap_dance_state_t *tap_dance_get_or_allocate_state(uint8_t tap_dance_idx, bool allocate) {
    uint8_t i;
    if (tap_dance_idx >= tap_dance_count()) {
        return NULL;
    }
    // Search for a state already used for this keycode
    for (i = 0; i < TAP_DANCE_MAX_SIMULTANEOUS; i++) {
        if (tap_dance_states[i].in_use && tap_dance_states[i].index == tap_dance_idx) {
            return &tap_dance_states[i];
        }
    }
    // No existing state found; bail out if new state allocation is not allowed
    if (!allocate) {
        return NULL;
    }
    // Search for the first available state
    for (i = 0; i < TAP_DANCE_MAX_SIMULTANEOUS; i++) {
        if (!tap_dance_states[i].in_use) {
            tap_dance_states[i].index  = tap_dance_idx;
            tap_dance_states[i].in_use = true;
            return &tap_dance_states[i];
        }
    }
    // No states are available, tap dance won't happen
    return NULL;
}

tap_dance_state_t *tap_dance_get_state(uint8_t tap_dance_idx) {
    return tap_dance_get_or_allocate_state(tap_dance_idx, false);
}

void tap_dance_pair_on_each_tap(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;

    if (state->count == 2) {
        register_code16(pair->kc2);
        state->finished = true;
    }
}

void tap_dance_pair_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;

    register_code16(pair->kc1);
}

void tap_dance_pair_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *pair = (tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        wait_ms(TAP_CODE_DELAY);
        unregister_code16(pair->kc1);
    } else if (state->count == 2) {
        unregister_code16(pair->kc2);
    }
}

void tap_dance_dual_role_on_each_tap(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;

    if (state->count == 2) {
        layer_move(pair->layer);
        state->finished = true;
    }
}

void tap_dance_dual_role_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;

    if (state->count == 1) {
        register_code16(pair->kc);
    } else if (state->count == 2) {
        pair->layer_function(pair->layer);
    }
}

void tap_dance_dual_role_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *pair = (tap_dance_dual_role_t *)user_data;

    if (state->count == 1) {
        wait_ms(TAP_CODE_DELAY);
        unregister_code16(pair->kc);
    }
}

static inline void _process_tap_dance_action_fn(tap_dance_state_t *state, void *user_data, tap_dance_user_fn_t fn) {
    if (fn) {
        fn(state, user_data);
    }
}

static inline void process_tap_dance_action_on_each_tap(tap_dance_action_t *action, tap_dance_state_t *state) {
    state->count++;
    state->weak_mods = get_mods();
    state->weak_mods |= get_weak_mods();
#ifndef NO_ACTION_ONESHOT
    state->oneshot_mods = get_oneshot_mods();
#endif
    _process_tap_dance_action_fn(state, action->user_data, action->fn.on_each_tap);
}

static inline void process_tap_dance_action_on_each_release(tap_dance_action_t *action, tap_dance_state_t *state) {
    _process_tap_dance_action_fn(state, action->user_data, action->fn.on_each_release);
}

static inline void process_tap_dance_action_on_reset(tap_dance_action_t *action, tap_dance_state_t *state) {
    _process_tap_dance_action_fn(state, action->user_data, action->fn.on_reset);
    del_weak_mods(state->weak_mods);
#ifndef NO_ACTION_ONESHOT
    del_mods(state->oneshot_mods);
#endif
    send_keyboard_report();
    // Clear the tap dance state and mark it as unused
    memset(state, 0, sizeof(tap_dance_state_t));
}

static inline void process_tap_dance_action_on_dance_finished(tap_dance_action_t *action, tap_dance_state_t *state) {
    if (!state->finished) {
        state->finished = true;
        add_weak_mods(state->weak_mods);
#ifndef NO_ACTION_ONESHOT
        add_mods(state->oneshot_mods);
#endif
        send_keyboard_report();
        _process_tap_dance_action_fn(state, action->user_data, action->fn.on_dance_finished);
    }
    active_td = 0;
    if (!state->pressed) {
        // There will not be a key release event, so reset now.
        process_tap_dance_action_on_reset(action, state);
    }
}

bool preprocess_tap_dance(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;
    tap_dance_state_t * state;

    if (!record->event.pressed) return false;

    if (!active_td || keycode == active_td) return false;

    action = tap_dance_get(QK_TAP_DANCE_GET_INDEX(active_td));
    state  = tap_dance_get_state(QK_TAP_DANCE_GET_INDEX(active_td));
    if (state == NULL) {
        return false;
    }
    state->interrupted          = true;
    state->interrupting_keycode = keycode;
    process_tap_dance_action_on_dance_finished(action, state);

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
    uint8_t             td_index;
    tap_dance_action_t *action;
    tap_dance_state_t * state;

    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            td_index = QK_TAP_DANCE_GET_INDEX(keycode);
            if (td_index >= tap_dance_count()) {
                return false;
            }
            action = tap_dance_get(td_index);
            state  = tap_dance_get_or_allocate_state(td_index, record->event.pressed);
            if (state == NULL) {
                return false;
            }
            state->pressed = record->event.pressed;
            if (record->event.pressed) {
                last_tap_time = timer_read();
                process_tap_dance_action_on_each_tap(action, state);
                active_td = state->finished ? 0 : keycode;
            } else {
                process_tap_dance_action_on_each_release(action, state);
                if (state->finished) {
                    process_tap_dance_action_on_reset(action, state);
                    if (active_td == keycode) {
                        active_td = 0;
                    }
                }
            }

            break;
    }

    return true;
}

void tap_dance_task(void) {
    tap_dance_action_t *action;
    tap_dance_state_t * state;

    if (!active_td || timer_elapsed(last_tap_time) <= GET_TAPPING_TERM(active_td, &(keyrecord_t){})) return;

    action = tap_dance_get(QK_TAP_DANCE_GET_INDEX(active_td));
    state  = tap_dance_get_state(QK_TAP_DANCE_GET_INDEX(active_td));
    if (state != NULL && !state->interrupted) {
        process_tap_dance_action_on_dance_finished(action, state);
    }
}

void reset_tap_dance(tap_dance_state_t *state) {
    active_td = 0;
    process_tap_dance_action_on_reset(tap_dance_get(state->index), state);
}
