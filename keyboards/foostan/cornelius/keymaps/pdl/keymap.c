/* Copyright 2021 Daniel Perrett
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
#include "pdl.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
        MY_FESC, _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_BSPC,
        KC_TAB,  _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, MY_SQUO,
        MY_SBSL, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, NUMBRS,  NAVIGN, KC_SPC,   MY_SSPC, NUMBRS,  NAVIGN,  MY_AMNU, FUNCTN,  MY_CENT
    ),
    [_PROXIM] = LAYOUT_wrapper(
        MY_FESC, _________________PROXIM_L1_________________, _________________PROXIM_R1_________________, KC_BSPC,
        KC_TAB,  _________________PROXIM_L2_________________, _________________PROXIM_R2_________________, MY_ASCL,
        MY_SBSL, _________________PROXIM_L3_________________, _________________PROXIM_R3_________________, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, NUMBRS,  NAVIGN, KC_SPC,   MY_SSPC, NUMBRS,  NAVIGN,  MY_AMNU, FUNCTN,  MY_CENT
    ),
    [_NAVIGN] = LAYOUT_wrapper(
        _______, _________________NAVIGN_L1_________________, _______, _______, _______, _______, _______, _______,
        _______, _________________NAVIGN_L2_________________, _______, _______, _______, _______, _______, _______,
        _______, _________________NAVIGN_L3_________________, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_PUNCTN] = LAYOUT_wrapper(
        _______, _______, _______, _______, _______, _______, _________________PUNCTN_R1_________________, _______,
        _______, _______, _______, _______, _______, _______, _________________PUNCTN_R2_________________, _______,
        _______, _______, _______, _______, _______, _______, _________________PUNCTN_R3_________________, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NUMBRS] = LAYOUT_wrapper(
        _______, _________________NUMBRS_L1_________________, _______, _______, _______, _______, _______, _______,
        _______, _________________NUMBRS_L2_________________, _______, _______, _______, _______, _______, _______,
        _______, _________________NUMBRS_L3_________________, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_CODING] = LAYOUT_wrapper(
        _______, _______, _______, _______, _______, _______, _________________CODING_R1_________________, _______,
        _______, _______, _______, _______, _______, _______, _________________CODING_R2_________________, _______,
        _______, _______, _______, _______, _______, _______, _________________CODING_R3_________________, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FUNCTN] = LAYOUT_wrapper(
        _______, _________________FUNCTN_L1_________________, _________________FUNCTN_R1_________________, MY_CAD,
        _______, _________________FUNCTN_L2_________________, _________________FUNCTN_R2_________________, KC_PSCR,
        _______, _________________FUNCTN_L3_________________, _________________FUNCTN_R3_________________, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};
