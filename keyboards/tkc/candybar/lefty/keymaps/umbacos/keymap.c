/* Copyright 2018 Jack Humbert
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

//Friendly Layer Names
enum qmk_layers {
  _QW, // QWERTY,
  _SH, // SHIFT,
  _NU, // NUMBER,
  _AC, // ACCENT,
  _SE, // SERVICE,
  _SY // SYMBOL
};

enum custom_keycodes {
    BRACKETS = SAFE_RANGE,
    EMOJI1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QW] = LAYOUT(  // QWERTY
      KC_P7, KC_P8, KC_P9, KC_NLCK,                     LT(_SY, KC_ESC), KC_Q, KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     _______,  LT(_SY,KC_BSPC), \
      KC_P4, KC_P5, KC_P6, KC_DEL,                      MT(MOD_LCTL, KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   IT_QUOT,   KC_SFTENT,  \
      KC_P1, KC_P2, KC_P3, KC_PMNS,                     LT(_SH, KC_DEL),      KC_Z,  KC_X,  KC_C,  KC_V,   KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  LT(_SH, KC_UP),   LT(_SH, KC_PSLS), \
    LT(_SE, KC_P0),LT(_SE, KC_P0),IT_DOT,KC_PPLS,       KC_LALT, MO(_NU), KC_LGUI, _______,            LT(_AC, KC_SPC),       _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_SH] = LAYOUT(  // SHIFT
      KC_7, KC_8, KC_9, KC_NLCK,                     S(KC_ESC),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), _______, S(KC_BSPC),  \
      KC_4, KC_5, KC_6, KC_DEL,                      LT(_SY, S(KC_TAB)),  S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), IT_DQUO, S(KC_ENT), \
      KC_1, KC_2, KC_3, KC_PMNS,                     BRACKETS,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_SCLN,  IT_COLN, S(KC_UP), IT_QUES,  \
      KC_0, KC_0,IT_DOT,KC_PPLS,                     S(KC_LCTL), S(KC_LALT), S(KC_LGUI),_______,             LT(_AC, S(KC_SPC)),       _______, _______, S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)  \
  ),

  [_NU] = LAYOUT(
      KC_F7, KC_F8, KC_F9, KC_NLCK,                  IT_LESS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, IT_CIRC, \
      KC_F4, KC_F5, KC_F6, KC_DEL,                   LT(_SY, KC_TAB), KC_PPLS, KC_PMNS, KC_PSLS, KC_PAST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SFTENT,
      KC_F1, KC_F2, KC_F3, KC_PMNS,                  LT(_SY, BRACKETS), IT_EQL,  IT_LBRC, IT_RBRC,   KC_DOT,   XXXXXXX,   XXXXXXX, XXXXXXX, IT_BSLS, IT_PIPE, KC_UP, LT(_SY, KC_DEL),
      KC_F10, KC_F10,IT_DOT,KC_PPLS,                 KC_LCTL, KC_LALT, KC_LGUI, _______,            KC_SPC,       _______, _______, KC_LEFT, KC_DOWN, KC_RGHT \
  ),

  [_SY] = LAYOUT(
      S(KC_F7), S(KC_F8), S(KC_F9), KC_NLCK,          IT_MORE, IT_EXLM, IT_AT,   IT_HASH, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN, _______, IT_PLUS, \
      S(KC_F4), S(KC_F5), S(KC_F6), KC_DEL,           S(KC_TAB), IT_EQL, IT_UNDS, KC_PSLS, KC_PAST,XXXXXXX, IT_RABK, IT_LABK,  IT_LCBR, IT_LCBR, IT_RCBR, KC_SFTENT,
      S(KC_F1), S(KC_F2), S(KC_F3), KC_PMNS,          KC_LSFT, _______, _______, _______, _______, _______, IT_BSLS,  IT_PIPE, IT_UNDS, IT_PLUS, S(KC_UP), IT_QUES, \
      S(KC_F10), S(KC_F10),IT_DOT,KC_PPLS,            S(KC_LCTL), S(KC_LALT), S(KC_LGUI), _______,            S(KC_SPC),       _______, _______, S(KC_LEFT), S(KC_DOWN), S(KC_RGHT) \
  ),

  [_AC] = LAYOUT(
      KC_7, KC_8, KC_9, KC_NLCK,                     _______, IT_EURO, IT_AT, IT_EGRV, _______, _______, _______, IT_UGRV, IT_IGRV, IT_OGRV, _______, _______, _______,  \
      KC_4, KC_5, KC_6, KC_DEL,                      _______, IT_AGRV, IT_SECT, _______, _______, IT_DEG, _______, _______, _______, _______, _______, _______,   \
      KC_1, KC_2, KC_3, KC_PMNS,                     KC_LSFT, _______, _______, IT_CCED, _______, _______, _______, _______, IT_SCLN, IT_COLN, _______, KC_RSFT,   \
      KC_0, KC_0, IT_DOT,KC_PPLS,                    _______, _______, _______, _______, _______, _______, _______, EMOJI1 , _______, _______ \
  ),

  [_SE] = LAYOUT(
      RESET,   KC_VOLU, _______, _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
      _______, KC_MUTE, _______, _______,            _______, KC_SLCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
      _______, KC_VOLD, _______, _______,            _______, _______, _______, KC_CAPS, _______, _______, KC_NLCK, _______, _______, _______, _______, _______,  \
      _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______   \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case BRACKETS:
          if (record->event.pressed) {
              // when keycode is pressed
              SEND_STRING("*("SS_TAP(X_LEFT));
          } else {
              // when keycode is released
          }
          break;
    }
    return true;
};
