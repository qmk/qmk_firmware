/* Copyright 2021 Alex Kagno
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

#include "arkag.h"

/*
 Userspace:
 https://github.com/arkag/qmk_firmware/blob/master/users/arkag/arkag.c
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_2u_space_ortho(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    M_PMOD,  M_SMOD,  KC_LALT, MEDIA,   SYMBOL,      KC_SPC,       ARROW,   FUNCT,   XXXXXXX, KC_RALT, QK_LEAD),


  [_SYMBOL] = LAYOUT_2u_space_ortho(
    KC_GRV,  KC_LPRN, KC_RPRN, KC_PLUS, KC_UNDS, KC_CIRC, KC_AMPR, KC_7,    KC_8,    KC_9,    _______, _______,
    KC_LCBR, KC_LBRC, KC_RBRC, KC_EQL,  KC_MINS, KC_ASTR, KC_PIPE, KC_4,    KC_5,    KC_6,    _______, KC_NUM,
    KC_RCBR, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_PDOT, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_PENT,
    M_DASH,  KC_TILD, _______, KEEB,    _______,      _______,     KC_0,    KC_PSLS, KC_PMNS, KC_PPLS, KC_PAST),

  [_MEDIA] = LAYOUT_2u_space_ortho(
    _______, _______, _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______, _______, _______, _______, _______, _______,
    KC_MPLY, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_MUTE, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______),

  [_ARROW] = LAYOUT_2u_space_ortho(
    _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______),

  [_FUNCT] = LAYOUT_2u_space_ortho(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, M_OS   ),

  [_KEEB] = LAYOUT_2u_space_ortho(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, BL_TOGG, BL_STEP, BL_UP,   BL_DOWN, BL_BRTG, _______, _______, _______, _______, _______, _______,
    RGB_M_P, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______,
    QK_BOOT, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______),

};
