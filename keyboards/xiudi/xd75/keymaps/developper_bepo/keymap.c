/* Copyright 2017 Quentin Lebastard
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
#include "keymap_bepo.h"

// Layer shorthand
#define _BP 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | $      | "      | {      | }      | (      | )      | VOL-   | MUTE   | VOL+   | +      | -      | /      | *      | =      | %      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | B      | E_ACUT | P      | O      | E_GRAV |        |        |        | ^      | V      | D      | L      | J      | Z      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | ESC    | A      | U      | I      | E      | ,      | HOME   |        | END    | C      | T      | S      | R      | N      | M      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | W      | Y      | X      | .      | K      | PAGE UP|        | PAGE D | ?      | Q      | G      | H      | F      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | ALT    |        | _      |ENTER/FN| DEL    |        | BACKSP |SPACE/FN| _      | ALT    | ALT    | RGUI   | LCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_BP] = LAYOUT_ortho_5x15( /* BepoDev */
  BP_DLR,    BP_DQUO,  BP_LCBR,    BP_RCBR, BP_LPRN, BP_RPRN,        KC_VOLD, KC_MUTE, KC_VOLU,   BP_PLUS,         BP_MINS, BP_SLSH, BP_ASTR,  BP_EQL,  BP_PERC,
  KC_TAB,    BP_B,     BP_EACU,    BP_P,    BP_O,    BP_EGRV,        KC_KP_7, KC_KP_8, KC_KP_9,   BP_DCIR,         BP_V,    BP_D,    BP_L,     BP_J,    BP_Z,
  KC_ESC,    BP_A,     BP_U,       BP_I,    BP_E,    BP_COMM,        KC_HOME, KC_KP_5, KC_END,    BP_C,            BP_T,    BP_S,    BP_R,     BP_N,    BP_M,
  KC_LSFT,   BP_W,     BP_Y,       BP_X,    BP_DOT,  BP_K,           KC_PGUP, KC_END,  KC_PGDOWN, BP_QUOT,         BP_Q,    BP_G,    BP_H,     BP_F,    KC_RSFT,
  KC_LCTL,   KC_LGUI, KC_RALT,     KC_LGUI, BP_UNDS, LT(_FN,KC_ENT), KC_DEL,  KC_KP_0, KC_BSPC,   LT(_FN,KC_SPC),  BP_UNDS, KC_RALT, KC_RALT,  KC_RGUI, KC_LCTL
 ),


/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | PREV   | PAUSE  | NEXT   | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | 1      | 2      | 3      | 4      | 5      |        |        |        | 6      | 7      | 8      | 9      | 0      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | |      | \      | [      | ]      | &      |        |        |        |        | LEFT   | DOWN   | UP     | RIGHT  |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        | <      | >      | @      |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | _      | MO(_FN)|        |        |        |        | MO(_FN)| _      |        |        |        | QK_BOOT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */


 [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
  KC_F1,   KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,          KC_MPRV, KC_MPLY, KC_MNXT, KC_F7,          KC_F8,      KC_F9,       KC_F10,      KC_F11,     KC_F12,
  _______, S(BP_DQUO), S(BP_LDAQ), S(BP_RDAQ), S(BP_LPRN), S(BP_RPRN),     _______, _______, _______, S(BP_AT),       S(BP_PLUS), S(BP_MINS), S(BP_SLSH), S(BP_ASTR), S(BP_EQL),
  _______, RALT(BP_B), BP_BSLS,    BP_LBRC,    BP_RBRC,    RALT(BP_P),     _______, _______, _______, _______,        KC_LEFT,    KC_DOWN,     KC_UP  ,     KC_RGHT,    _______,
  _______, BP_BSLS,    _______,    _______,    _______,    _______,        _______, _______, _______, _______,        BP_LABK,    BP_RABK,     BP_AT  ,     _______,    _______,
  _______, _______,    _______,    _______,    _______,    LT(_FN,KC_ENT), _______, _______, _______, LT(_FN,KC_SPC), _______,    _______,     _______,     _______,    QK_BOOT
 )

};
