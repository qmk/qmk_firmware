/*
Copyright 2019 Khader Syed

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

enum siroleo_layers
{
    _QWERTY,
    _COLEMAK,
    _FNM
};

enum siroleo_keycodes
{
    QWERTY = SAFE_RANGE,
    COLEMAK
};

#define FNM MO(_FNM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE layer: Default Layer
   * ,--------------------------------------------------------------------------------------------------.
   * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | Backspace |  | `   |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Bksp  |  | Del |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | `       |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
   * |--------------------------------------------------------------------------------------------+
   * | Shift      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift       | Up  |
   * +--------------------------------------------------------------------------------------------+-----+
   * | Ctrl  | Alt   | Gui  |               Space                | Fn  | Ctrl | Alt   | Left| Down|Right|
   * `--------------------------------------------------------------------------------------------------´
   */
  [_QWERTY] = LAYOUT(
        KC_GESC, KC_1,   KC_2,   KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,   KC_9,  KC_0,   KC_MINS,KC_EQL, KC_BSPC,    KC_GRV,
        KC_TAB,  KC_Q,   KC_W,   KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,   KC_O,  KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,    KC_DEL,
        KC_GRV , KC_A,   KC_S,   KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,   KC_L,  KC_SCLN,KC_QUOT,     KC_ENT,
        KC_LSFT, KC_Z,   KC_X,   KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,     KC_UP,
        KC_LCTL, KC_LALT,KC_LGUI,          KC_SPC,                      FNM,KC_RCTL,KC_RALT,    KC_LEFT,KC_DOWN,KC_RGHT
    ),
    /* Colemak Layer
   * ,--------------------------------------------------------------------------------------------------.
   * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | Backspace |  | `   |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Bksp  |  | Del |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | `       |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
   * |--------------------------------------------------------------------------------------------+
   * | Shift      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift       | Up  |
   * +--------------------------------------------------------------------------------------------+-----+
   * | Ctrl  | Alt   | Gui  |               Space                | Fn  | Ctrl | Alt   | Left| Down|Right|
   * `--------------------------------------------------------------------------------------------------´
   */
  [_COLEMAK] = LAYOUT(
        KC_GESC, KC_1,   KC_2,   KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,   KC_9,  KC_0,   KC_MINS,KC_EQL, KC_BSPC,    KC_GRV,
        KC_TAB,  KC_Q,   KC_W,   KC_F,  KC_P,  KC_G,  KC_J,  KC_L,  KC_U,   KC_Y,  KC_SCLN,KC_LBRC,KC_RBRC,KC_BSLS,    KC_DEL,
        KC_GRV , KC_A,   KC_R,   KC_S,  KC_T,  KC_D,  KC_H,  KC_N,  KC_E,   KC_I,  KC_O   ,KC_QUOT,     KC_ENT,
        KC_LSFT, KC_Z,   KC_X,   KC_C,  KC_V,  KC_B,  KC_K,  KC_M,  KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,     KC_UP,
        KC_LCTL, KC_LALT,KC_LGUI,          KC_SPC,                      FNM,KC_RCTL,KC_RALT,    KC_LEFT,KC_DOWN,KC_RGHT
    ),
   /* FN layer
   * ,--------------------------------------------------------------------------------------------------.
   * | `   | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |       Mute|  | Vol-|
   * |-----------------------------------------------------------------------------------------+  +-----+
   * |        |     |     |     |     |     |     |     |PrtSc| Slck| Paus|     |     |        |  | Vol+|
   * |-----------------------------------------------------------------------------------------+  +-----+
   * |         |     |     |     |     |     |     |     | Home| PgUp|     |     |             |
   * |--------------------------------------------------------------------------------------------+
   * |            |     |     |     |     |     |     |     | End | PgDn|     | Mouse Btn 1 | MsU |
   * +--------------------------------------------------------------------------------------------+-----+
   * |       | Reset |      |                                    |      |      |      | MsL | MsD | MsR |
   * `--------------------------------------------------------------------------------------------------´
   */
  [_FNM] = LAYOUT(
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_MUTE,     KC_VOLU,
        _______,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,_______,_______,  RESET,     KC_VOLD,
        _______,_______,_______, QWERTY,COLEMAK,_______,_______,_______,KC_HOME,KC_PGUP,_______,_______,     _______,
        _______,_______,_______,_______,_______,_______,_______,_______,KC_END, KC_PGDN,_______,KC_BTN1,     KC_MS_U,
        _______,_______,_______,                _______,               _______,_______,_______,       KC_MS_L,KC_MS_D,KC_MS_R
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
  }
  return true;
}