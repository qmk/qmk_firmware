/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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


enum layers {
    NOR = 0,
    NAV,
    SYM,
    ETC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NOR] = LAYOUT(
                     KC_NO,   KC_Q, KC_W, KC_D, KC_F, KC_K,                                     KC_J, KC_U, KC_R,    KC_L,   KC_SCLN, KC_BSLS,
                     KC_LSFT, KC_A, KC_S, KC_E, KC_T, KC_G,                                     KC_Y, KC_N, KC_I,    KC_O,   KC_H,    KC_QUOT,
                     KC_NO,   KC_Z, KC_X, KC_C, KC_V, KC_B, MO(NAV), MO(ETC), MO(ETC), MO(NAV), KC_P, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
       LCAG_T(KC_NO), KC_LALT, GUI_T(KC_TAB), LT(SYM,KC_BSPC), CTL_T(KC_ESC), SFT_T(KC_ENT), LT(SYM,KC_SPC), GUI_T(KC_TAB), KC_LALT, RCAG_T(KC_NO)
    ),

    [NAV] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
      KC_TRNS, KC_LSFT, KC_LCTL, KC_LOPT, KC_LCMD, KC_TRNS,                                     KC_VOLU, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [SYM] = LAYOUT(
      KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     KC_EQL,  KC_7,   KC_8,    KC_9, KC_PLUS, KC_TRNS,
      KC_AMPR, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_BSLS,                                     KC_MINS, KC_4,   KC_5,    KC_6, KC_QUOT, KC_TRNS,
      KC_GRV,  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_ASTR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_1,   KC_2,    KC_3, KC_DQUO, KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0,    KC_DOT, KC_TRNS
    ),

    [ETC] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LSFT, KC_LCTL, KC_LOPT, KC_LCMD, KC_TRNS,                                     KC_TRNS, KC_F4,   KC_F5,   KC_F6,   KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_TRNS, KC_TRNS,
                                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    /*
      [__TEMPLATE__] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      ),
    */
};
