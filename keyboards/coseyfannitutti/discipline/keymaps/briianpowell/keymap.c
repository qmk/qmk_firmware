/* Copyright 2019 COSEYFANNITUTTI
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

#define FN_ESC LT(_FUNC, KC_ESC)

enum discipline_layers {
  _QWERTY,
  _WORKMAN,
  _FUNC,
};

enum discpline_keycodes {
  QWERTY = SAFE_RANGE,
  WORKMAN,
  FUNC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY: Default Layer
  * ,--------------------------------------------------------------.
  * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backs|  `~|
  * |---------------------------------------------------------------|
  * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Del|
  * |---------------------------------------------------------------|
  * |Fn/CL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|   Enter|PgU|
  * |---------------------------------------------------------------|
  * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
  * |---------------------------------------------------------------|
  * |Ctrl|Gui |Alt |         Space    |Gui |Alt |Ctrl|  |Lef|Dow|Rig|
  * `---------------------------------------------------------------'
  */
  [_QWERTY] = LAYOUT_65_ansi(
    KC_ESC,  KC_1,    KC_2,    KC_3,  KC_4, KC_5, KC_6, KC_7, KC_8,   KC_9,  KC_0,   KC_MINS, KC_EQL, KC_BSPC,  KC_GRV,
    KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R, KC_T, KC_Y, KC_U, KC_I,   KC_O,  KC_P,   KC_LBRC,KC_RBRC, KC_BSLS,  KC_DEL,
    FN_ESC,  KC_A,    KC_S,    KC_D,  KC_F, KC_G, KC_H, KC_J, KC_K,   KC_L,  KC_SCLN,KC_QUOT,         KC_ENT,  KC_HOME,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,  KC_V, KC_B, KC_N, KC_M, KC_COMM,KC_DOT,KC_SLSH,        KC_RSFT, KC_UP,    KC_END,
    KC_LCTL,  KC_LGUI, KC_LALT,            KC_SPC,                  KC_RALT, KC_RGUI, KC_RCTL,KC_LEFT, KC_DOWN, KC_RGHT
  ),

  /* Workman
   * ,---------------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backs|  `~|
   * |---------------------------------------------------------------|
   * |Tab  |  Q|  D|  R|  W|  B|  J|  F|  U|  P|  ;|  [|  ]|   \| Del|
   * |---------------------------------------------------------------|
   * |Fn/CL |  A|  S|  H|  T|  G|  Y|  N|  E|  O|  I|  '|  Enter| PgU|
   * |---------------------------------------------------------------|
   * |Shift   |  Z|  X|  M|  C|  V|  K|  L|  ,|  .|  /|Shift |Up| PgD|
   * |---------------------------------------------------------------|
   * |Ctrl|Alt |Gui |         Space    |Gui |Alt |Ctrl|  |Lef|Dow|Rig|
   * `---------------------------------------------------------------'
   */
  [_WORKMAN] = LAYOUT_65_ansi(
      KC_ESC,  KC_1,   KC_2,   KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS,  KC_EQL, KC_BSPC, KC_GRV,
      KC_TAB,  KC_Q,   KC_D,   KC_R, KC_W, KC_B, KC_J, KC_F, KC_U,    KC_P,   KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
      FN_ESC,  KC_A,   KC_S,   KC_H, KC_T, KC_G, KC_Y, KC_N, KC_E,    KC_O,   KC_I,    KC_QUOT,          KC_ENT, KC_HOME,
      KC_LSFT,  KC_Z,   KC_X,   KC_M, KC_C, KC_V, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH,         KC_RSFT,  KC_UP,   KC_END,
      KC_LCTL,  KC_LGUI,KC_LALT,            KC_SPC,                  KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Function
     * ,---------------------------------------------------------------.
     * |RST| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|     |     |
     * |---------------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |INS|
     * |---------------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |HME|
     * |---------------------------------------------------------------|
     * |    |   |   |   |   |   |   |   |   |   |   |   |      |VL+|END|
     * |---------------------------------------------------------------|
     * |    |    |    |      PLY/PS      |    |    |    |  |PRV|VL-|NXT|
     * `---------------------------------------------------------------'
     */
    [_FUNC] = LAYOUT_65_ansi(
      _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,_______,   QK_BOOT,
      _______,KC_WH_U,KC_BTN1,KC_MS_U,KC_BTN2,_______,_______,AG_NORM,AG_SWAP,QWERTY,WORKMAN,_______,_______,_______,   KC_INS,
      _______,KC_WH_D,KC_MS_L,KC_MS_D,KC_MS_R,_______,_______,_______,_______,_______,_______,_______,       _______,  KC_PGUP,
      _______,KC_WH_L,KC_BTN3,KC_WH_R,_______,_______,_______,_______,_______,_______,_______,        _______,KC_VOLU, KC_PGDN,
      _______,_______,_______,                        KC_MPLY,                _______,_______,_______,KC_MPRV,KC_VOLD, KC_MNXT
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
  }
  return true;
}
