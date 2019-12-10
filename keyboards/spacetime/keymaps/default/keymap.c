/* Copyright 2019 Kyle Terry
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

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

/*  layer template:
 *  [_LAYER] = LAYOUT(
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, \
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, \
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, \
 *        _______,                        _______, _______, _______,   _______, _______, _______,                        _______
 *  ),
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_LCTL,    KC_RCTL, KC_Y,    KC_U,   KC_I,    KC_O,     KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_LALT,    KC_RALT, KC_H,    KC_J,   KC_K,    KC_L,     KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_LGUI,    KC_APP,  KC_N,    KC_M,   KC_COMM, KC_DOT,   KC_SLSH, KC_ENT,
        KC_LCTL,                        KC_LGUI, KC_SPC, LOWER,      RAISE,   KC_SPC,  KC_RGUI,                        KC_RCTL
  ),

  [_LOWER] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,   _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, KC_MPLY, KC_MNXT,
        _______,                        _______, _______, _______,   _______, _______, _______,                        _______
  ),

  [_RAISE] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,   _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU,
        _______,                        _______, _______, _______,   _______, _______, _______,                        _______
  ),

  [_ADJUST] = LAYOUT(
    _______, _______, KC_PGUP, _______, _______, _______, _______,   _______, _______, _______, KC_INS,  _______, KC_PSCR, _______,
    _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
        _______,                        _______, _______, _______,   _______, _______, _______,                        _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
