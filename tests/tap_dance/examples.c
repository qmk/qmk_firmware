/* Copyright 2022 Jouke Witteveen
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
#include "examples.h"

// Example code from the tap dance documentation, adapted for testing

// clang-format off

// Example 1

void dance_egg(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 100) {
        // SEND_STRING("Safety dance!");
        tap_code(KC_C);
        reset_tap_dance(state);
    }
}


// Example 2

void dance_flsh_each(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            register_code(KC_3);
            break;
        case 2:
            register_code(KC_2);
            break;
        case 3:
            register_code(KC_1);
            break;
        case 4:
            unregister_code(KC_3);
            // wait_ms(50);
            unregister_code(KC_2);
            // wait_ms(50);
            unregister_code(KC_1);
    }
}

void dance_flsh_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 4) {
        // reset_keyboard();
        tap_code(KC_R);
    }
}

void dance_flsh_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_1);
    // wait_ms(50);
    unregister_code(KC_2);
    // wait_ms(50);
    unregister_code(KC_3);
}


// Example 3

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(CT_CLN):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


// Example 4

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_X); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
        default: break;  // Not present in documentation
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_X); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);
        default: break;  // Not present in documentation
    }
    xtap_state.state = TD_NONE;
}

static void release_press(tap_dance_state_t *state, void *user_data) {
    tap_code16(KC_P);
}

static void release_unpress(tap_dance_state_t *state, void *user_data) {
    tap_code16(KC_U);
}

static void release_unpress_mark_finished(tap_dance_state_t *state, void *user_data) {
    tap_code16(KC_U);
    state->finished = true;
}

static void release_finished(tap_dance_state_t *state, void *user_data) {
    tap_code16(KC_F);
}

static void release_reset(tap_dance_state_t *state, void *user_data) {
    tap_code16(KC_R);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [CT_EGG]      = ACTION_TAP_DANCE_FN(dance_egg),
    [CT_FLSH]     = ACTION_TAP_DANCE_FN_ADVANCED(dance_flsh_each, dance_flsh_finished, dance_flsh_reset),
    [CT_CLN]      = ACTION_TAP_DANCE_TAP_HOLD(KC_COLN, KC_SCLN),
    [X_CTL]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [TD_RELEASE]  = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(release_press, release_unpress, release_finished, release_reset),
    [TD_RELEASE_AND_FINISH]  = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(release_press, release_unpress_mark_finished, release_finished, release_reset),
};

// clang-format on
