/* Copyright 2019 kakunpc
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

enum layers{
    BASE,
    COMMAND,
    NUMBER,
    SETTING
};

#define KC_CMD_SP    LT(COMMAND,KC_SPC)
#define KC_CMD_ET    LT(COMMAND,KC_ENTER)
#define KC_NUM_ALT   LT(NUMBER,KC_LALT)
#define KC_NUM_BS    LT(NUMBER,KC_BSPC)
#define KC_SET_CTRL  LT(SETTING,KC_LCTL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x5_3( /* Base */
          KC_Q,  KC_W,  KC_E, KC_R, KC_T,                 KC_Y,  KC_U,  KC_I, KC_O, KC_P,
          KC_A,  KC_S,  KC_D, KC_F, KC_G,                 KC_H,  KC_J,  KC_K, KC_L, KC_SCLN,
          KC_Z,  KC_X,  KC_C, KC_V, KC_B,                 KC_N,  KC_M,  KC_COMMA, KC_DOT, KC_SLASH,
       KC_SET_CTRL,  KC_NUM_ALT,  KC_CMD_SP,                 KC_CMD_ET,  KC_BSPC,  KC_LSFT
  ),
  [COMMAND] = LAYOUT_split_3x5_3( /* Base */
          KC_Q,  KC_W,  KC_E, KC_R, KC_T,                           KC_Y,  KC_U,  KC_I, KC_O, KC_P,
          KC_A,  KC_S,  KC_D, KC_F, KC_G,                           KC_H,  KC_J,  KC_K, KC_L, KC_SCLN,
    LCTL(KC_Z),  LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V), LCTL(KC_B),   KC_N,  KC_M,  KC_COMMA, KC_DOT, KC_SLASH,
                   KC_NO,  KC_NO,  KC_NO,                           KC_NO,  KC_NO,  KC_NO
  ),
  [NUMBER] = LAYOUT_split_3x5_3( /* Base */
          KC_F1,  KC_F2,  KC_F3, KC_F4, KC_F5,                 KC_P7,  KC_P8,  KC_P9, KC_NO, KC_NO,
          KC_F6,  KC_F7,  KC_F8, KC_F9, KC_F10,                KC_P4,  KC_P5,  KC_P6, KC_NO, KC_NO,
          KC_F11, KC_F12, KC_NO, KC_NO, KC_NO,                 KC_P1,  KC_P2,  KC_P3, KC_NO, KC_NO,
                        KC_NO,  KC_NO,  KC_NO,                 KC_P0,  KC_PDOT,  KC_NO
  ),
  [SETTING] = LAYOUT_split_3x5_3( /* Base */
          KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,
          KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,
          KC_NO,  KC_NO,  KC_NO, KC_NO, RGB_MOD,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,
                        KC_NO,  KC_NO,  KC_NO,                 KC_NO,  KC_NO,  KC_NO
  ),
};
