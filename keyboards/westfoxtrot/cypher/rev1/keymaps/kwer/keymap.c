/* Copyright 2018 westfoxtrot
 * Copyright 2019 kwerdenker
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
#include "keymap_german.h"

#define _DL 0
#define _FN 1
#define _LE 2

#define SPECIAL LT(_FN, DE_CIRC)    //capslock layer switch + stargate key on tap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DL] = LAYOUT_iso (
      KC_ESC,  KC_1,    KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,    KC_0,   DE_SS,   DE_ACUT, KC_BSPC, _______,     KC_NUM,  KC_PSCR,KC_PSLS,KC_PAST,
      KC_TAB,  KC_Q,    KC_W,  KC_E,  KC_R,  KC_T,  DE_Z,  KC_U,  KC_I,  KC_O,    KC_P,   DE_UDIA, DE_PLUS,                       KC_P7,   KC_P8,  KC_P9,  KC_PMNS,
      SPECIAL, KC_A,    KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,    DE_ODIA,DE_ADIA, DE_HASH, KC_ENT,               KC_P4,   KC_P5,  KC_P6,  KC_PPLS,
      KC_LSFT, DE_LABK, DE_Y,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, DE_MINS, KC_RSFT,        KC_UP,         KC_P1,   KC_P2,  KC_P3,  KC_PENT,
      KC_LCTL, _______, KC_LALT,             KC_SPC,                     _______, KC_RALT, TG(_LE),       KC_LEFT, KC_DOWN, KC_RGHT,        KC_P0,  KC_PDOT, KC_NO
  ),

  [_FN] = LAYOUT_iso (
      DE_DEG,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_DEL, _______,      _______, _______, _______, _______,
      _______, _______, KC_UP,   _______, _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______,                        _______, _______, _______, _______,
      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______,               _______, _______, _______, _______,
      _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______,               _______, _______, _______, _______,
      _______, _______, _______,             KC_LGUI,                _______, _______, _______,                         _______, _______, _______,               _______, _______, _______
  ),

  [_LE] = LAYOUT_iso (
      _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______, _______,      _______, _______, _______, QK_BOOT,
      _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______,                        RGB_TOG, RGB_MOD, RGB_RMOD,_______,
      _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______,               RGB_HUI, RGB_SAI, RGB_VAI, _______,
      _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______,               RGB_HUD, RGB_SAD, RGB_VAD, _______,
      _______, _______, _______,             _______,                _______, _______, _______,                         _______, _______, _______,               _______, _______, _______
  ),
};

bool led_update_user(led_t led_state) {
  // Insert custom handling for CAPS_LOCK, NUM_LOCK, SCROLL_LOCK here
      if (led_state.num_lock) {
        gpio_write_pin_high(F4);
        gpio_write_pin_high(F1);
        gpio_write_pin_high(F5);
    } else {
        gpio_write_pin_low(F4);
        gpio_write_pin_low(F1);
        gpio_write_pin_low(F5);
    }
    return false;
}
