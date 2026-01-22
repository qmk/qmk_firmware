/* Copyright 2019 MechMerlin
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
#include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

enum keymap_layers {
  _BASE,
  _QWERTY,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _FN1,
  _FN2,
};

#define SFTSPC  SFT_T(KC_SPC)
#define SFTENT  SFT_T(KC_ENT)
#define C_(k00) LCTL(KC_##k00)
#define S_(k00) LSFT(KC_##k00)
#define A_(k00) LALT(KC_##k00)
#define W_(k00) LGUI(KC_##k00)
#define CC(k00) CTL_T(KC_##k00)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_HOME, \
      KC_TAB,           KC_Y,    KC_R,    KC_O,    KC_U,    KC_COMM, KC_DOT,  KC_BSPC, KC_L,    KC_F,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,  \
      CC(ESC),          KC_D,    KC_S,    KC_A,    KC_I,    KC_G,    KC_J,    KC_E,    KC_H,    KC_T,    KC_K,    KC_QUOT, KC_ENT,           KC_DEL,  \
      KC_LSFT, KC_LSFT, KC_V,    KC_Z,    KC_X,    KC_M,    KC_C,    KC_N,    KC_W,    KC_B,    KC_Q,    KC_SLSH, KC_SCLN,          KC_UP,   MO(_FN2),\
      KC_LCTL, KC_APP,  KC_LWIN,                   SFTSPC,  MO(_FN1),SFTENT,           KC_RCTRL,KC_LALT,                   KC_LEFT, KC_DOWN, KC_RGHT  \
  ),
  [_QWERTY] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_HOME, \
      KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,  \
      C_(ESC),          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_DEL,  \
      KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   MO(_FN2),\
      KC_LCTL, KC_APP,  KC_LWIN,                   SFTSPC,  MO(_FN1),SFTENT,           KC_RCTRL,KC_LALT,                   KC_LEFT, KC_DOWN, KC_RGHT  \
  ),
  [_NAGINATA] = LAYOUT( \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,          NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,    NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,          NG_A,    NG_S,    NG_D,    NG_F,    NG_G,    NG_H,    NG_J,    NG_K,    NG_L,    NG_SCLN, KC_TRNS, KC_TRNS,          KC_TRNS, \
      KC_TRNS, KC_TRNS, NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,    NG_N,    NG_M,    NG_COMM, NG_DOT,  NG_SLSH, KC_TRNS,          KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS,                   NG_SHFT, KC_TRNS, NG_SHFT2,         KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS  \
  ),
  [_FN1] = LAYOUT( \
      KC_NO  , KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO  , KC_NO  , NG_ON  , \
      A_(TAB),          KC_NO  , KC_NO  , KC_NO  , C_(S),   KC_NO  , KC_HOME, C_(X),   C_(V),   C_(Y),   C_(Z),   KC_NO  , KC_NO  , KC_NO  , NG_OFF , \
      KC_NO  ,          A_(TAB), W_(E)  , KC_LEFT, KC_RGHT, KC_NO  , C_(C),   KC_UP,   S_(UP),  KC_PGUP, KC_PGUP, KC_NO  , KC_NO  ,          NG_CLR , \
      KC_NO  , KC_NO  , KC_NO  , KC_NO  , S_(LEFT),S_(RGHT),KC_NO  , KC_END,  KC_DOWN, S_(DOWN),KC_PGDN, KC_PGDN, KC_NO  ,          KC_PGUP, KC_TRNS, \
      KC_NO  , KC_NO  , KC_NO  ,                   KC_NO  , KC_TRNS, KC_NO  ,          KC_NO  , KC_NO  ,                   KC_HOME, KC_PGDN, KC_END   \
  ),
  [_FN2] = LAYOUT( \
      RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO  , KC_NO  , KC_VOLU, \
      KC_NO  ,          RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO  , NGSW_WIN,NG_TAYO, NG_SHOS, KC_NO  , KC_PSCR, KC_SLCK, KC_PAUS, KC_NO  , KC_VOLD, \
      KC_NO  ,          RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO  , NGSW_MAC,NG_KOTI, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          KC_MUTE, \
      KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , NGSW_LNX,NG_MLV,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          KC_NO  , KC_TRNS, \
      KC_NO  , KC_NO  , KC_NO  ,                   KC_NO  , KC_TRNS, KC_NO  ,          KC_NO  , KC_NO  ,                   KC_NO  , KC_NO  , KC_NO    \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 薙刀式
    if (!process_naginata(keycode, record))
      return false;
  // 薙刀式

  // typewriter pairing on jis keyboard
  if (!twpair_on_jis(keycode, record))
    return false;

  return true;
}

void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_J, KC_E}; 
  uint16_t ngoffkeys[] = {KC_I, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
