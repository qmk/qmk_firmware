/* Copyright 2020-2021 koshinoya
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

enum layer_number {
    _BASE = 0,
    _FN1,
    _FN2
};

// Aliases
#define KC_SPFN1  LT(_FN1,KC_SPC)
#define KC_LCTAB  LCTL_T(KC_TAB)
#define KC_RSFSL  RSFT_T(KC_SLSH)
#define KC_RSFSP  RSFT_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_all(
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_MINS,  KC_BSPC,
        KC_LCTAB, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFSL,
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPFN1,           KC_SPFN1, KC_RSFSP,           KC_RALT,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT
    ),
    [_FN1] = LAYOUT_all(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
        KC_TRNS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,  KC_EQL,
        KC_TRNS,  KC_F12,   KC_APP,   MO(_FN2), KC_NO,    KC_NO,    KC_LBRC,  KC_RBRC,  KC_QUOT,  KC_TRNS,  KC_TRNS,  KC_BSLS,  KC_BSLS,
        KC_INS,   KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END
    ),
    [_FN2] = LAYOUT_all(
        KC_NO,    UG_TOGG,  UG_HUEU,  UG_SATU,  UG_VALU,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_PSCR,  KC_SCRL,  KC_PAUS, KC_NO,
        KC_CAPS,  UG_NEXT,  UG_HUED,  UG_SATD,  UG_VALD,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,
        KC_TRNS,  KC_NO,    KC_NO,    KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,
        KC_LCTL,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,            KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
    )
};
