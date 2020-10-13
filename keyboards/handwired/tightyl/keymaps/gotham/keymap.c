/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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
#include "gotham.h"

/*
 * The `LAYOUT_tightyl_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_tightyl_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
      ALT_ESC,  K01,  K02,  K03,  K04,  K05,                        K06,  K07,  K08,  K09,  K0A,  KC_BSLS, \
      KC_LSFT,  K11,  K12,  K13,  K14,  K15,                        K16,  K17,  K18,  K19,  K1A,  RSFT_T(KC_QUOT), \
      CTL_EQL,  K21,  K22,  K23,  K24,  K25,                        K26,  K27,  K28,  K29,  K2A,  RCTL_T(KC_MINS), \
          KC_UP, KC_DOWN, SP_LOWR, TAB_CTL, KC_LGUI,         MS_DEL, ENT_SFT, BK_RAIS, KC_LEFT, KC_RIGHT \
    )

#define LAYOUT_tightyl_mods( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
      ALT_ESC,  LALT_T(K01),  K02,  K03,  K04,  K05,                        K06,  K07,  K08,  K09,  RALT_T(K0A),  KC_BSLS, \
      KC_LSFT,  LSFT_T(K11),  K12,  K13,  K14,  K15,                        K16,  K17,  K18,  K19,  RSFT_T(K1A),  RSFT_T(KC_QUOT), \
      CTL_EQL,  LCTL_T(K21),  K22,  K23,  K24,  K25,                        K26,  K27,  K28,  K29,  RCTL_T(K2A),  RCTL_T(KC_MINS), \
                  KC_UP, KC_DOWN, SP_LOWR, TAB_CTL, KC_LGUI,         MS_DEL, ENT_SFT, BK_RAIS, KC_LEFT, KC_RIGHT \
    )
/* Re-pass though to allow templates to be used */
#define LAYOUT_tightyl_base_wrapper(...)       LAYOUT_tightyl_base(__VA_ARGS__)
#define LAYOUT_tightyl_mods_wrapper(...)       LAYOUT_tightyl_mods(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_tightyl_mods_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),
#ifdef ENABLE_LAYOUT_COLEMAK
    [_COLEMAK] = LAYOUT_tightyl_mods_wrapper(
        _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
        _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
        _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
    ),
#endif
#ifdef ENABLE_LAYOUT_COLEMAK_DH
    [_COLEMAK_DH] = LAYOUT_tightyl_mods_wrapper(
        ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
        ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
        ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
    ),
#endif
#ifdef ENABLE_LAYOUT_DVORAK
    [_DVORAK] = LAYOUT_tightyl_mods_wrapper(
        _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
        _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
        _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
    ),
#endif
#ifdef ENABLE_LAYOUT_WORKMAN
    [_WORKMAN] = LAYOUT_tightyl_mods_wrapper(
        _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
        _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
        _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
    ),
#endif
#ifdef ENABLE_LAYOUT_NORMAN
    [_NORMAN] = LAYOUT_tightyl_mods_wrapper(
        _________________NORMAN_L1_________________, _________________NORMAN_R1_________________,
        _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
        _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
    ),
#endif
    [_GAME] = LAYOUT_wrapper(
      GN_ESC,  __________________GAME_L1__________________,                                      _________________QWERTY_R1_________________, _______,
      _______, __________________GAME_L2__________________,                                      _________________QWERTY_R2_________________, _______,
      _______, __________________GAME_L3__________________,                                      _________________QWERTY_R3_________________, _______,
                                KC_NO, KC_LALT, KC_SPC, GN_TAB, MO(_GAMENUM),  KC_EQL, TG_GNAV, KC_ENT, KC_DEL, KC_NO
    ),

    [_GAMENAV] = LAYOUT_wrapper(
      _______, ___________________BLANK___________________,                                     ___________________BLANK___________________, _______,
      _______, ___________________BLANK___________________,                                     _______, _______, KC_UP,   _______, _______, _______,
      _______, ___________________BLANK___________________,                                     _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_GAMENUM] = LAYOUT_wrapper(
      _______, KC_NO,  KC_1, KC_2, KC_3, KC_NO,                                       TG_GAME,  KC_F1,  KC_F2,  KC_F3,  KC_F10, _______,
      _______, KC_0,   KC_4, KC_5, KC_6, KC_NO,                                       KC_NO,    KC_F4,  KC_F5,  KC_F6,  KC_F11, _______,
      _______, KC_NO,  KC_7, KC_8, KC_9, KC_NO,                                       KC_NO,    KC_F7,  KC_F8,  KC_F9,  KC_F12, _______,
                     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______

    ),

    [_LOWER] = LAYOUT_tightyl_base_wrapper(
      _________________LOWER_L1__________________,    _________________LOWER_R1__________________,
      _________________LOWER_L2__________________,    _________________LOWER_R2__________________,
      _________________LOWER_L3__________________,    _________________LOWER_R3__________________
    ),

    [_RAISE] = LAYOUT_tightyl_base_wrapper(
      _________________RAISE_L1__________________,    _________________RAISE_R1__________________,
      _________________RAISE_L2__________________,    _________________RAISE_R2__________________,
      _________________RAISE_L3__________________,    _________________RAISE_R3__________________
    ),

    [_ADJUST] = LAYOUT_tightyl_base_wrapper(
      _________________ADJUST_L1_________________,    _________________ADJUST_R1_________________,
      _________________ADJUST_L2_________________,    _________________ADJUST_R2_________________,
      _________________ADJUST_L3_________________,    _________________ADJUST_R3_________________
    ),

    [_MOUSE] = LAYOUT_tightyl_base_wrapper(
      ___________________KC_NO___________________,    __________________MOUSE1___________________,
      ___________________KC_NO___________________,    __________________MOUSE2___________________,
      ___________________KC_NO___________________,    __________________MOUSE3___________________
    ),
};
// clang-format on

layer_state_t layer_state_set_keymap(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
