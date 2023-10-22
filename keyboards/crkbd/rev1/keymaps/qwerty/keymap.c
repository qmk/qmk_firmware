/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define MG(k) LGUI_T(k)
#define MS(k) LSFT_T(k)
#define MA(k) LALT_T(k)
#define MC(k) LCTL_T(k)

/**
 * QWERTY with HomeRows
 **/



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_DEL, MG(KC_A), MA(KC_S),MS(KC_D), MC(KC_F), KC_G,                      KC_H,  MC(KC_J),MS(KC_K), MA(KC_L), MG(KC_SCLN), KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_COMMA,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M, KC_COMM,  KC_DOT,  KC_SLSH,  KC_DOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_GRV,   MO(1),  KC_SPC,       KC_ENT,   MO(2), KC_BSLS
                                      //`--------------------------'  `--------------------------'
  ),
    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_DEL , KC_DQUO, KC_LBRC, S(KC_LBRC), S(KC_9), S(KC_1),               KC_EQL, S(KC_0), S(KC_RBRC), KC_RBRC, KC_QUOTE,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MINUS, KC_EXLM,  KC_AT,  KC_HASH, KC_DLR,  KC_PSLS,                     KC_PAST, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,  KC_UNDS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  KC_SPC,     KC_ENT,   MO(3), KC_PIPE
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX,                    KC_MS_ACCEL0, XXXXXXX, KC_MS_WH_DOWN, KC_MS_WH_UP, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_VOLD, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX,            KC_MS_ACCEL1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MUTE, KC_MPRV, XXXXXXX, XXXXXXX, KC_MNXT, XXXXXXX,                     KC_MS_ACCEL2, XXXXXXX, KC_MPLY, KC_MSTP, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TILD, MO(3),  KC_SPC,     KC_ENT, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),


    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
}
