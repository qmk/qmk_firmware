/* Copyright 2020 Michael Doo
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


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name
enum otd_layers {
  _QWERTY,
  _MAC,
  _DVORAK,
  _COLEMAK,
  _FUNCTION
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _QWERTY: Base Layer (default)
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    BSp|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Caps   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------'
     * |Ctrl |Gui|Alt  |         Space         |Alt  |  Fn   |Ctrl |
     * `-----------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,        KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,        KC_NO,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,       KC_NO,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_NO,   KC_RALT, MO(_FUNCTION), KC_RCTL
    ),

  /* Keymap _MAC: Mac Layout
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    BSp|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Caps   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------'
     * |Ctrl |Opt|Cmd  |         Space         |Cmd  |  Fn   |Ctrl |
     * `-----------------------------------------------------------'
     */
    [_MAC] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,        KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,        KC_NO,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,       KC_NO,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_NO,   KC_RGUI, MO(_FUNCTION), KC_RCTL
    ),

  /* Keymap _DVORAK: Dvorak Layout
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|    BSp|
     * |-----------------------------------------------------------|
     * |Tab  |  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|    \|
     * |-----------------------------------------------------------|
     * |Caps   |  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|Enter  |
     * |-----------------------------------------------------------|
     * |Shift   |  ;|  Q|  J|  K|  X|  B|  M|  W|  V|  Z|Shift     |
     * |-----------------------------------------------------------'
     * |Ctrl |Gui|Alt  |         Space         |Alt  |  Fn   |Ctrl |
     * `-----------------------------------------------------------'
     */
    [_DVORAK] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC,       KC_BSPC,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,        KC_BSLS,
        KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,        KC_NO,
        KC_LSFT,          KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,       KC_NO,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_NO,   KC_RALT, MO(_FUNCTION), KC_RCTL
    ),

  /* Keymap _COLEMAK: Colemak Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|    BSp|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Caps   |  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Enter  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|Shift     |
     * |-----------------------------------------------------------'
     * |Ctrl |Gui|Alt  |         Space         |Alt  |  Fn   |Ctrl |
     * `-----------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,        KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,       KC_BSLS,
        KC_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,        KC_NO,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,       KC_NO,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_NO,   KC_RALT, MO(_FUNCTION), KC_RCTL
    ),

  /* Keymap _FUNCTION: Function Layer
  */
    [_FUNCTION] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,        _______,
        _______, _______, KC_UP,   _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______,       _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,
        _______, _______, _______,                            _______,                            _______, _______, MO(_FUNCTION), _______
    ),
};

/* Set DIP switch options here
 *
 * _BV(x) represents the x position of the switch,
 * where 0 is the leftmost postiion.
 *
 * Use bitwise operators to check if one or more
 * switches are active.
 *
 * See the docs for more info: docs/feature_dip_switch.md
 */
void dip_switch_update_mask_user(uint32_t state) {
  if ((state & (_BV(0) | _BV(1))) == (_BV(0) | _BV(1))) {
    layer_on(_COLEMAK);
  } else {
    layer_off(_COLEMAK); // Guard against layer being active
    if ((state & _BV(0)) == _BV(0)) {
      layer_on(_MAC);
    } else {
      layer_off(_MAC);
    }
    if ((state & _BV(1)) == _BV(1)) {
      layer_on(_DVORAK);
    } else {
      layer_off(_DVORAK);
    }
  }

  if ((state & _BV(2)) == _BV(2)) {
    keymap_config.capslock_to_control = true;
  } else {
    keymap_config.capslock_to_control = false;
  }
}
