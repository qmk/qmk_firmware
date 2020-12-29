/* 
 * Copyright 2020 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2020 Anthony MARIN <anthony@hidtech.ca>
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

#define MACLOCK LGUI(LCTL(KC_Q)) // Lock my MacBook!

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
  KC_GRV,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
                             MO(1),   KC_BSPC, KC_DEL,  KC_ENT,  KC_SPC,  MO(2), \
                                      KC_LCTL, KC_LALT, KC_RGUI, KC_RCTL
  ),

[1] = LAYOUT(
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
  _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_CAPS, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_PGUP, _______, KC_PLUS, KC_LCBR, KC_RCBR, _______, \
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_END,  KC_PGDN, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, \
                             _______, _______, _______, _______, _______, _______, \
                                      RESET,   MACLOCK, _______, _______
  ),

[2] = LAYOUT(
  KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
  _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_CAPS, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_PGUP, _______, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_END,  KC_PGDN, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, \
                             _______, _______, _______, _______, _______, _______, \
                                      _______, MACLOCK, _______, RESET
  ),
};