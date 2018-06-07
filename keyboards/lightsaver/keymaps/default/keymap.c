/* Copyright 2017 Rasmus Schults <rasmus.schults@gmail.com>
 *
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

#define KC_F1GL TD(TD_F1_GAME)
#define KC_CLFN TD(TD_CAPS_FN)

enum custom_layers {
    BASE,   // Base QWERTY layer
    FN = 5, // Function layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT(\
      KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_NLCK, KC_INS,  KC_HOME, KC_PGUP, KC_PSLS, \
      KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_DEL,  KC_END,  KC_PGDN, KC_PAST, \
      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, \
      MO(FN),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
      KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,           KC_SLSH, KC_RSFT, KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
      KC_LCTL,  KC_LGUI, KC_LALT,                                              KC_SPC,                    KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT), \

[FN] = LAYOUT(\
      _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS, KC_SLCK, RGB_TOG, RGB_MOD, _______, _______,  \
      _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_CAPS, BL_TOGG, _______, _______, _______,  \
      _______,  _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______,          _______, _______, _______, _______, _______,  \
      _______,  _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,                   _______, _______, _______, _______, _______,  \
      _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, RESET,  \
      _______,  _______, _______,                                              _______,                   _______, _______, _______, _______, _______, _______, _______ ), \

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE;
};
