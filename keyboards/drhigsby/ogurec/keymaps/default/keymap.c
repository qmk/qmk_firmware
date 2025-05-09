/* Copyright 2021 drhigsby
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

enum layers{
  _BASE,
  _NUM,
  _FN
};

enum combo_events {
  combo_ESC,
  combo_BACK,
  combo_TAB,
  combo_DELETE,
  combo_ENTER,
  combo_LPRN,
  combo_RPRN,
};

const uint16_t PROGMEM esc_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM lprn_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM rprn_combo[] = {KC_COMM, KC_DOT, COMBO_END};


combo_t key_combos[] = {
  [combo_ESC] = COMBO(esc_combo, KC_ESC),
  [combo_BACK] = COMBO(bspc_combo, KC_BSPC),
  [combo_TAB] = COMBO(tab_combo, KC_TAB),
  [combo_DELETE] = COMBO(del_combo, KC_DEL),
  [combo_ENTER] = COMBO(enter_combo, KC_ENT),
  [combo_LPRN] = COMBO(lprn_combo, KC_LPRN),
  [combo_RPRN] = COMBO(rprn_combo, KC_RPRN),
};

#define NUM MO(_NUM)
#define FN MO(_FN)
#define xxx KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_3x12(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, KC_RBRC, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G, FN, KC_QUOT, KC_H, KC_J, KC_K, KC_L, KC_SCLN,
        LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, NUM, KC_SPC, KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH)
  ),

    [_NUM] = LAYOUT_ortho_3x12(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_HOME, KC_PGUP, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_END, KC_PGDN, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,
        KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_LCBR, KC_LT, KC_GT, KC_RCBR, KC_PIPE, KC_BSLS, KC_DQUO, KC_QUOT
  ),

    [_FN] = LAYOUT_ortho_3x12(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx,
        KC_VOLD, KC_VOLU, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_MUTE, KC_MRWD, KC_MFFD, xxx, xxx, xxx
  )

};
