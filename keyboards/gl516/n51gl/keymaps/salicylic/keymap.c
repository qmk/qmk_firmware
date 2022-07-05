/*
Copyright 2021 Salicylic_Acid

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
#include "keymap_jp.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_rotary_layer(
  //,--------------------------------------------------------------|        |--------------------------------------------------------------.
       KC_ESC,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
              KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_VOLU,    KC_H,    KC_J,    KC_K,    KC_L, JP_MINS, JP_BSLS,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
               KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    KC_N,    KC_M, KC_COMM,  KC_DOT, JP_SLSH,   KC_UP, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
         JP_ZKHK, KC_LALT,LGUI_T(JP_MHEN),LT(_LOWER,KC_ENT),KC_BSPC, KC_VOLD, KC_DEL,LT(_RAISE,KC_SPC),ALT_T(JP_HENK),KC_LEFT, KC_DOWN, KC_RGHT
  //|--------------------------------------------------------------|        |--------------------------------------------------------------'
  ),
  [_LOWER] = LAYOUT_rotary_layer(
  //,--------------------------------------------------------------|        |--------------------------------------------------------------.
      _______, _______, JP_EXLM, JP_QUES, JP_LBRC, JP_RBRC, JP_TILD,             KC_6,    KC_7,    KC_8,    KC_9, JP_ASTR, JP_SLSH, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
               JP_QUOT, JP_HASH,  JP_DQT, JP_LPRN, JP_RPRN,   JP_AT, KC_WH_U, XXXXXXX,    KC_4,    KC_5,    KC_6, JP_MINS,  JP_EQL, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
               JP_CIRC, JP_PERC, JP_AMPR, JP_SCLN, JP_COLN, JP_PIPE, KC_BTN3,    KC_0,    KC_1,    KC_2,    KC_3, JP_PLUS, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
               _______, _______,       JP_MHEN, MO(_LOWER), _______, KC_WH_D, _______, MO(_RAISE), JP_DOT,        _______, _______, _______
  //|--------------------------------------------------------------|        |--------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_rotary_layer(
  //,--------------------------------------------------------------|        |--------------------------------------------------------------.
      _______, _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP,LALT(KC_PSCR),KC_PSCR,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
        LCTL_T(KC_F11),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_WH_L, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
               KC_LSFT,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
               _______, _______,          _______, _______, _______, KC_WH_R, _______, _______, JP_HENK,          _______, _______, _______
  //|--------------------------------------------------------------|        |--------------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT_rotary_layer(
  //,--------------------------------------------------------------|        |--------------------------------------------------------------.
        RESET,  KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,LALT(KC_PSCR),KC_PSCR,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
              KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_TOG, RGB_MOD, RGB_SAD, RGB_SAI, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
         SFT_T(KC_F12), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, XXXXXXX, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
               _______, _______,          _______, _______, _______,RGB_RMOD, _______, _______, _______,          _______, _______, _______
  //|--------------------------------------------------------------|        |--------------------------------------------------------------'
  )
};

//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _LOWER:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case _RAISE:
      rgblight_sethsv_at(HSV_RED, 0);
      break;
    case _ADJUST:
      rgblight_sethsv_at(HSV_PURPLE, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at( 0, 0, 0, 0);
      break;
    }
    rgblight_set_effect_range( 1, 14);
#endif
return state;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;
    if (clockwise) {
        key.row = 3;
        key.col = 0;
    } else {
        key.row = 1;
        key.col = 0;
    }
    action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
    action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});
    return true;
}
