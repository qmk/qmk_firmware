/*
Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>

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
#include "jpe230.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_preonic_grid(
  //,-----------------------------------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_LBRC, KC_RBRC, KC_LGUI,   MO(1), _______,  KC_SPC, _______,  KC_ENT,   MO(2), KC_RALT, KC_MINS,  KC_EQL
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [1] = LAYOUT_preonic_grid(
  //,-----------------------------------------------------------------------------------------------------------.
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
       KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______,   CK_UP, AU_TOGG,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_CAPS, _______, _______, _______, _______, _______, _______,   KC_UP, _______, _______, CK_DOWN, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_LSFT, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,KC_RIGHT, _______,  CK_RST, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______,   MO(3), _______, _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [2] = LAYOUT_preonic_grid(
  //,-----------------------------------------------------------------------------------------------------------.
       KC_GRV,  KC_F11,  KC_F12,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_CAPS, _______, KC_MS_U, _______, _______, _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______,  MO(3),  _______, KC_BTN1, _______, _______, _______, _______, _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [3] = LAYOUT_preonic_grid(
  //,-----------------------------------------------------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_MUTE, KC_WBAK, KC_WFWD,   KC_F7,   KC_F8,   KC_F9, _______,    KC_7,    KC_8,    KC_9, _______, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_VOLU, _______, KC_MNXT,   KC_F6,   KC_F5,   KC_F6, _______,    KC_6,    KC_5,    KC_4, _______, QK_MAKE,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_VOLD, KC_MPRV, KC_MNXT,   KC_F1,   KC_F2,   KC_F3, KC_LSRS,    KC_1,    KC_2,    KC_3, _______, DB_TOGG,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      MU_TOGG, MU_NEXT, _______, _______, _______, KC_LSRE, _______, KC_LERS, _______, _______, _______,  EE_CLR
  //`-----------------------------------------------------------------------------------------------------------'
  )
};

/* 
Logic to shift between the bars:
    KC_LSRE => Left Bar - Space... Right Bar - Enter
    KC_LERS => Left Bar - Enter... Right Bar - Space
    KC_LSRS => Left Bar - Space... Right Bar - Space

    Hack into dynamic_keymap_set_keycode and change the value of the keymap.
    (Just like VIA does, but instead it is done inside the keyboard so no need
    to open the app)

    Possible alternatives:
        - Create 3 layers but only change the KC_ENTER and KC_SPACE position between them
        - Create a custom keycode and use process_record_user to alter the behaviour
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
    case KC_LSRS:
      dynamic_keymap_set_keycode(LEFT_BAR, KC_SPC);
      dynamic_keymap_set_keycode(RIGHT_BAR, KC_SPC);
      PLAY_SONG(song_lsrs);
      return false;
    case KC_LERS:
      dynamic_keymap_set_keycode(LEFT_BAR, KC_ENT);
      dynamic_keymap_set_keycode(RIGHT_BAR, KC_SPC);
      PLAY_SONG(song_lers);
      return false;
    case KC_LSRE:
      dynamic_keymap_set_keycode(LEFT_BAR, KC_SPC);
      dynamic_keymap_set_keycode(RIGHT_BAR, KC_ENT);
      PLAY_SONG(song_lsre);
      return false;
    default:
      return true; // Process all other keycodes normally
    }
  }
  return true;
}
