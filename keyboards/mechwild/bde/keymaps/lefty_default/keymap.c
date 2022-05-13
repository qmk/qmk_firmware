/* Copyright 2020 Kyle McCreery 
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

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN3_B       LT(3, KC_B)
#define CTL_Z       CTL_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define CTL_M       RCTL_T(KC_M)
#define SFT_ENT     RSFT_T(KC_ENT)
#define WIN_C		LGUI_T(KC_C)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_7,    KC_8,    KC_9,    KC_0,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_4,    KC_5,    KC_6,    SFT_ENT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_ESC,
    KC_1,    KC_2,    KC_3,     	    CTL_Z,   ALT_X,   WIN_C,   KC_V,    FN2_BSPC, FN1_SPC, FN3_B,   ALT_N,   CTL_M,   SFT_ENT
  ),

  [1] = LAYOUT(
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, RESET,   _______,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_F4,   KC_F5,   KC_F6,   KC_TAB,  _______, _______, _______, _______, _______,  KC_COMM, KC_DOT,  KC_SLSH, KC_SCLN, KC_QUOT,
    KC_F1,   KC_F2,   KC_F3,       	    _______, _______, KC_LGUI, _______, KC_DEL,	  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),
	
  [2] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_LABK, KC_RABK, KC_QUES, KC_COLN, KC_DQUO,
    KC_F11,  KC_F12,  _______,          _______, _______, _______, _______, _______,  KC_PSCR, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [3] = LAYOUT(
    RGB_M_G,  RGB_M_T, _______,  RGB_M_P, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  _______,  _______, _______, _______, _______, _______,
    RGB_M_SN, RGB_M_K, RGB_M_X,  RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD, _______,  _______, _______, _______, _______, _______,
    RGB_M_B,  RGB_M_R, RGB_M_SW,          _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______
  )

};
