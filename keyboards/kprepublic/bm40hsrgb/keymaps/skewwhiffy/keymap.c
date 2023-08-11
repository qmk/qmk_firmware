/* Copyright 2023 skewwhiffy
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
#include "keymap_uk.h"

// Layer shorthand
enum Layers {
  cm, // colemak
  nbl, // numbers left
  nbr, // numbers right
  syl, // symbols left
  syr, // symbols right
  nal, // navigation left
  nar // navigation right
};

// Layer buttons
#define _Z_SFT SFT_T(UK_Z)
#define _SLSH SFT_T(UK_SLSH)

#define _X_NB LT(nbl, UK_X)
#define _DOT_NB LT(nbr, UK_DOT)
#define __NBL LT(nbl, _______)
#define __NBR LT(nbr, _______)

#define _C_SY LT(syl, UK_C)
#define _COM_SY LT(syr, UK_COMM)
#define __SYL LT(syl, _______)
#define __SYR LT(syr, _______)

#define _V_NAL LT(nal, UK_V)
#define _M_NAR LT(nar, UK_M)
#define __NAL LT(nal, _______)
#define __NAR LT(nar, _______)

// Custom hotkeys
#define _TERM LCTL(UK_QUOT) // Hotkey for terminal
#define _S_TAB S(KC_TAB)
#define _C_LEFT LCTL(KC_LEFT)
#define _C_RGHT LCTL(KC_RGHT)
#define _A_LEFT LALT(KC_LEFT)
#define _A_RGHT LALT(KC_RGHT)
#define _VIM_ESC LCTL(KC_LBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * .-----------------------------------------------------------------------------------------------------.
 * | Q      | W      | F      | P      | G      |     |     | J      | L      | U      | Y      | ;      |
 * |-----------------------------------------------------------------------------------------------------|
 * | A      | R      | S      | T      | D      |     |     | H      | N      | E      | I      | O      |
 * |-----------------------------------------------------------------------------------------------------|
 * | Z      | X      | C      | V      | B      | DEL | DEL | K      | M      | ,      | .      | /      |
 * | SHIFT  | NUMBER | SYMBOL | NAV    |        |     |     |        | NAV    | SYMBOL | FUNC   | SHIFT  |
 * |-----------------------------------------------------------------------------------------------------|
 * | LSHIFT | LCTRL  | LALT   | LGUI   | SPACE  |   ENTER   | BKSPC  | RGUI   | RALT   | RCTRL  | RSHIFT |
 * .-----------------------------------------------------------------------------------------------------.
 */
  [cm] = LAYOUT_planck_mit(
    UK_Q,    UK_W,    UK_F,    UK_P,    UK_G, _______, _______, UK_J,    UK_L,    UK_U,    UK_Y,    UK_SCLN,
    UK_A,    UK_R,    UK_S,    UK_T,    UK_D, _______, _______, UK_H,    UK_N,    UK_E,    UK_I,    UK_O,
    _Z_SFT,  _X_NB,   _C_SY,   _V_NAL,  UK_B, KC_DEL,  KC_DEL,  UK_K,    _M_NAR,  _COM_SY, _DOT_NB, _SLSH,
    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,     KC_ENT,     KC_BSPC, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT
  ),

/* Numbers _NB
 * .-----------------------------------------------------------------------------------------------------------.
 * |        | F7     | F8     | F9     | F10    |        |        |        | 7      | 8      | 9      |        |
 * |-----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F4     | F5     | F6     | F11    |        |        |        | 4      | 5      | 6      |        |
 * |-----------------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        | F1     | F2     | F3     | F12    |        |        | 0      | 1      | 2      | 3      | .      |
 * |-----------------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
  [nbl] = LAYOUT_planck_mit(
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, KC_7,    KC_8,    KC_9,    _______,
    _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______, _______, _______, KC_4,    KC_5,    KC_6,    _______,
    _______, __NBL,   KC_F2,   KC_F3,   KC_F12,  _______, _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_DOT,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
  ),
  [nbr] = LAYOUT_planck_mit(
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, KC_7,    KC_8,    KC_9,    _______,
    _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______, _______, _______, KC_4,    KC_5,    KC_6,    _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______, _______, KC_0,    KC_1,    KC_2,    __NBR,   KC_DOT,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
  ),

/* Symbols _SY
 * .-----------------------------------------------------------------------------------------------------------.
 * | !      | £      | _      | -      | ~      |        |        | \      | {      | }      | /      | #      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | $      | %      | +      | =      |        |        |        | "      | (      | )      | '      | @      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ^      | &      | *      | |      |        |        |        | <      | [      | ]      | >      | `      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
  [syl] = LAYOUT_planck_mit(
    UK_EXLM, UK_PND,  UK_UNDS, UK_MINS, UK_TILD, _______, _______, UK_BSLS, UK_LCBR, UK_RCBR, UK_SLSH, UK_HASH,
    UK_DLR,  UK_PERC, UK_PLUS, UK_EQL,  _______, _______, _______, UK_DQUO, UK_LPRN, UK_RPRN, UK_QUOT, UK_AT,
    UK_CIRC, UK_AMPR, __SYL,   UK_PIPE, _______, _______, _______, UK_LABK, UK_LBRC, UK_RBRC, UK_RABK, UK_GRV,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
  ),
  [syr] = LAYOUT_planck_mit(
    UK_EXLM, UK_PND,  UK_UNDS, UK_MINS, UK_TILD, _______, _______, UK_BSLS, UK_LCBR, UK_RCBR, UK_SLSH, UK_HASH,
    UK_DLR,  UK_PERC, UK_PLUS, UK_EQL,  _______, _______, _______, UK_DQUO, UK_LPRN, UK_RPRN, UK_QUOT, UK_AT,
    UK_CIRC, UK_AMPR, UK_ASTR, UK_PIPE, _______, _______, _______, UK_LABK, UK_LBRC, __SYR,   UK_RABK, UK_GRV,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______
 ),

/*
 * Navigation
 * .----------------------------------------------------------------------------------------------------------------.
 * | Ctrl [ | Ctrl L | Up     | Ctrl R |        | RGB HUE | RGB ON/OFF |        | PtSn   | ScLk   | Pause  | ESC    |
 * +--------+--------+--------+--------+--------+---------+------------+--------+--------+--------+--------+--------|
 * | Tab    | Left   | Down   | Right  |        | RGB SAT |            |        | Insert | Home   | PgUp   | Term   |
 * +--------+--------+--------+--------+--------+---------+------------+--------+--------+--------+--------+--------|
 * | ShTab  | Alt L  |        | Alt R  |        | RGB VAL | RESET      |        | Delete | End    | PgDn   |        |
 * +--------+--------+--------+--------+--------+---------+------------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |     RGB MODE         |        |        |        |        |        |
 * '----------------------------------------------------------------------------------------------------------------'
 */
  [nal] = LAYOUT_planck_mit(
    _VIM_ESC,  _C_LEFT, KC_UP,   _C_RGHT, _______, RGB_HUI, RGB_TOG, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_ESC,
    KC_TAB,    KC_LEFT, KC_DOWN, KC_RGHT, _______, RGB_SAI, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _TERM,
    _S_TAB,    _A_LEFT, _______, __NAL,   _______, RGB_VAI, QK_BOOT, _______, KC_DEL,  KC_END,  KC_PGDN, _______,
    _______,   _______, _______, _______, _______,       RGB_MOD,    _______, _______, _______, _______, _______
  ),
  [nar] = LAYOUT_planck_mit(
    _VIM_ESC,  _C_LEFT, KC_UP,   _C_RGHT, _______, RGB_HUI, RGB_TOG, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_ESC,
    KC_TAB,    KC_LEFT, KC_DOWN, KC_RGHT, _______, RGB_SAI, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _TERM,
    _S_TAB,    _A_LEFT, _______, _A_RGHT, _______, RGB_VAI, QK_BOOT, _______, __NAR,   KC_END,  KC_PGDN, _______,
    _______,   _______, _______, _______, _______,      RGB_MOD,     _______, _______, _______, _______, _______
  ),
};
