/* Copyright 2021 Mats Nilsson
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

#include "mnil.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_TILD:  // ~
            if (record->event.pressed) {
                tap_code16(RALT(KC_RBRC));
                tap_code(KC_SPC);
            } else {
            }
            break;
        case M_CIRC:  // ^
            if (record->event.pressed) {
                tap_code16(S(KC_RBRC));
                tap_code(KC_SPC);
            } else {
            }
            break;
        case M_BTCK:  // `
            if (record->event.pressed) {
                tap_code16(S(KC_EQL));
                tap_code(KC_SPC);
            } else {
            }
            break;
        case QWE_COL:  // Swap default keymap layer
            if (record->event.pressed) {
                if (get_highest_layer(default_layer_state) == _COLEMAK) {
                    default_layer_set(1UL << _QWERTY);
                } else {
                    default_layer_set(1UL << _COLEMAK);
                }
            }
            break;
    }
    return true;
};

// Tap Dance
// Determine the current tap dance state
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_SINGLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8;
}

static tap ae_tap_state = {.is_press_action = true, .state = 0};

void ae_finished(qk_tap_dance_state_t *state, void *user_data) {
    ae_tap_state.state = cur_dance(state);
    switch (ae_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_A);
            break;
        case SINGLE_HOLD:
            tap_code(SE_ADIA);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(KC_A);
            register_code(KC_A);
            break;
    }
}

void ae_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ae_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_A);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_A);
            break;
    }
    ae_tap_state.state = 0;
}

static tap aa_tap_state = {.is_press_action = true, .state = 0};

void aa_finished(qk_tap_dance_state_t *state, void *user_data) {
    aa_tap_state.state = cur_dance(state);
    switch (aa_tap_state.state) {
        case SINGLE_TAP:
            register_code(SE_ODIA);
            break;
        case SINGLE_HOLD:
            register_code(SE_ARNG);
            unregister_code(SE_ARNG);
            break;
        case DOUBLE_SINGLE_TAP:
            tap_code(SE_ODIA);
            register_code(SE_ODIA);
            break;
    }
}

void aa_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (aa_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(SE_ODIA);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(SE_ODIA);
            break;
    }
    aa_tap_state.state = 0;
}

// clang-format off
qk_tap_dance_action_t tap_dance_actions[] = {
  [AAE] =  ACTION_TAP_DANCE_FN_ADVANCED(NULL, ae_finished, ae_reset),
  [OAA] =  ACTION_TAP_DANCE_FN_ADVANCED(NULL, aa_finished, aa_reset)
};
// clang-format on
