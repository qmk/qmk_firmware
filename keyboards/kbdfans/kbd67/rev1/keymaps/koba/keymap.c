/* Copyright 2019 Daisuke Kobayashi
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
#include "keymap_jp.h"

#define RGB_RMO RGB_RMOD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  ^|  \|BS |Del |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  @|  [| Ent |PgUp|
   * |------------------------------------------------------.    |----|
   * |H/Z   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  ]|    |PgDn|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PScr|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt | Space    |Fn | Space  |Alt |Ctrl|  |Lef|Dow|Rig |
   * `------------------------------------------------'  `------------'
   */
[0] = LAYOUT_all(
  KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, JP_CIRC, KC_JYEN, KC_BSPC, KC_DEL,  \
  KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    JP_AT,   JP_LBRC, JP_RBRC,       KC_PGUP, \
  KC_ZKHK,       KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, JP_COLN,       KC_ENT,        KC_PGDN, \
  KC_LSFT, XXXXXXX, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PSCR, \
  KC_LCTL, KC_LGUI, KC_LALT,        KC_SPC,         MO(1),          KC_SPC,          KC_RALT, KC_RCTL, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap Fn Layer
   * ,----------------------------------------------------------------.
   * |Rst| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |   |Ins |
   * |----------------------------------------------------------------|
   * |     |M- |M+ |RGB|H- |H+ |   |   |Prt|SLk|Pau|   |   |     |    |
   * |------------------------------------------------------.    |----|
   * |Caps  |Vo-|Vo+|Mut|S- |S+ |  *|  /|Hom|PUp|   |   |   |    |    |
   * |----------------------------------------------------------------|
   * |        |BL-|BL+|BL |V- |V+ |  +|  -|End|PDn|  _|      |PUp|    |
   * |----------------------------------------------------------------|
   * |    |    |    | Muhenkan |   | Henkan |Kana|Menu|  |Hom|PDn|End |
   * `------------------------------------------------'  `------------'
   */
[1] = LAYOUT_all(
   RESET,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, XXXXXXX,_______,KC_INS,  \
   _______,   RGB_RMO,RGB_MOD,RGB_TOG,RGB_HUD,RGB_HUI,XXXXXXX,XXXXXXX,KC_PSCR,KC_SLCK,KC_PAUS,XXXXXXX,XXXXXXX,XXXXXXX,     _______, \
   KC_CAPS,     KC_VOLD,KC_VOLU,KC_MUTE,RGB_SAD,RGB_SAI,KC_PAST,KC_PSLS,KC_HOME,KC_PGUP,XXXXXXX,XXXXXXX,      KC_PENT,     _______, \
   _______,_______,BL_DEC, BL_INC, BL_TOGG,RGB_VAD,RGB_VAI,KC_PPLS,KC_PMNS,KC_END, KC_PGDN,JP_UNDS,_______,        KC_PGUP,_______, \
   _______,_______,_______,        KC_MHEN,        _______,        KC_HENK,        KC_KANA,KC_APP, _______,KC_HOME,KC_PGDN,KC_END),
};
