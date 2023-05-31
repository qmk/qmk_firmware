/*
Copyright 2023 Joe Scotto
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Tap dance declarations
enum {
    TD_LCTL_ESC_SPOTLIGHT_EMOJI,
    TD_LALT_ESC_WINDOWS_EMOJI
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LCTL_ESC_SPOTLIGHT_EMOJI) :
        case TD(TD_LALT_ESC_WINDOWS_EMOJI) :
        case LGUI_T(KC_SPC) :
        case LT(1, KC_TAB) :
        case LT(2, KC_ENT) :
      return 200;
    default:
      return TAPPING_TERM;
  }
};

// Begin quad TD
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_HOLD,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        return TD_TRIPLE_TAP;
    }   

    return TD_UNKNOWN;
}

void td_lctl_esc_spotlight_emoji_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ESC); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: tap_code16(G(KC_SPC)); break;
        case TD_TRIPLE_TAP: tap_code16(C(G(KC_SPC))); break;
        default: break;
    }
}

void td_lctl_esc_spotlight_emoji_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void td_lalt_esc_windowr_emoji_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ESC); break;
        case TD_SINGLE_HOLD: register_code(KC_LALT); break;
        case TD_DOUBLE_TAP: tap_code(KC_LGUI); break;
        case TD_TRIPLE_TAP: tap_code16(G(KC_DOT)); break;
        default: break;
    }
}

void td_lalt_esc_windowr_emoji_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LALT); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

 // Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LCTL_ESC_SPOTLIGHT_EMOJI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lctl_esc_spotlight_emoji_finished, td_lctl_esc_spotlight_emoji_reset),
    [TD_LALT_ESC_WINDOWS_EMOJI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lalt_esc_windowr_emoji_finished, td_lalt_esc_windowr_emoji_reset),
};

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x10(
        KC_Q,         KC_W, KC_E,                            KC_R,    KC_T,           KC_Y,          KC_U,          KC_I,                            KC_O,   KC_P,
        KC_A,         KC_S, KC_D,                            KC_F,    KC_G,           KC_H,          KC_J,          KC_K,                            KC_L,   KC_BSPC,
        LSFT_T(KC_Z), KC_X, KC_C,                            KC_V,    KC_B,           KC_N,          KC_M,          KC_COMMA,                        KC_DOT, RSFT_T(KC_SLSH),
        KC_NO,        KC,NO TD(TD_LCTL_ESC_SPOTLIGHT_EMOJI), KC_LALT, LGUI_T(KC_SPC), LT(1, KC_TAB), LT(2, KC_ENT), TD(TD_LCTL_ESC_SPOTLIGHT_EMOJI), KC_NO,  KC_NO
    ),
    [1] = LAYOUT_ortho_4x10(
        KC_UNDS,         KC_MINS, KC_PLUS, KC_EQL,  KC_COLN, KC_GRV,   KC_MRWD, KC_MPLY, KC_MFFD, KC_DEL,
        KC_LCBR,         KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE, KC_ESC,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
        LSFT_T(KC_LBRC), KC_QUOT, KC_DQUO, KC_RBRC, KC_SCLN, KC_TILDE, KC_VOLD, KC_MUTE, KC_VOLU, RSFT_T(KC_BSLS),
        KC_NO,           KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_NO,   KC_NO
    ),
    [2] = LAYOUT_ortho_4x10(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_CAPS, KC_BSPC,
        KC_1,    KC_2,  KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LSFT, KC_NO, KC_NO,   KC_NO,   MO(3),   KC_NO,   KC_NO,   KC_COMM, KC_DOT,  RSFT_T(KC_SLSH),
        KC_NO,   KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO
    ),
    [3] = LAYOUT_ortho_4x10(
        KC_NO,  KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO(5), TO(4), 
        KC_F1,  KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9, KC_F10,
        KC_F11, KC_NO, KC_NO,   QK_BOOT, KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_F12,
        KC_NO,  KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO
    ),
    [4] = LAYOUT_ortho_4x10(
        KC_Q,         KC_W, KC_E,                          KC_R,    KC_T,           KC_Y,          KC_U,          KC_I,                           KC_O,   KC_P,
        KC_A,         KC_S, KC_D,                          KC_F,    KC_G,           KC_H,          KC_J,          KC_K,                           KC_L,   KC_BSPC,
        LSFT_T(KC_Z), KC_X, KC_C,                          KC_V,    KC_B,           KC_N,          KC_M,          KC_COMMA,                       KC_DOT, RSFT_T(KC_SLSH),
        KC_NO,        KC_NO, TD(TD_LALT_ESC_WINDOWS_EMOJI), KC_LALT, LCTL_T(KC_SPC), LT(6, KC_TAB), LT(7, KC_ENT), TD(TD_LALT_ESC_WINDOWS_EMOJI), KC_NO,  KC_NO
    ),
    [5] = LAYOUT_ortho_4x10(
        KC_Q,  KC_W,  KC_E, KC_R,                          KC_T,    KC_Y,   KC_U,          KC_I,          KC_O,                          KC_P,
        KC_A,  KC_S,  KC_D, KC_F,                          KC_G,    KC_H,   KC_J,          KC_K,          KC_L,                          KC_BSPC,
        KC_Z,  KC_X,  KC_C, KC_V,                          KC_B,    KC_N,   KC_M,          KC_COMMA,      KC_DOT,                        KC_SLSH,
        KC_NO, KC_NO, TD(TD_LALT_ESC_WINDOWS_EMOJI), KC_LCTL, KC_SPC, LT(6, KC_TAB), LT(7, KC_ENT), TD(TD_LALT_ESC_WINDOWS_EMOJI) KC_NO, KC_NO
    ),
    [6] = LAYOUT_ortho_4x10(
        KC_UNDS,         KC_MINS, KC_PLUS, KC_EQL,  KC_COLN, KC_GRV,   KC_MRWD, KC_MPLY, KC_MFFD, KC_DEL,
        KC_LCBR,         KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE, KC_ESC,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
        LSFT_T(KC_LBRC), KC_QUOT, KC_DQUO, KC_RBRC, KC_SCLN, KC_TILDE, KC_VOLD, KC_MUTE, KC_VOLU, RSFT_T(KC_BSLS),
        KC_NO,           KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_NO,   KC_NO
    ),
    [7] = LAYOUT_ortho_4x10(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_CAPS, KC_BSPC,
        KC_1,    KC_2,  KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LSFT, KC_NO, KC_NO,   KC_NO,   MO(8),   KC_NO,   KC_NO,   KC_COMM, KC_DOT,  RSFT_T(KC_SLSH),
        KC_NO,   KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO
    ),
    [8] = LAYOUT_ortho_4x10(
        KC_NO,  KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO(4),   TO(5), TO(0), 
        KC_F1,  KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9, KC_F10,
        KC_F11, KC_NO, KC_NO,   QK_BOOT, KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_F12,
        KC_NO,  KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO
    )
};
