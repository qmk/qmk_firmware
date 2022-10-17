/* Copyright 2019 John M Daly <jmdaly@gmail.com>
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
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum {
  // Layers
  _L1,
  _L2,
  _L3,
  _L4,
  _L5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_L1] = LAYOUT_standard( /* Qwerty */
    LT(_L5, KC_TAB),        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_BSPC,
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, LT(_L2, KC_QUOT),
    KC_LSPO,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSPC,
    MO(_L2),       KC_LGUI, MO(_L3),          KC_ENT,  LT(_L2, KC_SPC),                    KC_RALT, KC_BSLS,           MO(_L4)
  ),
  [_L2] = LAYOUT_standard( /* LAYER 2 */
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    _______, KC_BSLS, KC_QUOT, KC_MINS, KC_EQL,  KC_LBRC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, KC_ESC,  _______, KC_PSCR, _______, _______, _______, KC_MSTP, KC_LBRC, KC_RBRC, KC_MNXT, _______,
    _______, KC_LGUI, _______,          _______, _______,                   _______, _______,          MO(_L4)
  ),
  [_L3] = LAYOUT_standard( /* LAYER 3 */
    KC_MINS, KC_1,     KC_2,     KC_3,     KC_4,    KC_5,          KC_6,          KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_EQL,  KC_PIPE,  KC_TILD,  KC_UNDS,  KC_PLUS, LSFT(KC_LBRC), LSFT(KC_RBRC), KC_4,    KC_5,    KC_6,    KC_VOLU, KC_INS,
    _______, RGB_TOG,  RGB_MOD,  RGB_RMOD, KC_DQUO, _______,       KC_0,          KC_1,    KC_2,    KC_3,    KC_VOLD, _______,
    _______, _______,  _______,            _______, _______,                               _______, _______,          _______
  ),
  [_L4] = LAYOUT_standard( /* LAYER 4 */
    QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,     KC_PGUP,   _______,
    KC_ESC,  _______, _______, _______, _______, _______, _______, KC_F5,   KC_F6,   KC_HOME,   KC_END,    _______,
    KC_LSFT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_F9,   KC_F10,  KC_PGDN,   KC_F12,    _______,
    _______, KC_LSFT, KC_B,             KC_SPC,  KC_C,                      _______, _______,              _______
  ),
  [_L5] = LAYOUT_standard( /* LAYER 5 */
    _______,   LGUI(KC_1),   LGUI(KC_2),   LGUI(KC_3),   LGUI(KC_4),   LGUI(KC_5),   LGUI(KC_6),   LGUI(KC_7),   LGUI(KC_8),   LGUI(KC_9),     LGUI(KC_0),   LGUI(KC_MINS),
    KC_ESC,  _______, _______, _______, _______, _______, _______, KC_F5,   KC_F6,   KC_HOME,   KC_END,    _______,
    KC_LSFT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_F9,   KC_F10,  KC_PGDN,   KC_F12,    _______,
    _______, KC_LSFT, KC_B,             KC_SPC,  KC_C,                      _______, _______,              _______
  )
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
