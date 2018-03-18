/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "30sqrt2.h"
/*
* .-----------------------------------------------------------------------------------------.
* | ESC| | F1| F2| F3| F4|  | F5| F6| F7| F8|  | F9| F10| F11| F12|  | DEL | INS| PGDN| PGUP|
* |---------------------------------------------------------------|  |----------------------|
* |  ~ | 1 |  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  BS |    |  | NUM |  /  | *  |  -  |
* |---------------------------------------------------------------|  |----------------------|
* |TAB |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| \  |     |  |  7  |  8  |  9 |     |
* |---------------------------------------------------------------|  |----------------------|
* |CAPS|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|   |ENT |     |  |  4  |  5  |  6 |     |
* |---------------------------------------------------------------|  |----------------------|
* |SHFT|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|SHF|   |    |  | UP || 1  |  2  |  3 |     |
* |-----------------------------------------------------------------------------------------|
* |CTRL|GUI|ALT|   |   |   |   |   |   |   |ALT|GUI|MEN|  LEFT|DOWN |RGHT | |0  |  . |    |
* `-----------------------------------------------------------------------------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = KEYMAP( \
      KC_ESC,        KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,   KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,                                      KC_DEL, KC_INS, KC_PGUP,KC_PGDN, \
      KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6, KC_7,   KC_8,   KC_9,    KC_0,   KC_MINS, KC_EQL,  KC_BSPC, KC_NO,                  KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,  KC_Y, KC_U,   KC_I,   KC_O,    KC_P,   KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,                  KC_P7,  KC_P8,  KC_P9,  KC_PPLS, \
      KC_CAPS, KC_A,    KC_S,  KC_D,  KC_F,  KC_G, KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,  KC_NO, KC_NO,                    KC_P4,  KC_P5,  KC_P6,  KC_NO, \
      KC_LSFT, KC_Z,    KC_X,  KC_C,  KC_V,  KC_B, KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_NO,   KC_RSFT, KC_NO,               KC_UP,      KC_P1,  KC_P2,  KC_P3,  KC_PENT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC,   KC_SPC, KC_SPC,  KC_SPC,   KC_SPC,  KC_RALT, KC_RCTL, KC_MENU,   KC_LEFT,KC_DOWN,KC_RGHT,        KC_P0,  KC_PDOT, KC_NO \
    ),
    // [1] = KEYMAP(
    //   _______,        _______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______, _______,  _______,                                                                  _______,_______,_______,_______,
    //   _______,  _______,    _______,    _______,  _______,  _______,  _______, _______,   _______,   _______,    _______,   _______, _______,  _______, _______,                                  _______,_______,_______,_______,
    //   _______,  _______,    _______,    _______,  _______,  _______,  _______, _______,   _______,   _______,    _______,   _______, _______,  _______, _______,                                  _______,_______,_______,_______,
    //   _______,  _______,    _______,    _______,  _______,  _______,  _______, _______,   _______,   _______,    _______,   _______, _______,  _______, _______,                                  _______,_______,_______,_______,
    //   _______,  _______,    _______,    _______,  _______,  _______,  _______, _______,   _______,   _______,    _______,   _______, _______,  _______,                 _______,                  _______,_______,_______,_______,
    //   _______,  _______,    _______,    _______,  _______,  _______,  _______, _______,   _______,   _______,    _______,   _______, _______,                  _______, _______, _______,                 _______,_______,_______
    //   ),
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
