/* Copyright 2019 mechmerlin
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

#define MT_RSFT_ENT MT(MOD_RSFT, KC_ENT)
#define MT_RSFT_TAB MT(MOD_RCTL, KC_TAB)

//Friendly Layer Names
enum prototype30_layers {
  _QWERTY,
  _SHIFT,
  _NUMBER,
  _ACCENT,
  _SERVICE,
  _SYMBOL
};

enum custom_keycodes {
    DUMP = SAFE_RANGE,
};

#define IT_PTVG 0x

keymap_config_t keymap_config;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  MT_RSFT_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   MT_RSFT_ENT,
  LT(_SHIFT, IT_APOS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,  KC_M, KC_COMM, LT(_SHIFT, KC_UP), LT(_SHIFT, KC_PSLS),
  MT(MOD_RCTL, 0x64), KC_LALT, KC_LGUI, LT(_NUMBER, KC_DEL), LT(_ACCENT, KC_SPC), KC_DOT, KC_LEFT, KC_DOWN, KC_RGHT
),
[_SHIFT] = LAYOUT(
    S(KC_ESC),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), KC_DEL,
    S(KC_TAB),  S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), S(KC_ENT),
    IT_DQOT,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_SCLN,  S(KC_UP), IT_QST,
    S(KC_LCTL), S(KC_LALT), S(KC_LGUI), LT(_NUMBER, IT_COLN), LT(_ACCENT, KC_SPC), IT_COLN, S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)
),
[_NUMBER] = LAYOUT(
  IT_DEG,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  _______, KC_PPLS, KC_PMNS, KC_PSLS, KC_PAST, IT_MORE, IT_LESS, IT_EQL,  IT_LBRC, IT_RBRC, MT_RSFT_ENT,
  LT(_SYMBOL,IT_DQOT), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   IT_SCLN,  IT_COLN,  LT(_SYMBOL,IT_DQOT),
  KC_LCTL, KC_LALT, KC_LGUI,  _______,  LT(_SERVICE, KC_DEL),             KC_DOT, KC_PGUP, KC_PGDN, KC_END
),
[_SYMBOL] = LAYOUT(
    KC_ESC, IT_EXLM, IT_AT,   IT_SHRP, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN, IT_COLN,
    S(KC_TAB), KC_PPLS, IT_UNDS, KC_PSLS, KC_PAST,IT_MORE, IT_LESS,  IT_LCBR, IT_LCBR, IT_RCBR, MT_RSFT_ENT,
    IT_DQOT,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_BKSL,  IT_PIPE, IT_QST,
    S(KC_LCTL), S(KC_LALT), S(KC_LGUI), LT(_ACCENT, KC_DEL), LT(_NUMBER, KC_SPC), S(KC_LEFT), S(KC_UP), S(KC_DOWN), S(KC_RGHT)
),
[_ACCENT] = LAYOUT(
    _______, IT_EURO, _______, IT_EACC, _______, _______, _______, IT_UACC, IT_IACC, IT_OACC, _______, _______,
    _______, IT_AACC, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
    _______, _______,_______, LT(_SERVICE, KC_DEL), _______,           _______, KC_VOLU, KC_VOLD, KC_MUTE
),
[_SERVICE] = LAYOUT(
    RESET,   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______,  _______, _______, _______, _______, _______, _______,_______,_______, KC_F12,
    _______,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_VOLU, _______,
    DUMP, _______,_______, _______,  _______, _______, KC_VOLU, KC_VOLD, KC_MUTE
)

};
