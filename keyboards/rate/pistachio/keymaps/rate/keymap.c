/* Copyright 2020 rate
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
#include "keymap_japanese.h"


enum layer_names {
    _QWERTY = 0,
    _FN,
    _NUM
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
               KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_DEL,            KC_F5,  KC_F6,   KC_F7,   KC_F8,  KC_F9,   KC_F10,   KC_F11,  KC_F12,
      KC_0,    JP_ZKHK,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,      KC_7,   KC_8,    KC_9,    KC_0,   JP_MINS, JP_CIRC,  JP_YEN,  KC_BSPC,  KC_DEL,
      KC_H,    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,              KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    JP_AT,    JP_LBRC,           KC_HOME,
      KC_U,    KC_ENT,   KC_A,    KC_S,    KC_D,    KC_F,  KC_G,              KC_H,   KC_J,    KC_K,    KC_L,   JP_SCLN, JP_COLN,  JP_RBRC, KC_ENT,   KC_END,
      KC_VOLU, KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,              KC_N,   KC_M,    JP_COMM, JP_DOT, JP_SLSH, JP_BSLS,           KC_RSFT,  KC_PGUP,
      KC_VOLD, KC_LCTL,  KC_LGUI, KC_LALT, KC_LALT, LT(_NUM, KC_M),  KC_SPC,  LT(_FN, KC_SPC), KC_MPLY, JP_KANA, KC_UP,  KC_DOWN,  KC_INS,  KC_RCTL,  KC_PGDN
    ),
     [_FN] = LAYOUT(
                _______, _______, _______, _______, _______,  _______,                _______, _______, _______, _______,  _______, _______, _______, _______,
      RGB_VAI,  _______, _______, _______, _______, _______,  _______, _______,       _______, _______, _______, _______,  _______, _______, _______, _______, _______,
      RGB_VAD,  _______, _______, _______, _______, KC_UP,    _______,                _______, KC_HOME, KC_END,  _______,  KC_PGUP, _______, _______,          _______,
      _______,  _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,                KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT, KC_PGDN, _______, _______, _______, _______,
      RGB_HUI,  _______, _______, _______, _______, _______,  _______,                _______, _______, _______, _______,  _______,          _______, _______, RGB_SAI,
      RGB_HUD,  _______, _______, _______, _______, _______,  _______,                _______,          _______, _______,  _______, _______, _______, _______, RGB_SAD
    ),
    [_NUM] = LAYOUT(
                _______, _______, _______, _______, _______,  _______,                _______, _______, _______, _______,  _______, _______, _______, _______,
      RGB_VAI,  _______, _______, _______, _______, _______,  _______, _______,       _______, _______, _______, _______,  KC_PMNS, _______, _______, _______, _______,
      RGB_VAD,  KC_7,    KC_8,    KC_9, _______, _______,  _______,                   KC_7,    KC_8,    KC_9,    _______,  _______, _______, _______,          _______,
      _______,  KC_4,    KC_5,    KC_6, _______, _______,  _______,                   KC_4,    KC_5,    KC_6,    _______,  KC_PPLS, KC_PAST, _______, _______, _______,
      RGB_HUI,  KC_1,    KC_2,    KC_3, KC_0, JP_DOT,  _______,                       KC_1,    KC_2,    KC_3,    _______,  KC_PSLS,          _______, _______, RGB_SAI,
      RGB_HUD,  _______, _______, _______, _______, _______,  _______,                KC_0,          _______,    JP_DOT,   _______, _______, _______, _______, RGB_SAD
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case RGB_RST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
          }
        break;
  }

  return true;
}
