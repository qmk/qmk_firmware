/* Copyright 2019 Luciano M
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
enum custom_keycodes {
  MESON = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
  [0] = LAYOUT( /* Base */
    KC_ESC,  KC_Q, KC_W, KC_E, KC_R,  KC_T, KC_TAB,         KC_BSLS, KC_Y,   KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC, 
    KC_LCTL, KC_A, KC_S, KC_D, KC_F,  KC_G, KC_LALT,        KC_GRV,  KC_H,   KC_J,  KC_K,    KC_L,   KC_SCLN, KC_ENT, 
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V,  KC_B, KC_LGUI,        KC_B,    KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_QUOT, 
                               MO(1), KC_SPC,                        KC_SPC, MO(2) 
  ),
  
  [1] = LAYOUT( /* Symbols */
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TAB,        KC_BSLS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RGB_VAI, 
    KC_LCTL, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RGB_VAD, 
    KC_LSFT, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_LGUI,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,  MESON,  RGB_MOD, 
                                        MO(1),   KC_SPC,                          KC_SPC,  MO(3) 
  ),
  
  [2] = LAYOUT( /* Numbers */
    KC_GRV,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_TAB,         KC_BSLS, KC_6,    KC_7,   KC_8,    KC_9,     KC_0,    KC_VOLU, 
    KC_LCTL, KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,          KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,   KC_F12,  KC_VOLD, 
    KC_LSFT, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_LGUI,        KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_MPRV, KC_MNXT, KC_MPLY, 
                                       MO(3),   KC_SPC,                           KC_SPC,  MO(2) 
  ),
    
  [3] = LAYOUT( /* Reset, other functions if you want */
    QK_BOOT,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                         KC_TRNS, KC_TRNS,                      KC_TRNS,  KC_TRNS 
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MESON:
      if (record->event.pressed) {
        // when keycode MESON is pressed
        SEND_STRING("Meson macro working");
      } else {
        // when keycode MESON is released
      }
      break;
  }
  return true;
}
