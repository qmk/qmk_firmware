/*
Copyright 2023 StenoKeyboards

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
#include "keymap_steno.h"

enum polyglot_layers {
    _UNI_GEMINI,
    _QWERTY,
    _DVORAK,
    _COLEMAK,
    _RAISE,
    _LOWER,
    _GEMINI,
    _PLOVER,
    _UNI_PLOVER,
};

enum polyglot_keycodes {
    UNI_GEMINI = SAFE_RANGE,
    QWERTY,
    DVORAK,
    COLEMAK,
    RAISE,
    LOWER,
    GEMINI,
    PLOVER,
    UNI_PLOVER,
    BACK,
};

int default_keymap = _QWERTY;

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [_UNI_GEMINI] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, 					  STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, 					 STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        BACK,  KC_LSFT,  KC_LCTL,  KC_LALT,  KC_LCMD,  KC_SPC,    				KC_VOLD,  KC_LEFT, KC_DOWN, KC_UP ,KC_RIGHT,  KC_VOLU,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   STN_N1,  STN_A,   STN_O,                       STN_E,   STN_U, STN_N2
                                       //`--------------------------'  `--------------------------'

   ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   UNI_PLOVER,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   KC_TAB,   _______, KC_LEFT, KC_DOWN,  KC_UP,KC_RIGHT,                        _______,QWERTY,DVORAK, COLEMAK,  _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  _______,KC_DEL, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                _______, _______, _______,                      _______, XXXXXXX, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       PLOVER, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,               KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      GEMINI, RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_MODE_FORWARD,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,XXXXXXX, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UNI_GEMINI,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   RAISE, KC_LSFT,       KC_SPC, LOWER, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

    [_DVORAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,   KC_S,  KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UNI_GEMINI,    KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LGUI,   RAISE, KC_LSFT,       KC_SPC, LOWER, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

    [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UNI_GEMINI,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LGUI,   RAISE, KC_LSFT,       KC_SPC, LOWER, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [_PLOVER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      BACK,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_1,   KC_C,    KC_V,                        KC_N,    KC_M, KC_2
                                      //`--------------------------'  `--------------------------'

  ),

  [_GEMINI] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      BACK,  STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  					            STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, 					             STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, 					             STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       STN_N1,   STN_A,   STN_O,         STN_E,   STN_U, STN_N2
                                      //`--------------------------'  `--------------------------'

  ),

  [_UNI_PLOVER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        BACK,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_SPC,    				KC_VOLD,  KC_LEFT, KC_DOWN, KC_UP ,KC_RIGHT,  KC_VOLU,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    KC_1,   KC_C,    KC_V,                        KC_N,    KC_M, KC_2
                                      //`--------------------------'  `--------------------------'

  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
		    layer_move(_QWERTY);
        default_keymap = _QWERTY;
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
		    layer_move(_DVORAK);
        default_keymap = _DVORAK;
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
		    layer_move(_COLEMAK);
        default_keymap = _COLEMAK;
      }
      return false;
    case PLOVER:
      if (record->event.pressed) {
		    layer_move(_PLOVER);
      }
      return false;
    case GEMINI:
      if (record->event.pressed) {
        layer_move(_GEMINI);
      }
      return false;
    case UNI_PLOVER:
      if (record->event.pressed) {
		    layer_move(_UNI_PLOVER);
      }
      return false;
    case UNI_GEMINI:
      if (record->event.pressed) {
        layer_move(_UNI_GEMINI);
      }
      return false;
    case BACK:
      if (record->event.pressed) {
        layer_move(default_keymap);
      }
      return false;
  }
  return true;
}
