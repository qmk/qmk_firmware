/* Copyright 2018
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

enum foobar_layers {
  QWERTY,
  FN1,
  FN2,
  FN3,
  FN4,
  FN5
};

#define FN1_SPC  LT(FN1, KC_SPC)
#define FN2_BSC  LT(FN2, KC_BSPC)
#define FN3_C    LT(FN3, KC_C)
#define FN4_V    LT(FN4, KC_V)
#define FN5_B    LT(FN5, KC_B)
#define RALT_N   RALT_T(KC_N)
#define LALT_X   LALT_T(KC_X)
#define LCTL_Z   LCTL_T(KC_Z)
#define RCTL_M   RCTL_T(KC_M)
#define LSFT_ENT LSFT_T(KC_ENT)
#define RGUI_ESC RGUI_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERTY] = LAYOUT_split(
    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    RGUI_ESC,
    LCTL_Z, LALT_X,  FN3_C,   FN4_V,   FN2_BSC, FN1_SPC, FN5_B,   RALT_N,  RCTL_M,  LSFT_ENT
  ),

  [FN1] = LAYOUT_split(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______
  ),

  [FN2] = LAYOUT_split(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, KC_GRV,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [FN3] = LAYOUT_split(
    _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TAB,  _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, KC_SCLN, KC_QUOT,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  [FN4] = LAYOUT_split(
    _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    KC_TAB,  _______, _______, _______, _______, KC_LABK, KC_RABK, KC_QUES, KC_COLN, KC_DQUO,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [FN5] = LAYOUT_split(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
