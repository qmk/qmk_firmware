/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3(
    KC_B,              KC_Z,              KC_P,              KC_O,              KC_QUOT,           KC_DOT,            KC_V,              KC_D,              KC_L,              KC_J,
    LGUI_T(KC_A),      LALT_T(KC_U),      LSFT_T(KC_I),      LCTL_T(KC_E),      KC_COMM,           KC_C,              LCTL_T(KC_T),      LSFT_T(KC_S),      LALT_T(KC_R),      LGUI_T(KC_N),
    LT(4, KC_W),     KC_Y,              KC_X,              KC_SLSH,           KC_K,              KC_M,              KC_Q,              KC_G,              KC_H,              KC_F, 
                                          LT(3, KC_BSPC),LT(1, KC_ENT),   LT(2, KC_TAB), LT(6, KC_ESC),   LT(5, KC_SPC),   U_NP
  ),
  [1] = LAYOUT_split_3x5_3(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, U_NA,    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1, U_NA,    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                      U_NA,    U_NA,    U_NA,    KC_ENT,  KC_DEL, KC_DEL
  ),
  [2] = LAYOUT_split_3x5_3(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, U_NA,    U_NU,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NU,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
                      U_NA,    U_NA,    U_NA,    KC_BTN1, KC_BTN3, KC_BTN2
  ),
  [3] = LAYOUT_split_3x5_3(
    RESET,   U_NA,    U_NA,    U_NA,    U_NA,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
    KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, U_NA,    U_NU,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
    U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,
                      U_NA,    U_NA,    U_NA,    KC_MSTP, KC_MPLY, KC_MUTE
  ),
  [4] = LAYOUT_split_3x5_3(
    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
    KC_LGUI, DRAG_SCROLL, KC_LSFT, KC_LCTL, KC_TRNS, KC_TRNS, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI,
    U_RDO,   SNIPER,  U_CPY,   U_CUT,   U_UND,   U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN1, KC_BTN3, KC_BTN2
  ),
  [5] = LAYOUT_split_3x5_3(
    KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,  U_NA,    KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                      KC_DOT,  KC_0,    KC_MINS, U_NA,    U_NA,    U_NA
  ),
  [6] = LAYOUT_split_3x5_3(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS, U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                      KC_LPRN, KC_RPRN, KC_UNDS, U_NA,    U_NA,    U_NA
  ),
  [7] = LAYOUT_split_3x5_3(
    KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, U_NA,    U_NA,    U_NA,    U_NA,    RESET,
    KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA,
                      KC_APP,  KC_SPC,  KC_TAB,  U_NA,    U_NA,    U_NA
  )
};
