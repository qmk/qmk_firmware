/*
Copyright 2021-2022 Rocco Meli <@RMeli>

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

#include "keyrecords/tap_dances.h"

// + ---------- +
// + TAP DANCES |
// + ---------- +

// Tap dances definitions
// Need to needs to be defined in a .c file to avoid a linker error (multiple definitions)
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LSPO_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, LSPO_CAPS_finished, LSPO_CAPS_reset),
    [TD_RSPC_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, RSPC_CAPS_finished, RSPC_CAPS_reset),
    [TD_ESC_DEL]   = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_DEL),
};

// + ------ +
// + DANCES |
// + ------ +

// https://github.com/qmk/qmk_firmware/blob/9294258c02d3e025e01935a06c4d9f1997535bda/users/gordon/gordon.c#L112-L135
td_state_t hold_cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) {
            if (!state->pressed)
                return TD_SINGLE_TAP;
            else
                return TD_SINGLE_HOLD;
        } else {
            if (!state->pressed)
                return TD_SINGLE_TAP;
            else
                return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        if (state->pressed)
            return TD_NONE;
        else
            return TD_DOUBLE_TAP;
    } else
        return TD_NONE;
}

// + ------------------------------------------------ +
// + LEFT SHIFT PARENTHESIS OPEN (LSPO) AND CAPS LOCK |
// + ------------------------------------------------ +

// Create an instance of 'td_tap_t' for the 'LSPO_CAPS' tap dance.
static td_tap_t LSPO_CAPS_state = {.is_press_action = true, .state = TD_NONE};

void LSPO_CAPS_finished(qk_tap_dance_state_t *state, void *user_data) {
    LSPO_CAPS_state.state = hold_cur_dance(state);
    switch (LSPO_CAPS_state.state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            register_code16(KC_CAPS);
            break;
        case TD_NONE:
            break;
    }
}

void LSPO_CAPS_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (LSPO_CAPS_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_CAPS);
            break;
        case TD_NONE:
            break;
    }
    LSPO_CAPS_state.state = TD_NONE;
}

// + -------------------------------------------------- +
// + RIGHT SHIFT PARENTHESIS CLOSE (RSPC) AND CAPS LOCK |
// + -------------------------------------------------- +

// Create an instance of 'td_tap_t' for the 'RSPC_CAPS' tap dance.
static td_tap_t RSPC_CAPS_state = {.is_press_action = true, .state = TD_NONE};

void RSPC_CAPS_finished(qk_tap_dance_state_t *state, void *user_data) {
    RSPC_CAPS_state.state = hold_cur_dance(state);
    switch (RSPC_CAPS_state.state) {
        case TD_SINGLE_TAP:
            register_code16(KC_RPRN);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_RSFT);
            break;
        case TD_DOUBLE_TAP:
            register_code16(KC_CAPS);
            break;
        case TD_NONE:
            break;
    }
}

void RSPC_CAPS_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (RSPC_CAPS_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_RPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_RSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_CAPS);
            break;
        case TD_NONE:
            break;
    }
    RSPC_CAPS_state.state = TD_NONE;
}
