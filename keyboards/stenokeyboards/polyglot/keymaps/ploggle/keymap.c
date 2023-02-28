/*
Copyright 2021 Peter C. Park <peter@stenokeyboards.com>

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
 _UNI_PLOVER = 0
 ,_QWERTY //1
 ,_DVORAK //2
 ,_COLEMAK //3 ... Enum means list of consecutive numbers
 ,_RAISE
 ,_LOWER
};

int default_typing_layer = 1;

enum polyglot_keycodes {
 QWERTY = SAFE_RANGE
 ,DVORAK
 ,COLEMAK
 ,RAISE
 ,LOWER
 ,PLOGGLE
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_UNI_PLOVER] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       PLOGGLE,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_SPC,    				KC_VOLD,  KC_LEFT, KC_DOWN, KC_UP ,KC_RIGHT,  KC_VOLU,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    KC_1,   KC_C,    KC_V,                        KC_N,    KC_M, KC_2
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_RALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          RAISE,   KC_LGUI, KC_LSFT,       KC_SPC, KC_LCTL, LOWER
                                      //`--------------------------'  `--------------------------'

  ),

    [_DVORAK] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,   KC_S,  KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_RALT,    KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        RAISE,   KC_LGUI, KC_LSFT,       KC_SPC, KC_LCTL, LOWER
                                      //`--------------------------'  `--------------------------'

  ),

    [_COLEMAK] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_RALT,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      PLOGGLE,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        RAISE,   KC_LGUI, KC_LSFT,       KC_SPC, KC_LCTL, LOWER
                                      //`--------------------------'  `--------------------------'

  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   _______,   KC_TAB, KC_LEFT, KC_DOWN,  KC_UP,KC_RIGHT,                        _______,QWERTY,DVORAK, COLEMAK,  _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  _______,KC_DEL, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                _______, KC_LGUI, KC_LSFT,                      KC_SPC, KC_LCTL, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,               KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,KC_LGUI, KC_LSFT,    KC_SPC, KC_LCTL, _______
                                      //`--------------------------'  `--------------------------'
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
		    layer_move(_QWERTY);
        default_typing_layer = 1;
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
		    layer_move(_DVORAK);
        default_typing_layer = 2;
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
		    layer_move(_COLEMAK);
        default_typing_layer = 3;
      }
      return false;
    case PLOGGLE:
      if (record->event.pressed) {
        //when key pressed
      } else
      {
        //when key released
        //change the layer
        if (IS_LAYER_ON(_UNI_PLOVER)) {
          layer_move(default_typing_layer);
        } else {
          layer_move(_UNI_PLOVER);
        }
        // this is the ploggle thing
        SEND_STRING(SS_DOWN(X_E)SS_DOWN(X_R)SS_DOWN(X_F)SS_DOWN(X_V)SS_DOWN(X_O)SS_DOWN(X_L)SS_UP(X_E)SS_UP(X_R)SS_UP(X_F)SS_UP(X_V)SS_UP(X_O)SS_UP(X_L));
      }
      return false;
  }
  return true;
}

// initialize steno protocol
void matrix_init_user(void)
{
  steno_set_mode(STENO_MODE_GEMINI);
}
