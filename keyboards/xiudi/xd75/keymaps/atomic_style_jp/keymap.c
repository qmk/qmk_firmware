/* Copyright 2017 Wunder
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
 *
 */


 // 2019/03/04 takashiski
 // NORTICE
 // This layout is for Japanese Keyboard User.
 // So there are logicalparing symbols and special keycode like a JP_BSLS, JP_HENK, JP_MHEN, JP_YEN.
 // 日本語キーボードとして認識させて使うことが前提なので、記号位置が英語キーボードとは異なります。
 // また、日本語キーボードでないと認識されない特殊なキーコードが含まれています。

#include QMK_KEYBOARD_H


// Layer shorthand
enum LAYER{
  _QW,
  _EASY_QW,
  _CURSOR,
  _RS,
  _LW
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 //qwerty layer(almost use default)
 [_QW] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_INT3,  KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT, KC_DEL,
  KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,  KC_ENT,  KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_INT1, KC_RSFT, KC_UP,   KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, KC_INT5, LT(_LW,KC_TAB), KC_SPC,  LT(_CURSOR,KC_ENT),  LT(_RS,KC_BSPC), KC_INT4, KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
 ),
 //4th row shifted 1u from regular ortholinear.
 [_EASY_QW] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_INT3,  KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT, KC_DEL,
  KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,  KC_ENT,  KC_ENT,
  KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_INT1, KC_UP,   KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, KC_INT5, LT(_LW,KC_TAB), KC_SPC,  LT(_CURSOR,KC_ENT),  LT(_RS,KC_BSPC), KC_INT4, KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
 ),
//LOWER
 [_LW] = LAYOUT(
  KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_PSCR,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, KC_INS ,
  KC_CAPS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, _______, _______, _______,
  KC_LSFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, KC_PGUP, KC_SCRL,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
 ),

//RAISE
 [_RS] = LAYOUT(
   KC_NUM,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
   KC_SCRL, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_PAUS, KC_PSCR,
   KC_CAPS, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, KC_ACL0, KC_ACL2, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, _______, _______, _______,
   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_TOGG, BL_UP,   BL_DOWN,  _______,KC_WH_U, KC_MS_U, KC_WH_D,
   QK_BOOT, DF(_QW), DF(_EASY_QW), _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
	 ),
 [_CURSOR] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_INT3,  KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT, KC_DEL,
  KC_CAPS,  KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_G,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_SCLN, KC_QUOT, KC_BSLS,  KC_ENT,  KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_INT1, KC_RSFT, KC_UP,   KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, KC_INT5, LT(_LW,KC_TAB), KC_SPC,  KC_ENT,  LT(_RS,KC_BSPC), KC_INT4, KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
)

};
