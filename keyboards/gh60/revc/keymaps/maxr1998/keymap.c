/*
Copyright 2017 Max Rumpf alias Maxr1998 <max.rumpf1998@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define KC_EURO RALT(KC_5)

#define SWITCH_LANG SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)))
#define PRINT_UMLAUT(str) SWITCH_LANG;_delay_ms(90);SEND_STRING(str);SWITCH_LANG;

enum custom_keycodes {
    MCO_AE = SAFE_RANGE,
    MCO_OE = SAFE_RANGE + 1,
    MCO_UE = SAFE_RANGE + 2,
    MCO_SS = SAFE_RANGE + 3,
    TP_REQ = SAFE_RANGE + 10,
    TP_ACC = SAFE_RANGE + 11
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: qwertz */
  LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,\
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NO,  \
    KC_LOCK, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_HOME, KC_ENT, \
    KC_LSFT, KC_BSLS, KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT,\
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_NO,   MO(1),   KC_LEFT, KC_DOWN, KC_RGHT),
  /* 1: fn */
  LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_EURO, TP_REQ,  TP_ACC,  KC_TRNS, MCO_UE,  KC_TRNS, MCO_OE,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
    KC_TRNS, MCO_AE,  MCO_SS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_SW,KC_TRNS, KC_GRV,  KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUI, RGB_HUD, KC_TRNS, KC_TRNS, KC_TRNS,\
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case MCO_AE:
      PRINT_UMLAUT("'"); // ä
      return false;
      case MCO_OE:
      PRINT_UMLAUT(";"); // ö
      return false;
      case MCO_UE:
      PRINT_UMLAUT("["); // ü
      return false;
      case MCO_SS:
      PRINT_UMLAUT("-"); // ß
      return false;
      case TP_REQ:
      SEND_STRING("/tpa ");
      return false;
      case TP_ACC:
      SEND_STRING("/tpaccept"SS_TAP(X_ENTER));
      return false;
    }
  }
  return true;
}
