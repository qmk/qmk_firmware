/*
Copyright 2020 worldspawn00

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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _MEDIA };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,           KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSPC,    KC_PSCR,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_INS,
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,              KC_DEL,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       MO(_MEDIA),  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,            KC_UP,
    KC_LCTL, KC_LGUI,  KC_LALT,          KC_SPC,  MO(_FN),                        KC_BSPC,           KC_RALT,      KC_RCTL,       KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN] = LAYOUT(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,           KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,    KC_PAUS,
    _______, _______, _______, _______, QK_BOOT,   _______,                  _______, _______, _______, _______, _______, _______, _______, _______,    _______,
    _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                  _______, _______, _______, _______, _______, _______, _______,             _______,
    _______, RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, _______,        _______,  _______, _______, _______, _______, _______, _______,           KC_PGUP,
    _______, _______, _______,          _______, _______,                         _______,           _______,      _______,       KC_HOME, KC_PGDN, KC_END
  ),

  [_MEDIA] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,    QK_BOOT,
    _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, _______, _______,    _______,
    _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, KC_MPLY,             _______,
    _______, _______, _______, _______, _______, _______,        _______,  _______, _______, _______, _______, _______, _______,           KC_VOLU,
    _______, _______, _______,          _______, _______,                         _______,           _______,      _______,       KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [3] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,    _______,
    _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, _______, _______,    _______,
    _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, _______,             _______,
    _______, _______, _______, _______, _______, _______,        _______,  _______, _______, _______, _______, _______, _______,           _______,
    _______, _______, _______,          _______, _______,                         _______,           _______,      _______,       _______, _______, _______
  )
};

void matrix_init_user(void) {
  // set CapsLock LED to output and off (active high)
  setPinOutput(F5);
  // set NumLock LED to output and off (active high)
  setPinOutput(F6);
  // set ScrollLock LED to output and off (active high)
  setPinOutput(F7);
}

// write to above indicators in a binary fashion based on current layer
layer_state_t layer_state_set_user(layer_state_t state)
{
    writePin(F5, (state & 0x1));
    writePin(F6, (state & 0x2));
    writePin(F7, (state & 0x4));
    return state;
}
