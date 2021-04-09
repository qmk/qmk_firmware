/* Copyright 2018 wanleg
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
#include "wanleg.h"


#define LAYOUT_kbd6x_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
	 KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSPC, KC_DEL, \
     KC_TAB, 	K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, KC_LBRC, KC_RBRC, KC_BSLS, \
     KC_CAPS, 	K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, KC_QUOT, KC_ENT, \
     KC_LSFT, 	K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, KC_LSFT, FUNCTION, \
     KC_LCTL, KC_LGUI, KC_LALT,				LT(gDIR,KC_SPC),			KC_RALT, KC_RGUI, KC_RCTL \
  )
#define LAYOUT_kbd6x_base_wrapper(...)       LAYOUT_kbd6x_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[gGK] = LAYOUT_kbd6x_base_wrapper(
  _______________Gherkin_Row_0_______________,
  _______________Gherkin_Row_1_______________,
  _______________Gherkin_Row_2_______________
),

[gNUM] = LAYOUT_kbd6x_base_wrapper(
  _______________Gherkin_NUM_0_______________,
  _______________Gherkin_NUM_1_______________,
  _______________Gherkin_NUM_2_______________
),

[gDIR] = LAYOUT_kbd6x_base_wrapper(
  _______________Gherkin_DIR_0_______________,
  _______________Gherkin_DIR_1_______________,
  _______________Gherkin_DIR_2_______________
),

[gETC] = LAYOUT_kbd6x_base_wrapper(
  _______________Gherkin_ETC_0_______________,
  _______________Gherkin_ETC_1_______________,
  _______________Gherkin_ETC_2_______________
),

[_FN] = LAYOUT_kbd6x_base_wrapper(
  _______________Gherkin_FN_0________________,
  _______________Gherkin_FN_1________________,
  _______________Gherkin_FN_2________________
),

//mac layout
[_QW] = LAYOUT_wrapper(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(ONE),
	  KC_LCTL, MO(ONE), KC_LGUI,                   KC_SPACE,                   KC_RGUI, KC_RALT, KC_RCTL
      ),

[ONE] = LAYOUT_wrapper(
      KC_GRV,  _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, RESET,
      _______, BL_BRTG, BL_DEC,  BL_INC,  BL_TOGG, BL_STEP,  BL_ON,   KC_PGUP, KC_HOME, _______, _______, _______, _______, _______,
      _______, RGB_M_B, RGB_VAD, RGB_VAI, RGB_TOG, RGB_MOD,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,
      _______, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, _______,  _______, KC_PGDN, KC_END,  _______, gGHERKIN,_______, _______,
	    _______, _______, _______,                   _______,                    _______, _______, _______
      ),
};
