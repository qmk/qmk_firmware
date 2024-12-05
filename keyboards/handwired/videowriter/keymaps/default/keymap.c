/* Copyright 2019 DmNosachev
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* 
 * ,---------------------------------------------------------------------------------------.
 * |   ,----------------.  ,-----------------------.  ,--------------.          | up |     |
 * |   |vol- |vol+| mute|  | prev| play| stop| next|  |prsc|scrlk|ins|     |left|down|right|
 * |---------------------------------------------------------------------------------------|
 * | ~`|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  = |   BSp| fn1 |
 * |---------------------------------------------------------------------------------------|
 * |Tab/fn1| Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  | menu|
 * |---------------------------------------------------------------------------------------|
 * |Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  "  | enter ||\ctrl|
 * |---------------------------------------------------------------------------------------'
 * |  Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  <  |  >  |  ?  |   Shift   |
 * `---------------------------------------------------------------------------------'
 *        | Alt  |                     Space                         | Caps  |
 *        `------------------------------------------------------------------'
 */
  [_BASE] = LAYOUT(
		        KC_VOLD, KC_VOLU, KC_MUTE,      KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT,    KC_PSCR, KC_SCRL, KC_INS,      KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,
		KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_PGUP,
		KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,          KC_PGDN,
		KC_LCAP, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,           RCTL_T(KC_BSLS),
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
		  KC_LGUI,                              KC_SPC,                                          KC_RALT),
/* 
 *
 * ,---------------------------------------------------------------------------------------.
 * |   ,----------------.  ,-----------------------.  ,--------------.          |pgup|     |
 * |   |     |    |     |  |     |     |      |sect|  |  |reset|pause|     |home|pgdn| end |
 * |---------------------------------------------------------------------------------------|
 * |Esc| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9 | F10 | F11 | F12 |  del |     |
 * |---------------------------------------------------------------------------------------|
 * |      | mlb | mup | mrb | ms+ |     |     |     |  up |     |     |     |     |  | gui |
 * |---------------------------------------------------------------------------------------|
 * |      |  ml | mdn | mr  | ms- |     |     | left| down|right|     |     |        |     |
 * |---------------------------------------------------------------------------------------'
 * |         |     |     |     |     |     |     |     |     |     |     |           |   
 * `---------------------------------------------------------------------------------'
 *       |      |                                                   |       |
 *       `------------------------------------------------------------------'
 */
  [_FN1] = LAYOUT(
                _______, _______, _______,      _______, _______, _______, _______,    _______,   QK_BOOT,   _______,    _______, _______, _______, _______,
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_HOME,
		_______, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______,          KC_END,
		_______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		  _______,                                _______,                                          _______
  )
};
