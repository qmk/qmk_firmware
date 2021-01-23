/*
Copyright 2016 Priyadi Iman Nurcahyo <priyadi@priyadi.net>

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

enum layers {
  DVO, // dvorak
  QWE, // qwerty
  SYS, // system
};

enum keycodes {
  // default layout switcher
  LAY_DVO = SAFE_RANGE,
  LAY_QWE,

  // layer switchers
  LYR_SYS,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* dvorak */
    [DVO] = LAYOUT(
                                   KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_PSCR, MO(SYS), KC_PAUS,
                                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,

    XXXXXXX, XXXXXXX,     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, XXXXXXX, KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,     KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_MNXT, KC_VOLU,     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,           XXXXXXX,     KC_DEL,  KC_END,  KC_PGDN,     KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_MPLY, KC_MUTE,     KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,          KC_BSLS, KC_ENT,               KC_UP,                KC_P4,   KC_P5,   KC_P6,   KC_PCMM,
    KC_MPRV, KC_VOLD,     KC_LSFT, _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             XXXXXXX, KC_RSFT,     KC_LEFT, XXXXXXX, KC_RGHT,     KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LGUI, KC_APP,      KC_LCTL,          KC_LALT,                            KC_SPC,                                               KC_RALT,          KC_RCTL,              KC_DOWN,              XXXXXXX, KC_P0,   KC_PDOT, XXXXXXX
    ),
    /* qwerty */
    [QWE] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,   _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,           _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, KC_GRV,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,           _______,              _______,              _______, _______, _______, _______
    ),

    /* system */
    [SYS] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, LAY_QWE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, LAY_DVO, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,          _______,              _______,              _______, _______, _______, _______
    ),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /* layout switcher */
    case LAY_QWE:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<QWE);
      }
      return false;
      break;
    case LAY_DVO:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<DVO);
      }
      return false;
      break;

  }
  return true;
}
