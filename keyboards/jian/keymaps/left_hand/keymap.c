 /* Copyright 2020 KGOH
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

enum jian_layers {
    _DFLT_L,
    _DFLT_R,
    _RAIS_L,
    _RAIS_R,
    _LOWR_L,
    _LOWR_R,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DFLT_L] = LAYOUT_symmetric_left(
  KC_LSFT, LGUI_T(KC_GRV), KC_Q, KC_W, KC_E,                 KC_R,                KC_T,
           KC_LCTL,        KC_A, KC_S, KC_D,                 KC_F,                KC_G,
           KC_LALT,        KC_Z, KC_X, KC_C,                 KC_V,                KC_B,
                                       LT(_RAIS_L, KC_BSPC), LT(_DFLT_R, KC_SPC), LT(_LOWR_L, KC_ENT)
),
[_DFLT_R] = LAYOUT_symmetric_right(
  KC_Y,                KC_U,    KC_I,               KC_O,    KC_P,    KC_LBRC, KC_RBRC,
  KC_H,                KC_J,    KC_K,               KC_L,    KC_SCLN, KC_QUOT,
  KC_N,                KC_M,    KC_COMM,            KC_DOT,  KC_SLSH, KC_BSLS,
  LT(_LOWR_R, KC_ESC), _______, LT(_RAIS_R, KC_DEL)
),
[_RAIS_L] = LAYOUT_symmetric_left(
  _______, LGUI_T(KC_CAPS), KC_SCRL, KC_HOME, KC_PSCR, KC_PGUP,              KC_VOLU,
           LCTL_T(KC_APP),  KC_INS,  KC_LEFT, KC_UP,   KC_RGHT,              KC_MUTE,
           _______,         KC_PAUS, KC_END,  KC_DOWN, KC_PGDN,              KC_VOLD,
                                              _______, LT(_RAIS_R, KC_TAB) , LT(_ADJUST, KC_ESC)
),
[_RAIS_R] = LAYOUT_symmetric_left(
  KC_RSFT, KC_RGUI, XXXXXXX, KC_F7, KC_F8,               KC_F9,   KC_F10,
           KC_RCTL, XXXXXXX, KC_F4, KC_F5,               KC_F6,   KC_F11,
           KC_LALT, XXXXXXX, KC_F1, KC_F2,               KC_F3,   KC_F12,
                                    LT(_ADJUST, KC_DEL), _______, _______
),
[_LOWR_L] = LAYOUT_symmetric_left(
  _______, _______, XXXXXXX, KC_7, KC_8,                KC_9,                KC_0,
           _______, KC_GRV,  KC_4, KC_5,                KC_6,                KC_MINS,
           _______, KC_0,    KC_1, KC_2,                KC_3,                KC_EQL,
                                   LT(_ADJUST, KC_DEL), LT(_LOWR_R, KC_TAB), _______
),
[_LOWR_R] = LAYOUT_symmetric_left(
 _______, _______, XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
          _______, KC_TILD, KC_DLR,  KC_PERC, KC_CIRC, KC_UNDS,
          _______, KC_LPRN, KC_EXLM, KC_AT,   KC_HASH, KC_PLUS,
                                     _______, _______, LT(_ADJUST, KC_ESC)
),
[_ADJUST] = LAYOUT_symmetric_left(
  QK_BOOT, DB_TOGG, XXXXXXX, BL_UP,   RGB_VAI, RGB_HUD, RGB_HUI,
           XXXXXXX, XXXXXXX, BL_DOWN, RGB_VAD, RGB_SAD, RGB_SAI,
           XXXXXXX, BL_BRTG, BL_TOGG, RGB_TOG, RGB_RMOD,RGB_MOD,
                                      _______, _______, _______
)
};
