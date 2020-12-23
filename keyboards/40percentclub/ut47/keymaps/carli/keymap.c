/* Copyright 2018 Carlos Filoteo
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
#include "keymap_italian.h"

#ifdef LED_ENABLE
  #include "protocol/serial.h"
#endif

#define MT_RSFT_ENT MT(MOD_RSFT, KC_ENT)
#define MT_RSFT_TAB MT(MOD_LSFT, KC_TAB)

enum custom_keycodes {
    LED_TOG = SAFE_RANGE,
    LED_CHG
};
enum layers {
  _QWERTY,
  _SHIFT,
  _NUMBER,
  _SYMBOL,
  _ACCENT,
  _SERVICE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_GESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LT(_ACCENT, KC_BSPC),
  MT(MOD_LCTL, KC_DEL), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_PSLS , MT_RSFT_ENT,
  LT(MOD_LSFT, KC_TAB), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,  KC_M,    KC_COMM, KC_DOT, KC_UP, LT(_SHIFT, IT_APOS),
  MO(_SHIFT), KC_LALT, MO(_SERVICE),  KC_LGUI, LT(_SYMBOL, KC_SPC), LT(_ACCENT, KC_SPC), LT(_NUMBER, KC_SPC),  IT_SCLN, KC_LEFT, KC_DOWN,   KC_RGHT
),

[_SHIFT] = LAYOUT(
    S(KC_ESC),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), KC_DEL,  \
    S(KC_LCTL),  S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), IT_QST, S(KC_ENT), \
    S(KC_TAB),    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_BKSL,  IT_PIPE, S(KC_UP),  IT_DQOT,  \
    KC_LSFT, KC_LALT, MO(_SERVICE), KC_LGUI, LT(_NUMBER, KC_SPC), S(KC_SPC), LT(_SYMBOL, KC_SPC),  IT_COLN, S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)  \
),

[_NUMBER] = LAYOUT(
   IT_DEG,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
   MT(MOD_LCTL, KC_DEL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IT_LBRC, IT_RBRC, IT_LESS,  IT_APOS, XXXXXXX, IT_LESS,
   LT(_SYMBOL, KC_TAB), XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, KC_PMNS, IT_EQL, XXXXXXX, XXXXXXX, KC_VOLU, LT(_SYMBOL, KC_DEL),
   _______, _______, _______, _______, _______,     _______,      _______, XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE
 ),

[_SYMBOL] = LAYOUT(
     KC_TILDE, IT_EXLM, IT_AT,IT_SHRP, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN, KC_BSPC,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IT_LCBR, IT_RCBR, IT_MORE, IT_DQOT, XXXXXXX, MT_RSFT_ENT,
     LT(_NUMBER, KC_TAB), XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, IT_UNDS, IT_PLUS, XXXXXXX, XXXXXXX, KC_VOLU, LT(_SYMBOL, KC_DEL),
     _______, _______, _______, _______, _______,     _______,      _______, XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE
 ),

[_ACCENT] = LAYOUT(
  XXXXXXX,  IT_EURO, IT_AT,  IT_EACC, XXXXXXX, XXXXXXX, XXXXXXX, IT_UACC, IT_IACC, IT_OACC, XXXXXXX, XXXXXXX,
  XXXXXXX, IT_AACC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_LSFT, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,  KC_RSFT,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE
),

[_SERVICE] = LAYOUT(
  RESET,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_F9, KC_F10, XXXXXXX,
  XXXXXXX, KC_F11, KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F8, KC_F19,KC_F20, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
};
