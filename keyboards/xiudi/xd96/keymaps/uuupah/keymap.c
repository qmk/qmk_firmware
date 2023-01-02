/* Copyright 2020 Jonathan Souter 
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

#define LT_ENT2 LT(2,KC_ENT)

#ifdef RGBLIGHT_ENABLE
void matrix_init_user() {
  rgblight_disable();
}
#endif

enum custom_keycodes {
  ZEROZER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_all(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CALC, KC_PSCR, KC_HOME, KC_END,  KC_PGUP, KC_PGDN,
	  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  KC_NUM,  _______, KC_PMNS, KC_PSLS,
	  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_P7,   KC_P8,   KC_P9,   KC_PAST,
	  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, _______, LT_ENT2,          KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
	  KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),            KC_P1,   KC_P2,   KC_P3,   KC_EQL,
	  KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,          KC_P0,   ZEROZER, KC_PDOT, KC_PENT
  ),

  [1] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, QK_BOOT, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	  _______, KC_MPLY, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   KC_PSCR, _______,          _______, _______, _______, _______,
	  _______, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_RGHT, _______, _______,          _______, _______, _______, _______,
	  _______, _______, KC_VOLD, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOWN, _______, _______,          _______, _______, _______, _______,
	  _______, _______, _______,                            _______,                            _______, _______, _______, _______,          _______, _______, _______, _______
  ),
  
  [2] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______, _______,          _______, _______, _______, _______,
	  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, _______,          _______, _______, _______, _______,
	  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, _______, _______,          _______, _______, _______, _______,
	  _______, _______, _______,                            _______,                            _______, _______, _______, _______,          _______, _______, _______, _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ZEROZER:
      if (record->event.pressed) {
        SEND_STRING("00");
      } else {
      }
      break;
  }
  return true;
}
