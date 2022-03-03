/* Copyright 2022 Christoph Jabs (BifbofII)
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

#define LAYOUT_ortho_4x12_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)
// clang-format off
#define LAYOUT_ortho_4x12_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ortho_4x12_wrapper( \
      KC_TAB,      K01,     K02,     K03,     K04,   K05,        K06,        K07,   K08,     K09,     K0A,     KC_BSPC, \
      UNICODE_ESC, K11,     K12,     K13,     K14,   K15,        K16,        K17,   K18,     K19,     K1A,     K1B, \
      KC_LSFT,     K21,     K22,     K23,     K24,   K25,        K26,        K27,   K28,     K29,     K2A,     SFT_ENT, \
      KC_LCTL,     KC_LGUI, XXXXXXX, KC_LALT, LOWER, FUNC_SPACE, FUNC_SPACE, RAISE, KC_RALT, KC_RGUI, KC_RCTL, XXXXXXX \
  )
// clang-format on
#define LAYOUT_ortho_4x12_base_wrapper(...) LAYOUT_ortho_4x12_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off
    [_QWERTY] = LAYOUT_ortho_4x12_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_COLEMAK] = LAYOUT_ortho_4x12_base_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),

    [_DVORAK] = LAYOUT_ortho_4x12_base_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),

    [_UNICODE] = LAYOUT_ortho_4x12_wrapper(
        _______, _________________UNICODE_L1________________, _________________UNICODE_R1________________, _______,
        _______, _________________UNICODE_L2________________, _________________UNICODE_R2________________, _______,
        _______, _________________UNICODE_L3________________, _________________UNICODE_R3________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    ),

    [_FUNC] = LAYOUT_ortho_4x12_wrapper(
        _______, _________________FUNC_L1___________________, _________________FUNC_R1___________________, KC_DEL,
        KC_CAPS, _________________FUNC_L2___________________, _________________FUNC_R2___________________, _______,
        _______, _________________FUNC_L3___________________, _________________FUNC_R3___________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    ),

    [_LOWER] = LAYOUT_ortho_4x12_wrapper(
        KC_TILD, _________________LOWER_L1__________________, _________________LOWER_R1__________________, _______,
        _______, _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_PIPE,
        _______, _________________LOWER_L3__________________, _________________LOWER_R3__________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    ),

    [_RAISE] = LAYOUT_ortho_4x12_wrapper(
        KC_GRV,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, _______,
        _______, _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, _______,
        _______, ___________________BLANK___________________, ___________________BLANK___________________, _______
    ),

    [_ADJUST] = LAYOUT_ortho_4x12_wrapper(
        XXXXXXX, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, XXXXXXX,
        XXXXXXX, _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, XXXXXXX,
        XXXXXXX, _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, XXXXXXX,
        XXXXXXX, ___________________BLOCK___________________, ___________________BLOCK___________________, XXXXXXX
    ),
    // clang-format on
};
