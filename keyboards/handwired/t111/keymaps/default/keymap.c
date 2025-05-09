/* Copyright 2020 DmNosachev
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * ,-------------------------------------------------------------------------------------------------------------------------------------.
 * | xxx |     |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | xxx |PrnSc| ScLk|Pause|                         |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  ~  |backspc|  | ins | del |  |NumLk|  /  |  *  |  -  |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * |  tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   enter      | PgUp| PgDn|  |  7  |  8  |  9  | +=  |
 * |--------------------------------------------------------------------------------              |--------------------------------------|
 * |  ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;: |  '" |  |\ |             | home| end |  |  4  |  5  |  6  |  +  |
 * |-------------------------------------------------------------------------------------------------------------------------------------|
 * |   shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /? | ctrl|     shift      |  up | down|  |  1  |  2  |  3  |enter|
 * |-------------------------------------------------------------------------------------------------------------------------------|     |
 * |         | gui |  alt  |                    Space                      | alt |                | left|right|  |     0     |  .  |     |
 * `-------------------------------------------------------------------------------------------------------------------------------------'
*/
    [0] = LAYOUT(
    KC_NO,            KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, KC_NO, KC_PSCR, KC_SCRL, KC_PAUS,
    KC_ESC,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_GRV, KC_BSPC,   KC_INS,  KC_DEL,   KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP, KC_PGDN,  KC_P7,   KC_P8,   KC_P9,   KC_EQL,
    KC_LCTL, KC_A,   KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,        KC_ENT,    KC_HOME, KC_END,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,          KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,        KC_RSFT,   KC_UP,   KC_DOWN,  KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                   KC_LGUI, KC_LALT,                                KC_SPC,                                    KC_RALT,                   KC_LEFT, KC_RGHT,     KC_P0,   KC_PDOT
    )
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
