/* Copyright 2021 FluxLab
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
enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty */
[_QWERTY] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MUTE,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_DEL,  LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_LBRC, KC_RBRC, KC_QUOT, KC_MINS
),

/* Lower */
[_LOWER] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, _______, _______, KC_UP,   _______, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______,
    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_1,    KC_2,    KC_3,    KC_BSLS, _______,
    _______, _______, _______, _______, LOWER,   _______, _______, KC_0,    KC_0,    KC_DOT,  KC_BSLS, KC_EQL
),

/* Raise */
[_RAISE] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    UG_HUEU, UG_SATU, UG_VALU, UG_NEXT, _______, UG_TOGG, _______, _______, _______, _______, _______, _______,
    UG_HUED, UG_SATD, UG_VALD, UG_PREV, _______, UG_TOGG, _______, _______, _______, _______, KC_UP,   _______,
    _______, _______, _______, _______, _______, _______, _______, RAISE,   _______, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Adjust (Lower + Raise) */
[_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
    tap_code(KC_VOLD);
  } else {
    tap_code(KC_VOLU);
  }
  return true;
}
