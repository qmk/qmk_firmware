/* Copyright 2019 jrfhoutx
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

// Defines the keycodes used by our macros in process_record_user
//enum custom_keycodes {
//  QMKBEST = SAFE_RANGE,
//  QMKURL
//};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* Keymap BASE: (Base Layer) Default Layer
   * .----.,----------------------------------------------------------------------.
   * | M1 || ~ | 1 |  2|  3|  4|  5|  6|          |  7|  8|  9|  0|  -|  =|Backsp |
   * |----||----------------------------------------------------------------------|
   * | M2 ||Tab  |  Q|  W|  E|  R|  T|          |  Y|  U|  I|  O|  P| [ | ] |  \  |
   * |----||----------------------------------------------------------------------|
   * | M3 ||Ctrl   |  A|  S|  D|  F|  G|          |  H|  J|  K|  L|  ;|  '|Return |
   * `----'|----------------------------------------------------------------------|
   *       |Shift   |  Z|  X|  C|  V|  B|     |  B|  N|  M|  ,|  .|  /|Shift | Fn |
   *       |----------------------------------------------------------------------|
   *       |CAPS|    | Alt | Space | Fn |     | Space | Alt |               | Ctrl|
   *       `----------------------------------------------------------------------'
   */
[0] = LAYOUT_alice( /* OSA Base */
	KC_DEL,   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,              KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
	KC_PGUP,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    					 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_PGDN,  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,    					 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
	          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,	                     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_HOME,
	          KC_LCTL,          KC_LALT,          KC_SPC, MO(1),                     KC_SPC,                    KC_RALT,                            KC_RCTL
  ),
/* Keymap BASE: (Base Layer) Default Layer
   * .----.,----------------------------------------------------------------------.
   * | M1 || ~ | 1 |  2|  3|  4|  5|  6|          |  7|  8|  9|  0|  -|  =|Backsp |
   * |----||----------------------------------------------------------------------|
   * | M2 ||Tab  |  Q|  W|  E|  R|  T|          |  Y|  U|  I|  O|  P| [ | ] |  \  |
   * |----||----------------------------------------------------------------------|
   * | M3 ||Ctrl   |  A|  S|  D|  F|  G|          |  H|  J|  K|  L|  ;|  '|Return |
   * `----'|----------------------------------------------------------------------|
   *       |Shift   |  Z|  X|  C|  V|  B|     |  B|  N|  M|  ,|  .|  /|Shift | Fn |
   *       |----------------------------------------------------------------------|
   *       |CAPS|    | Alt | Space | Fn |     | Space | Alt |               | Ctrl|
   *       `----------------------------------------------------------------------'
   */
[1] = LAYOUT_alice( /* OSA Layer 1 */
	KC_DEL,   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,              KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
	KC_PGUP,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    					 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_PGDN,  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,    					 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
	          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,	                     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_HOME,
	          KC_LCTL,          KC_LALT,          KC_SPC, _______,                     KC_SPC,                    KC_RALT,                            KC_RCTL
  ),
};




//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//  switch (keycode) {
//    case QMKBEST:
//      if (record->event.pressed) {
//        // when keycode QMKBEST is pressed
//        SEND_STRING("QMK is the best thing ever!");
//      } else {
//       // when keycode QMKBEST is released
//      }
//      break;
//    case QMKURL:
//      if (record->event.pressed) {
//        // when keycode QMKURL is pressed
//       SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
//      } else {
//        // when keycode QMKURL is released
//     }
//      break;
//  }
//  return true;
//}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
