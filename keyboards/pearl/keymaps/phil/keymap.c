/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Layer shorthand
#define COLEMAK 0
#define QWERTY 1
#define WIN 2
#define _FN1 3
#define _FN2 4
#define LIGHT 5

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [COLEMAK] = LAYOUT_all(
      KC_TAB,           KC_Q,    KC_W,    KC_F,    KC_P,   KC_G,   KC_J,   KC_L,   KC_U,    KC_Y,    KC_SCLN,  KC_NO, KC_BSPC,
      LGUI_T(KC_ESC),   KC_A,    KC_R,    KC_S,    KC_T,   KC_D,   KC_H,   KC_N,   KC_E,    KC_I,    KC_O,     KC_QUOT,
      LSFT_T(KC_DEL),   KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  RSFT_T(KC_ENT),
      KC_LCTL,          KC_LGUI, KC_LALT,    LT(_FN1, KC_SPC),    KC_NO,        LT(_FN2, KC_SPC), TG(QWERTY),  TG(WIN)
      ),
  [QWERTY] = LAYOUT_all(
      KC_TRNS,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_NO, KC_TRNS,
      KC_TRNS,   KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_TRNS,
      KC_TRNS,   KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS,
      KC_TRNS,          KC_TRNS, KC_TRNS,    KC_TRNS,    KC_NO,        KC_TRNS, KC_TRNS,  KC_TRNS
      ),
  [WIN] = LAYOUT_all(
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,  KC_TRNS,
      LCTL_T(KC_ESC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_LGUI, KC_LALT, KC_LCTL, KC_TRNS, KC_NO,  KC_TRNS,  KC_TRNS,  KC_TRNS
      ),
  [_FN1] = LAYOUT_all(
      KC_GRV,  KC_MNXT, KC_NO, KC_PIPE, KC_PLUS,  KC_LBRC, KC_RBRC, KC_HOME, KC_UP,   KC_END,  KC_PGUP,   KC_NO,  KC_TRNS,
      KC_TRNS, KC_MPLY, KC_SPC, KC_UNDS, KC_EQUAL, KC_LPRN, KC_RPRN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDOWN, KC_TRNS,
      KC_TRNS, KC_MPRV, KC_NO, KC_BSLS, KC_MINUS, KC_LCBR, KC_RCBR, KC_NO,   KC_MUTE, KC_VOLU, KC_VOLD,   KC_CAPS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,  KC_TRNS,  KC_TRNS,  KC_TRNS
      ),
  [_FN2] = LAYOUT_all(
      KC_TILD,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_NO,  KC_TRNS,
      KC_TRNS,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
      KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CAPS,
      TG(LIGHT), KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,  KC_TRNS,  KC_TRNS,  KC_TRNS
      ),
  [LIGHT] = LAYOUT_all(
      RESET, KC_NO,  BL_ON,   BL_INC,  BL_BRTG, RGB_M_P,  RGB_M_B, RGB_MOD,  RGB_HUI,  RGB_SAI, RGB_VAI, KC_NO,  KC_NO,
      KC_NO, KC_NO,  BL_TOGG, BL_STEP, KC_NO,   RGB_M_SN, RGB_M_K, RGB_TOG,  RGB_HUD,  RGB_SAD, RGB_VAD, KC_NO,
      KC_NO, KC_NO,  BL_OFF,  BL_DEC,  KC_NO,   KC_NO,    KC_NO,   RGB_RMOD, RGB_M_SW, RGB_M_R, RGB_M_G, KC_NO,
      TG(LIGHT), KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO
      ),
};

uint32_t layer_state_set_kb(uint32_t state) {
  if (state & (1<<QWERTY)){
    PORTD &= ~(1 << PD0);
  } else {
    PORTD |= (1 << PD0);
  }

  if (state & (1<<WIN)){
    PORTD &= ~(1 << PD1);
  }
  else{
    PORTD |= (1 << PD1);
  }

  if (state & (1<<LIGHT)){
    PORTD &= ~(1 << PD6);
  }
  else{
    PORTD |= (1 << PD6);
  }
    return state;
}
