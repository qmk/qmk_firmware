/* Copyright 2019 LanceMercado
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
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16
// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,          KC_R,               KC_T,              KC_Y,          KC_U,               KC_I,          KC_O,    KC_P,  \
  KC_A,    KC_S,    KC_D,          KC_F,               KC_G,              KC_H,          KC_J,               KC_K,          KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,          KC_V,               KC_B,              KC_N,          KC_M,               KC_COMM,       KC_DOT,  KC_SLSH, \
  KC_ESC,  KC_LGUI, ALT_T(KC_ENT), LT(_LOWER, KC_DEL), CTL_T(KC_BSPC),    SFT_T(KC_SPC), LT(_RAISE, KC_TAB), OSM(MOD_RSFT), KC_PSCR, KC_ENT \
),

[_RAISE] = LAYOUT( \
  KC_EXLM,    KC_AT,    KC_HASH, KC_DLR,      KC_PERC,      KC_PLUS,  KC_7,     KC_8,   KC_9, KC_0, \
  KC_CIRC,    KC_AMPR,  KC_UNDS, KC_DQUO,     KC_QUOT,      KC_MINUS, KC_4,     KC_5,   KC_6, KC_EQL, \
  KC_PIPE,    KC_BSLS,  KC_TILD, KC_GRV,      KC_CALC,      KC_ASTR,  KC_1,     KC_2,   KC_3, KC_TRNS, \
  KC_TRNS,    KC_TRNS,  KC_TRNS, MO(_ADJUST), KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS \
),


[_LOWER] = LAYOUT( \
  KC_VOLU,  KC_HOME, KC_UP,   KC_END,   KC_INS,      KC_LPRN, KC_RPRN,     KC_TRNS, KC_TRNS, KC_CAPS, \
  KC_MUTE,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGUP,     KC_LBRC, KC_RBRC,     KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_VOLD,  KC_MPRV, KC_MPLY, KC_MNXT,  KC_PGDN,     KC_LCBR, KC_RCBR,     KC_TRNS, KC_TRNS,  KC_TRNS, \
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, MO(_ADJUST), KC_TRNS, KC_TRNS, KC_TRNS \
),


[_ADJUST] =  LAYOUT( \
  KC_ACL0, KC_ACL1, KC_MS_U, KC_ACL2, KC_WH_U,      KC_BTN1, KC_F7,    KC_F8,   KC_F9,    KC_F10, \
  KC_SLEP, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,      KC_BTN2, KC_F4,    KC_F5,   KC_F6,    KC_F11, \
  RESET,   KC_BTN4, KC_BTN5, KC_WH_L, KC_WH_R,      KC_BTN3, KC_F1,    KC_F2,   KC_F3,    KC_F12, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS  \
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
