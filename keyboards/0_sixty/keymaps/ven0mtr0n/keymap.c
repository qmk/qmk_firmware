/* Copyright 2020 Vinam Arora <vinam@posteo.de>
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

enum zero_sixty_layers {
  _DEFAULT,
  _L1,
  _L2,
  _L3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DEFAULT] = LAYOUT_1x2uC( /* qwerty */
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC ,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT ,
  KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RCTL ,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT ,
  KC_LGUI,  MO(_L3), MO(_L2), KC_LALT, MO(_L1),     KC_SPC,       MO(_L1), KC_RALT, MO(_L2), MO(_L3), KC_RGUI
),

[_L1] = LAYOUT_1x2uC(
  _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
  _______,  KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_TILD, KC_PIPE, KC_GRV,  KC_QUOT, KC_DQUO, KC_PGUP, _______ ,
  _______,  KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGDN, _______ ,
  _______,  KC_APP,  _______, _______, _______, _______, KC_EQL,  KC_UNDS, KC_MINS, KC_PLUS, KC_BSLS, _______ ,
  _______,  _______, _______, _______, _______,     KC_CAPS,      _______, _______, _______, _______, _______
),

[_L2] = LAYOUT_1x2uC(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______ ,
  _______,  _______, _______, _______, _______, KC_VOLU, _______, KC_7,    KC_8,    KC_9,    KC_F11,  _______ ,
  _______,  _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_4,    KC_5,    KC_6,    KC_F12,  _______ ,
  _______,  _______, _______, _______, KC_MUTE, KC_VOLD, KC_MUTE, KC_1,    KC_2,    KC_3,    KC_PSCR, _______ ,
  _______,  _______, KC_CAPS, _______, _______,     _______,      KC_0,    _______, KC_CAPS, _______, _______
),

[_L3] = LAYOUT_1x2uC(
  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
  _______,  _______, _______, _______, _______, _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______ ,
  _______,  _______, KC_ACL2, KC_ACL1, KC_ACL0, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______ ,
  _______,  _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______ ,
  _______,  _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
),

};
