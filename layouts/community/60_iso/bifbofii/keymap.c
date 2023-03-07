/* Copyright 2023 Christoph Jabs (BifbofII)
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

#include "bifbofii.h"

#define LAYOUT_60_iso_wrapper(...) LAYOUT_60_iso(__VA_ARGS__)
// clang-format off
#define LAYOUT_60_iso_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_60_iso_wrapper( \
      KC_GRV,      ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL, KC_BSPC, \
      KC_TAB,      K01,     K02,     K03,     K04,     K05,     K06,     K07,     K08,     K09,     K0A,     KC_LBRC, KC_RBRC, \
      UNICODE_ESC, K11,     K12,     K13,     K14,     K15,     K16,     K17,     K18,     K19,     K1A,     K1B,     KC_BSLS, KC_ENT, \
      KC_LSFT,     XXXXXXX, K21,     K22,     K23,     K24,     K25,     K26,     K27,     K28,     K29,     K2A,     KC_RSFT, \
      KC_LCTL,     KC_LGUI, KC_LALT,                      FUNC_SPACE,                      KC_RALT, KC_RGUI, KC_RCTL, ADJUST \
  )
// clang-format on
#define LAYOUT_60_iso_base_wrapper(...) LAYOUT_60_iso_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off
    [_QWERTY] = LAYOUT_60_iso_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_COLEMAK] = LAYOUT_60_iso_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DVORAK] = LAYOUT_60_iso_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_GAMING] = LAYOUT_60_iso_wrapper(
        KC_ESC,  ________________NUMBER_LEFT________________,  ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  _________________QWERTY_L1_________________,  _________________QWERTY_R1_________________, KC_LBRC, KC_RBRC,
        KC_CAPS, _________________QWERTY_L2_________________,  _________________QWERTY_R2_________________, KC_BSLS, KC_ENT,
        KC_LSFT, XXXXXXX, _________________QWERTY_L3_________________,  _________________QWERTY_R3_________________, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                        KC_SPC,                         KC_RALT, KC_RGUI, KC_RCTL, ADJUST
    ),

    [_UNICODE] = LAYOUT_60_iso_wrapper(
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______, _______, _______,
        _______, _________________UNICODE_L1________________, _________________UNICODE_R1________________, _______, _______,
        _______, _________________UNICODE_L2________________, _________________UNICODE_R2________________, _______, _______, _______,
        KC_LSFT, XXXXXXX, _________________UNICODE_L3________________, _________________UNICODE_R3________________, KC_RSFT,
        _______, _______, _______,                        _______,                                _______, _______, _______, _______
    ),

    [_FUNC] = LAYOUT_60_iso_wrapper(
        _______, _________________FN_LEFT___________________, _________________FN_RIGHT__________________, KC_F11,  KC_F12,  KC_DEL,
        _______, _________________FUNC_L1___________________, _________________FUNC_R1___________________, _______, _______,
        KC_CAPS, _________________FUNC_L2___________________, _________________FUNC_R2___________________, _______, _______, KC_ENT,
        KC_LSFT, XXXXXXX, _________________FUNC_L3___________________, _________________FUNC_R3___________________, FUNC2,
        _______, _______, _______,                        _______,                                _______, _______, _______, _______
    ),

    [_FUNC2] = LAYOUT_60_iso_wrapper(
        _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT,
        KC_LSFT, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                        _______,                                _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_60_iso_wrapper(
        XXXXXXX, ___________________BLOCK___________________, ___________________BLOCK___________________, RGB_VAD, RGB_VAI, XXXXXXX,
        XXXXXXX, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, XXXXXXX, XXXXXXX,
        XXXXXXX, _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, XXXXXXX, XXXXXXX, RGB_TOG,
        XXXXXXX, XXXXXXX, _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, _______
    ),
    // clang-format on
};
