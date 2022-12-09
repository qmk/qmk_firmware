/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>
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

#include "tapdances.h"

void ios_media(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_MPLY);
    } else if (state->count == 2) {
        tap_code(KC_MNXT);
    } else if (state->count == 3) {
        tap_code(KC_MPRV);
    } else {
        reset_tap_dance(state);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_FN(ios_media),
    [1] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_SCLN),
    [2] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COLON),
    [3] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [4] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
};
