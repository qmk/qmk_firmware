/* Tap dance tap hold
 *
 * Copyright 2021 Benjamin Smith (@Merlin04)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "register_any.h"

td_tap_result cur_dance(qk_tap_dance_state_t *state) {
    td_tap_result result = {
        .count = state->count,
        .type = (!(state->interrupted) && state->pressed)
            ? TD_HOLD
            : TD_TAP
    };
    return result;
}

uint16_t td_get_keycode(uint16_t defKeycode, uint8_t type, uint8_t taps) {
    uint16_t keycode = type == TD_HOLD
        ? td_th_defs[defKeycode].hold_kc[taps - 1]
        : td_th_defs[defKeycode].tap_kc[taps - 1];

    return keycode;
}

// TODO: stop tap dance once TD_TH_MAX_TAP is reached to make it more responsive
void td_finished(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t stateKeycode = state->keycode - QK_TAP_DANCE;
    td_states[stateKeycode] = cur_dance(state);
    uint16_t kc = td_get_keycode(stateKeycode, td_states[stateKeycode].type, td_states[stateKeycode].count);
    if(td_states[stateKeycode].count <= TD_TH_MAX_TAP && kc != KC_UNDEFINED) {
        register_any(kc, true);
    }
    else {
        // Fall back to repeating the tap once keycode however many times the user has tapped
        for(uint8_t i = 0; i < td_states[stateKeycode].count - 1; i++) {
            tap_any(td_th_defs[stateKeycode].tap_kc[0]);
        }
        register_any(td_th_defs[stateKeycode].tap_kc[0], true);
    }
}

void td_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t stateKeycode = state->keycode - QK_TAP_DANCE;
    uint16_t kc = td_get_keycode(stateKeycode, td_states[stateKeycode].type, td_states[stateKeycode].count);
    if(td_states[stateKeycode].count <= TD_TH_MAX_TAP && kc != KC_UNDEFINED) {
        register_any(
            kc,
            false
        );
    }
    else {
        register_any(td_th_defs[stateKeycode].tap_kc[0], false);
    }

    td_states[stateKeycode].count = 0;
    td_states[stateKeycode].type = 0;
}
