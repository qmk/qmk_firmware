/* Copyright 2015-2017 Jack Humbert
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

#include "preonic.h"
#include "action_layer.h"

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = {
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT)},
    {KC_GRV,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,   KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, KC_BSLS}
  },
  [_LOWER] = {
    {_______, _______,_______, _______, _______, _______,   _______, _______, _______, _______, _______, _______},
    { KC_GRV, KC_SLSH,   KC_7,    KC_8,    KC_9, _______,   KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_VOLU, _______},
    {KC_TILD, KC_MINS,   KC_4,    KC_5,    KC_6, KC_PPLS,   KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_MUTE, _______},
    {_______, KC_UNDS,   KC_1,    KC_2,    KC_3,  KC_EQL,   _______, _______, _______, _______, KC_VOLD, _______},
    { KC_ENT, _______,   KC_0,  KC_DOT, _______, KC_COMM,   _______, _______, _______, _______, _______, _______}
  },
  [_RAISE] = {
    {_______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_DEL },
    {_______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  _______, _______, KC_LPRN, KC_RPRN, _______, _______},
    {_______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,  _______,  KC_INS, KC_LBRC, KC_RBRC, KC_PIPE, _______},
    {_______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,  _______,  KC_DEL, KC_LABK, KC_RABK, KC_SLSH, KC_BSLS},
    {_______, _______, _______, _______, _______, _______,  _______, _______, KC_LCBR, KC_RCBR, _______, _______}
  },
  [_ADJUST] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};
