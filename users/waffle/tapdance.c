/* Copyright 2021 @waffle#0007
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

#include "waffle.h"
#include "secrets.h"

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8;
}

static tap cur_tap_state = {
    .is_press_action = true,
    .state = 0
};

void mslgui_finished(qk_tap_dance_state_t *state, void *user_data) {
    cur_tap_state.state = cur_dance(state);
    switch (cur_tap_state.state) {
        case SINGLE_TAP: register_code(KC_LGUI); break;
        case SINGLE_HOLD: register_code(KC_LGUI); break;
        case DOUBLE_TAP: register_code(KC_LGUI); break;
        case DOUBLE_HOLD: register_code16(KC_MS_L); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_LGUI); register_code(KC_LGUI);
    }
}

void mslgui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_LGUI); break;
        case SINGLE_HOLD: unregister_code(KC_LGUI); break;
        case DOUBLE_TAP: unregister_code(KC_LGUI); break;
        case DOUBLE_HOLD: unregister_code16(KC_MS_L);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_LGUI);
    }
    cur_tap_state.state = 0;
}

void gclipst_finished(qk_tap_dance_state_t *state, void *user_data) {
    cur_tap_state.state = cur_dance(state);
    switch (cur_tap_state.state) {
        case SINGLE_TAP: register_code16(C(S(KC_V))); break;
        case SINGLE_HOLD: register_code16(KC_MS_R); break;
        case DOUBLE_TAP: register_code16(C(S(KC_V))); break;
        case DOUBLE_HOLD: register_code16(KC_MS_R); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_RGUI); register_code(KC_RGUI);
    }
}

void gclipst_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_tap_state.state) {
        case SINGLE_TAP: unregister_code16(C(S(KC_V))); break;
        case SINGLE_HOLD: unregister_code16(KC_MS_R); break;
        case DOUBLE_TAP: unregister_code16(C(S(KC_V))); break;
        case DOUBLE_HOLD: unregister_code16(KC_MS_R); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_RGUI);
    }
    cur_tap_state.state = 0;
}

void oslgui_finished(qk_tap_dance_state_t *state , void *user_data) {
    cur_tap_state.state = cur_dance(state);
    switch (cur_tap_state.state) {
        case SINGLE_TAP: set_oneshot_layer(_RAISE, ONESHOT_START); break;
        case SINGLE_HOLD: register_code(KC_RGUI); break;
        case DOUBLE_TAP: set_oneshot_layer(_RAISE, ONESHOT_START); break;
        case DOUBLE_HOLD: register_code(KC_RGUI); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_TRNS); register_code(KC_TRNS);
    }
}

void oslgui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_tap_state.state) {
        case SINGLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case SINGLE_HOLD: unregister_code(KC_RGUI); break;
        case DOUBLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case DOUBLE_HOLD: unregister_code(KC_RGUI); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_TRNS);
    }
    cur_tap_state.state = 0;
}

void dance_qmk_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(C(KC_T));
        send_string(qmkstr);
        tap_code(KC_ENT);
    } else {
        tap_code16(C(KC_T));
        send_string(confstr);
        tap_code(KC_ENT);
    }
}

void dance_doc_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      send_string(docstr);
    } else {
      send_string(drivstr);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [QMK] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_qmk_finished, NULL, 220),
    [DOCS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_doc_finished, NULL, 220),
    [MSLGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mslgui_finished, mslgui_reset),
    [GCLIPST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gclipst_finished, gclipst_reset),
    [OSLGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, oslgui_finished, oslgui_reset),
};
