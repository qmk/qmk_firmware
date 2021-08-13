/* Copyright 2021 imchipwood
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
#include "imchipwood.h"

static td_state_t td_state[3];

// determine the tapdance state to return
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    }
    if (state->count == 2) {
        return DOUBLE_TAP;
    } else {
        return 3;
    }  // any number higher than the maximum state value you return above
}

void altf2_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state[0] = cur_dance(state);
    switch (td_state[0]) {
        case SINGLE_TAP:
            register_code(KC_F2);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LALT));
            tap_code(KC_F2);
            break;
    }
}

void altf2_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state[0]) {
        case SINGLE_TAP:
            unregister_code(KC_F2);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_TAP:
            unregister_code(KC_F2);
            unregister_mods(MOD_BIT(KC_LALT));
            break;
    }
}


void ctlf5_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state[1] = cur_dance(state);
    switch (td_state[1]) {
        case SINGLE_TAP:
            register_code(KC_F5);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            break;
        case DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LCTL));
            tap_code(KC_F5);
            break;
    }
}

void ctlf5_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state[1]) {
        case SINGLE_TAP:
            unregister_code(KC_F5);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
        case DOUBLE_TAP:
            unregister_code(KC_F5);
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
    }
}

void altf7_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state[2] = cur_dance(state);
    switch (td_state[2]) {
        case SINGLE_TAP:
            register_code(KC_F7);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LALT));
            tap_code(KC_F7);
            break;
    }
}

void altf7_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state[2]) {
        case SINGLE_TAP:
            unregister_code(KC_F7);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_TAP:
            unregister_code(KC_F7);
            unregister_mods(MOD_BIT(KC_LALT));
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [ALT_F2]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altf2_finished, altf2_reset),
    [CTL_F5]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlf5_finished, ctlf5_reset),
    [ALT_F7]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altf7_finished, altf7_reset),
    [DEL_NLCK] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_NLCK),
    // Double tap right -> END
    [TD_REND] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, KC_END),
    // Double tap left -> HOME
    [TD_LOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
    // Double tap right shift -> CAPS LOCK
    [TD_RSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};
