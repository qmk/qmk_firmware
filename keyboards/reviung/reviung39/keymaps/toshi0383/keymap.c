/* Copyright 2019 gtips
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

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung39(
   KC_ESC, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,             KC_Y,  KC_U,  KC_I, KC_O,   KC_P, KC_BSPACE,
   KC_TAB, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,             KC_H,  KC_J,  KC_K, KC_L,   SFT_T(KC_SCLN), KC_RGUI,
   KC_SPC, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,             KC_N,  KC_M,  KC_RCTL, KC_DOT, KC_RALT, RGUI(KC_RSFT),
                                       LOWER,  KC_ENT,  RAISE
  ),

  [_LOWER] = LAYOUT_reviung39(
   KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, RCMD(RALT(KC_I)), RCMD(RALT(KC_O)), _______,
   _______, KC_LT, KC_GT, KC_LPRN, KC_RPRN, KC_GRV,       KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_PIPE,
   KC_LALT, _______, _______, ADJUST, KC_EQL, KC_QUES,   KC_UNDS, KC_PLUS, KC_COMM, _______, KC_SLSH, _______,
                                      _______,  _______,  KC_RGUI
  ),

  [_RAISE] = LAYOUT_reviung39(
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  _______,
  _______, KC_COLN, KC_SCLN, KC_DQT, KC_QUOT, KC_BSLS,    KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______,   ADJUST, _______, _______, _______, _______, _______,
                                       KC_LGUI,  _______,  _______
  ),

  [_ADJUST] = LAYOUT_reviung39(
    _______, RCMD(LALT(KC_1)), RCMD(LALT(KC_2)), RCMD(LALT(KC_3)), RCMD(LALT(KC_4)), RCMD(LALT(KC_5)), RCMD(LALT(KC_6)), RCMD(LALT(KC_7)), _______, _______, RCMD(LALT(KC_0)), _______,
    RGB_SAI, RGB_HUI,  RGB_MOD,  _______,   RGB_TOG,    RGB_VAI,   RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, _______,   _______,
    KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU,  QK_BOOT,   _______,  _______,  _______,  _______,  _______,  _______,
                                                   KC_LGUI,  _______,  _______
  ),
};
