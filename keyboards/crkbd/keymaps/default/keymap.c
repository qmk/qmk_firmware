/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include <stdio.h>
// TAP DANCES
enum {
    TD_ACCENTED_A,
    TD_ACCENTED_E,
    TD_ACCENTED_I,
    TD_ACCENTED_O,
    TD_ACCENTED_U,
};

// Custom keycodes
#define KC_CSL LCTL(LSFT(KC_L))     // Ctrl + Shift + F10
#define KC_AACC TD(TD_ACCENTED_A)
#define KC_EACC TD(TD_ACCENTED_E)
#define KC_IACC TD(TD_ACCENTED_I)
#define KC_OACC TD(TD_ACCENTED_O)
#define KC_UACC TD(TD_ACCENTED_U)

void accented_letter_a(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("à");
            break;
        case 2:
            send_unicode_string("À");
            break;
        case 3:
            send_unicode_string("á");
            break;
        case 4:
            send_unicode_string("Á");
            break;
    }
}
void accented_letter_e(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("è");
            break;
        case 2:
            send_unicode_string("È");
            break;
        case 3:
            send_unicode_string("é");
            break;
        case 4:
            send_unicode_string("É");
            break;
    }
}
void accented_letter_i(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("ì");
            break;
        case 2:
            send_unicode_string("Ì");
            break;
        case 3:
            send_unicode_string("í");
            break;
        case 4:
            send_unicode_string("Í");
            break;
    }
}
void accented_letter_o(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("ò");
            break;
        case 2:
            send_unicode_string("Ò");
            break;
        case 3:
            send_unicode_string("ó");
            break;
        case 4:
            send_unicode_string("Ó");
            break;
    }
}
void accented_letter_u(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("ù");
            break;
        case 2:
            send_unicode_string("Ù");
            break;
        case 3:
            send_unicode_string("ú");
            break;
        case 4:
            send_unicode_string("Ú");
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ACCENTED_A] = ACTION_TAP_DANCE_FN(accented_letter_a),
    [TD_ACCENTED_E] = ACTION_TAP_DANCE_FN(accented_letter_e),
    [TD_ACCENTED_I] = ACTION_TAP_DANCE_FN(accented_letter_i),
    [TD_ACCENTED_O] = ACTION_TAP_DANCE_FN(accented_letter_o),
    [TD_ACCENTED_U] = ACTION_TAP_DANCE_FN(accented_letter_u),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   KC_LALT,  MO(1),     KC_SPC,   MO(2), KC_RCTL
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_RBRC, KC_RCBR, KC_LCBR, KC_LBRC,  KC_F12,                      XXXXXXX, KC_HOME,   KC_UP,  KC_END, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC,  KC_CSL,    KC_F2,  KC_EQL, KC_MINS, KC_PLUS,                      KC_UNDS, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_GRV, KC_TILDE, KC_BSLS, KC_PIPE, KC_LGUI,                      XXXXXXX,  KC_DEL, KC_QUOT, KC_DQUO, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LALT, _______,     KC_SPC,   MO(3), KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_VOLD, KC_VOLU, KC_MUTE,  KC_DEL, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LALT,  MO(3),      KC_SPC, _______, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, KC_EACC, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_UACC, KC_IACC, KC_OACC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_AACC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LALT,  _______,     KC_SPC, _______, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  )
};
