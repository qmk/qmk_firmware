/* Copyright 2017 IslandMan93
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

enum custom_keycodes {
  IJ_OMN = SAFE_RANGE // IntelliJ Omnibox
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [cm] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, UK_Q,    UK_W,    UK_F,    UK_P,    UK_G,    _______,                   _______, UK_J,    UK_L,    UK_U,    UK_Y,    UK_SCLN, _______, \
    _______, UK_A,    UK_R,    UK_S,    UK_T,    UK_D,    _______,                   _______, UK_H,    UK_N,    UK_E,    UK_I,    UK_O   , _______, \
    _______, _Z_SFT,  _X_NB,   _C_SY,   _V_NAL,  UK_B,    _______,                   _______, UK_K,    _M_NAR,  _COM_SY, _DOT_NB, _SLSH  , _______, \
    _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_ENT,  _______, _______, KC_DEL,  KC_BSPC, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT, _______  \
  ),

  [nbl] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,                   _______, _______, UK_7,    UK_8,    UK_9,    _______, _______, \
    _______, _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,                   _______, _______, UK_4,    UK_5,    UK_6,    _______, _______, \
    _______, _______, __NBL,   KC_F2,   KC_F3,   KC_F12,  _______,                   _______, UK_0,    UK_1,    UK_2,    UK_3,    UK_DOT,  _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),
  [nbr] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,                   _______, _______, UK_7,    UK_8,    UK_9,    _______, _______, \
    _______, _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,                   _______, _______, UK_4,    UK_5,    UK_6,    _______, _______, \
    _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,                   _______, UK_0,    UK_1,    UK_2,    __NBR,   UK_DOT , _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),

  [syl] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, UK_EXLM, UK_PND,  UK_UNDS, UK_MINS, UK_TILD, _______,                   _______, UK_BSLS, UK_LCBR, UK_RCBR, UK_SLSH, UK_HASH, _______, \
    _______, UK_DLR,  UK_PERC, UK_PLUS, UK_EQL,  _______, _______,                   _______, UK_DQUO, UK_LPRN, UK_RPRN, UK_QUOT, UK_AT  , _______, \
    _______, UK_CIRC, UK_AMPR, __SYL,   UK_PIPE, _______, _______,                   _______, UK_LABK, UK_LBRC, UK_RBRC, UK_RABK, UK_GRV , _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),
  [syr] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, UK_EXLM, UK_PND,  UK_UNDS, UK_MINS, UK_TILD, _______,                   _______, UK_BSLS, UK_LCBR, UK_RCBR, UK_SLSH, UK_HASH, _______, \
    _______, UK_DLR,  UK_PERC, UK_PLUS, UK_EQL,  _______, _______,                   _______, UK_DQUO, UK_LPRN, UK_RPRN, UK_QUOT, UK_AT  , _______, \
    _______, UK_CIRC, UK_AMPR, UK_ASTR, UK_PIPE, _______, _______,                   _______, UK_LABK, UK_LBRC, __SYR,   UK_RABK, UK_GRV , _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),

  [nal] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_ESC,  _C_LEFT, KC_UP  , _C_RGHT, _______, _______,                   _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, \
    _______, KC_TAB,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   _______, _______, KC_INS,  KC_HOME, KC_PGUP, _TERM  , _______, \
    _______, _S_TAB,  _A_LEFT, IJ_OMN,  __NAL,   _______, _______,                   _______, _______, KC_SLCK, KC_END,  KC_PGDN, _______, _______, \
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  ),
  [nar] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_ESC,  _C_LEFT, KC_UP  , _C_RGHT, _______, _______,                   _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, \
    _______, KC_TAB,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   _______, _______, KC_INS,  KC_HOME, KC_PGUP, _TERM  , _______, \
    _______, _S_TAB,  _A_LEFT, IJ_OMN,  _A_RGHT, _______, _______,                   _______, _______, __NAR,   KC_END,  KC_PGDN, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
  )

};
