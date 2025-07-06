/* Copyright 2021 Hydrogen BD <support@hgenbd.com>
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

#include QMK_KEYBOARD_H

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum custom_keycodes {
    TD_CUT_REDO,
    TD_PLAY_PAUSE_MUTE,
    TD_MNXT_RIGHT,
    TD_MPRV_LEFT,
    TD_SEARCH_REFRESH,
    QUAD_LAYER_SWITCH,
    QUAD_CVXA,
    YOUTUBE = SAFE_RANGE,
    FACEBOOK,
    DISCORD,
    VALORANT,
    VSCODE,
};

td_state_t cur_dance(tap_dance_state_t *state);

/* Quad layer switching */
void layer_finished(tap_dance_state_t *state, void *user_data);
void layer_reset(tap_dance_state_t *state, void *user_data);

/* Copy, paste, select all, cut */
void cvxa_finished(tap_dance_state_t *state, void *user_data);
void cvxa_reset(tap_dance_state_t *state, void *user_data);

static td_tap_t layerTap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t cvxa_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else return TD_UNKNOWN;
}

void layer_finished(tap_dance_state_t *state, void *user_data) {
    layerTap_state.state = cur_dance(state);
    layer_off(get_highest_layer(layer_state));
    switch (layerTap_state.state) {
        case TD_SINGLE_TAP: layer_on(0); break;
        case TD_SINGLE_HOLD: layer_on(1); break;
        case TD_DOUBLE_TAP: layer_on(2); break;
        case TD_DOUBLE_HOLD: layer_on(3); break;
        default: layer_on(0);
    }
}

void layer_reset(tap_dance_state_t *state, void *user_data) {
    layerTap_state.state = TD_NONE;
}

void cvxa_finished(tap_dance_state_t *state, void *user_data) {
    cvxa_state.state = cur_dance(state);
    register_mods(MOD_BIT(KC_LCTL));
    switch (cvxa_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_V); break;
        case TD_SINGLE_HOLD: tap_code(KC_A); break;
        case TD_DOUBLE_TAP: tap_code(KC_C); break;
        case TD_DOUBLE_HOLD: tap_code(KC_X); break;
        default: tap_code(KC_V);
    }
    unregister_mods(MOD_BIT(KC_LCTL));
}

void cvxa_reset(tap_dance_state_t *state, void *user_data) {
    cvxa_state.state = TD_NONE;
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_CUT_REDO] = ACTION_TAP_DANCE_DOUBLE(C(KC_Z), S(C(KC_Z))),
    [TD_PLAY_PAUSE_MUTE] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MUTE),
    [TD_MNXT_RIGHT] = ACTION_TAP_DANCE_DOUBLE(KC_MNXT, KC_RIGHT),
    [TD_MPRV_LEFT] = ACTION_TAP_DANCE_DOUBLE(KC_MPRV, KC_LEFT),
    [TD_SEARCH_REFRESH] = ACTION_TAP_DANCE_DOUBLE(KC_WREF, KC_WSCH),
    [QUAD_LAYER_SWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layer_finished, layer_reset),
    [QUAD_CVXA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cvxa_finished, cvxa_reset)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case YOUTUBE:
            if (record->event.pressed) {
                tap_code16(C(KC_L));
                SEND_STRING("https://www.youtube.com/");
            } else {
                tap_code(KC_ENT);
            }
            break;
        case FACEBOOK:
            if (record->event.pressed) {
                tap_code16(C(KC_L));
                SEND_STRING("https://www.facebook.com/");
            } else {
                tap_code(KC_ENT);
            }
            break;
        case VALORANT:
            if (record->event.pressed) {
                tap_code16(G(KC_S));
                SEND_STRING("valorant");
            } else {
                tap_code(KC_ENT);
            }
            break;
        case DISCORD:
            if (record->event.pressed) {
                tap_code16(G(KC_S));
                SEND_STRING("discord");
            } else {
                tap_code(KC_ENT);
            }
            break;
        case VSCODE:
            if (record->event.pressed) {
                tap_code16(G(KC_S));
                SEND_STRING("vscode");
            } else {
                tap_code(KC_ENT);
            }
            break;
    }
    return true;
}; 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
      TD(TD_CUT_REDO), TD(TD_MPRV_LEFT), TD(TD_PLAY_PAUSE_MUTE), TD(TD_MNXT_RIGHT), TD(QUAD_CVXA), TD(QUAD_LAYER_SWITCH)
      ),

  [1] = LAYOUT(
      YOUTUBE, KC_WBAK, TD(TD_SEARCH_REFRESH), KC_WFWD, FACEBOOK, TD(QUAD_LAYER_SWITCH)
      ),

  [2] = LAYOUT(
      A(KC_F4), LSG(KC_S), KC_MYCM, LCA(KC_DEL), KC_CALC, TD(QUAD_LAYER_SWITCH)
      ),
  
  [3] = LAYOUT(
      C(KC_SLSH), VALORANT, VSCODE, DISCORD, LSA(KC_A), TD(QUAD_LAYER_SWITCH)
      ),
};