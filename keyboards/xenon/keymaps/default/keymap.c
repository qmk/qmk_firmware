/* Copyright 2020 Kyrre Havik Eriksen
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

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define M_LWR MO(_LOWER)
#define M_RSE MO(_RAISE)
#define L(kc) (LSFT(kc))
#define R(kc) (RALT(kc))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
      KC_TAB,    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
      KC_LCTL,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
                         KC_MUTE, KC_RALT, KC_LALT, KC_LGUI, KC_SPC,      KC_ENT,  M_LWR,   KC_BSPC, M_RSE,   KC_MPLY,
                                  KC_DEL , KC_PGDN, KC_PGUP, KC_ESC,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [_LOWER] = LAYOUT(
      KC_BSLS,   KC_1,   KC_2,    KC_3,    KC_4,   KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
      KC_TRNS,   L(KC_1),L(KC_2), L(KC_3), L(KC_4),L(KC_5),                      L(KC_6), L(KC_7), L(KC_8), L(KC_9), L(KC_0), L(KC_MINS),
      KC_TRNS,   KC_GRV, KC_TRNS, L(KC_EQL),L(KC_RBRC),L(KC_BSLS),              KC_BSLS, KC_RBRC, KC_EQL,  KC_VOLD, KC_VOLU, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,       KC_ENT, KC_SPC,  KC_TRNS,  KC_TRNS, KC_RALT,
                                  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,       KC_ENT, KC_SPC,  KC_TAB,  KC_BSPC
    ),
    [_RAISE] = LAYOUT(
      KC_F1,     KC_F2,  KC_F3,   KC_F4,  KC_F5,  KC_F6,                        KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,
      KC_LCTL,   KC_A,   KC_S,    KC_D,   KC_F,   KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,   KC_Z,   KC_X,    KC_C,   KC_V,   KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
                         KC_LGUI, KC_DEL, KC_ENT, KC_SPC, KC_ESC,       KC_ENT, KC_SPC,  KC_TAB,  KC_BSPC, KC_RALT,
                                  KC_DEL, KC_ENT, KC_SPC, KC_ESC,       KC_ENT, KC_SPC,  KC_TAB,  KC_BSPC
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
  uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
