/* Copyright 2017 Mark Smith
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
#include "kbd66.h"

#include "eeconfig.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum kbd66_layers {
  _QWERTY,
  _DVORAK,
  _FUNC
};

enum kbd66_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,----------------------------------------------------------.   ,---.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  +|  Bs  |   |INS|
     * |----------------------------------------------------------|   |---|
     * |Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |   |DEL|
     * |-----------------------------------------------------| Ent|   `---'
     * |Cap  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |
     * |---------------------------------------------------------------.
     * |Shft|  `|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  Shift   | UP|
     * |-------------------------------------------------------------------.
     * |Ctl |Alt |Win |         Space           |Win |Alt | Fn |LFT|DWN|RIG|
     * `-------------------------------------------------------------------'
     */
[_QWERTY] = KEYMAP(
  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME,
  KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_ENT, KC_DEL,
  KC_CAPS,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS,
  KC_LSPO, KC_NONUS_BSLASH, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,
  KC_LCTL, KC_LALT, KC_LGUI,   KC_SPC,KC_SPC, KC_RGUI, KC_RALT, FUNC,      KC_LEFT, KC_DOWN,   KC_RGHT
),

    /* Dvorak
     * ,----------------------------------------------------------.   ,---.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  +|  Bs  |   |INS|
     * |----------------------------------------------------------|   |---|
     * |Tab |  "|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|     |   |DEL|
     * |-----------------------------------------------------| Ent|   `---'
     * |Cap  |  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|  \|    |
     * |-------------------------------------------------------------.
     * |Shft|  `|  ;|  Q|  J|  K|  X|  B|  M|  W|  V|  Z|  Shift | UP|
     * |-------------------------------------------------------------------.
     * |Ctl |Alt |Win |         Space           |Win |Alt | Fn |LFT|DWN|RIG|
     * `-------------------------------------------------------------------'
     */
[_DVORAK] = KEYMAP(
  KC_ESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,    KC_6,   KC_7, KC_8, KC_9, KC_0,  KC_LBRC, KC_RBRC, KC_BSPC, KC_HOME,
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_SLSH, KC_EQL, KC_ENT, KC_DEL,
  KC_CAPS,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS, KC_BSLS,
  KC_LSPO, KC_NONUS_BSLASH, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_RSPC, KC_UP,
  KC_LCTL, KC_LALT, KC_LGUI,   KC_SPC,KC_SPC, KC_RGUI, KC_RALT, FUNC,      KC_LEFT, KC_DOWN,   KC_RGHT
),

[_FUNC] = KEYMAP(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______,  QWERTY, DVORAK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, _______,  _______, _______, _______,
  _______, _______, _______,   _______,_______, _______, _______, FUNC,      _______, _______,   _______
)

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
      }
      return false;
      break;
  }

  return true;
}

void led_set_user(uint8_t usb_led) {

}
