/* Copyright 2021 James Young (@noroadsleft)
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

// FUNCIONES TAP DANCE
void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_N);
    } else {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_N));
        clear_keyboard();
    }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_N);
    }
}

//NOMBRES TAP DANCE
enum {
    TD_ENE,
    TD_SIFT_CAPSLOCK
};

// Tap Dance DEFINICIONES
qk_tap_dance_action_t tap_dance_actions[] = {
    // 1 TOQUE PARA OPC 1 DOS PARA OPC 2
    [TD_ENE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
    [TD_SIFT_CAPSLOCK]  = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_SHIFT, KC_CAPS_LOCK)
};



enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOV,
  _RIGHT_HAND_NUM_PAD,
  _LEFT_HAND_NUM_PAD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        LT(4, KC_GESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        TD(TD_SIFT_CAPSLOCK), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TD(TD_ENE),    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
        TT(5), KC_LCTL, KC_LGUI, KC_LALT, LT(1, KC_BACKSPACE),   LT(4, KC_SPACE),  LT(4, KC_SPACE),  LT(2, KC_ENTER),   KC_RALT,   KC_NO, KC_NO, KC_NO
    ),
    [_LOWER] = LAYOUT_ortho_4x12(
         KC_ESC, KC_EXLM,   KC_AT,   KC_HASH,  KC_DLR,  KC_PERC, KC_CIRC,  KC_AMPR,     KC_ASTR,      KC_LPRN, KC_RPRN, KC_BSPC,
        KC_TILD,   KC_F1,   KC_F2,     KC_F3,   KC_F4,    KC_F5,   KC_F6,  KC_UNDS,     KC_PLUS,      KC_LCBR, KC_RCBR, KC_PIPE,
        KC_NO,   KC_F7,   KC_F8,     KC_F9,  KC_F10,   KC_F11,  KC_F12,    KC_NO,       KC_NO,        KC_NO,   KC_NO,   KC_NO,
          KC_NO,   KC_NO,   KC_NO,     KC_NO, KC_TRNS,   KC_SPC,  KC_SPC,   KC_ENT,       KC_NO,      KC_MRWD, KC_MPLY, KC_MFFD
    ),
    [_RAISE] = LAYOUT_ortho_4x12(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_NO, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO, KC_NO, KC_NO, KC_NO,KC_NO,
        KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_BSPC, KC_SPC, KC_SPC, KC_TRNS, KC_NO, KC_NO, KC_NO, MO(3)
    ),
    [_ADJUST] = LAYOUT_ortho_4x12(
        RESET,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DEBUG,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,KC_NO,KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO,KC_NO, KC_NO, KC_TRNS
    ),

    [_MOV] = LAYOUT_ortho_4x12(
        KC_TAB,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_INS, KC_PSCR, KC_SLCK, KC_PAUS,
        KC_CAPS, KC_CAPS, KC_LCTL, KC_LALT, KC_LSFT, KC_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_DEL,  KC_NO,  LCTL(KC_LEFT_GUI), KC_END, KC_END, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO,
        TO(6), KC_NO, KC_NO, KC_NO, KC_BSPC, KC_TRNS, KC_TRNS, KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    [_RIGHT_HAND_NUM_PAD] = LAYOUT_ortho_4x12(
         KC_NO,   KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_PSLS, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_PAST,
        KC_ESC,   KC_NO, KC_NO,  KC_NO, KC_NO, KC_BSPC, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PPLS, KC_PMNS,
         KC_NO,   KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PENT, KC_NO,
         KC_NO,   KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_P0, KC_P0, KC_PDOT, KC_PENT, KC_NO
    ),

    [_LEFT_HAND_NUM_PAD] = LAYOUT_ortho_4x12(
        LM(0,MOD_LCTL), KC_7, KC_8, KC_9, KC_9,        KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LM(0,MOD_LCTL), KC_4, KC_5, KC_6, KC_6,        KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LM(0,MOD_LCTL), KC_1, KC_2, KC_3, KC_3,        KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        LM(0,MOD_LCTL), KC_0, KC_0, KC_0, KC_0, LALT(KC_TAB), LALT(KC_TAB), KC_NO, KC_NO, KC_NO, KC_NO,  TO(0)
    )

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}



