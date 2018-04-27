/* Copyright 2017 Paul Ewing
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
#include "speedo.h"

#define _______ KC_TRNS
#define FN MO(_FN)
#define TORST TO(_RESET)
#define TODFT TO(_DEFAULT)
#define TODO KC_NO

enum speedo_layers {
  _DEFAULT,
  _FN,
  _RESET
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_DEFAULT] = KEYMAP(
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_UP,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_DOWN,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LEFT,  KC_RGHT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_LCTL, KC_LGUI, KC_LALT, KC_GRV,  FN,      KC_BSPC, KC_DEL,   KC_ENT,  KC_SPC,  FN,      TODO,    KC_RALT, KC_RGUI, KC_RCTL \
),

[_FN] = KEYMAP(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,   TORST, \
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,      _______,     KC_PGUP, KC_HOME, KC_END,  _______, _______, _______, \
    KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_PAUS,      _______,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_INS,  _______, _______, KC_PGDN, KC_LBRC, KC_RBRC, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

[_RESET] = KEYMAP(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TODFT, \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO \
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
