/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
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
#include "version.h"
#include "itg.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWE] = LAYOUT_moonlander(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,          _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,         _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,         _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
        MO(MED), KC_LGUI, KC_LALT, MO(MED), MO(SYM),          _______,         _______,          MO(SYM), MO(MED), KC_RALT, LK_QWE,  MO(MED),
                                            KC_SPC,  MO(SYM), KC_LGUI,         MO(MED), KC_DEL,  KC_ENT
  ),

  [OSX] = LAYOUT_moonlander(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,          _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,         _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,         _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
        MO(MED), KC_LCTL, KC_LALT, KC_LGUI, MO(SYM),          KC_KP_0,         KC_PENT,          MO(SYM), KC_RGUI, KC_RALT, KC_RCTL, MO(MED),
                                            KC_SPC,  MO(SYM), KC_LGUI,         MO(MED), KC_DEL,  KC_ENT
  ),

  [SYM] = LAYOUT_moonlander(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        XXXXXXX, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, TG(SYM),           TG(STN), KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        XXXXXXX, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______,           _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PLUS, _______,
        XXXXXXX, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, XXXXXXX,
        XXXXXXX, _______, _______, _______, _______,          RGB_VAI,           RGB_TOG,          _______, KC_DOT,  KC_0,    KC_EQL,  _______,
                                            RGB_HUD, RGB_VAD, RGB_HUI, TOGGLE_LAYER_COLOR,_______, _______
  ),

  [MED] = LAYOUT_moonlander(
      _______, LK_QWE,  LK_OSX,  _______, _______, _______, _______,           KC_SCT1, _______, _______, _______, _______, _______, RESET,
      _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, _______, _______, _______,
                                          _______, _______, _______,           _______, _______, _______
  ),

};

// #ifdef AUDIO_ENABLE
//   float plover_song[][2]     = SONG(PLOVER_SOUND);
//   float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
// #endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      case LK_QWE:
        set_single_persistent_default_layer(QWE);
        return false;
      case LK_OSX:
        set_single_persistent_default_layer(OSX);
        return false;
      case SCREENSHOT:
        tap_code16(C(S(G(KC_4))));
        return false;
    }
  }
  return true;
}
