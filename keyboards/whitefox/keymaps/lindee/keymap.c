/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

#define PTT MT(MOD_RALT, KC_ESC)

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---------------------------------------------------------------.
     * |PTT|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|Os1|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|Os2|
     * |---------------------------------------------------------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |Os3|
     * |---------------------------------------------------------------|
     * |Shif|   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |Rsh|
     * |---------------------------------------------------------------|
     * |Ctrl| L1 |Alt |         Space         |Alt |Gui |  |Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [0] = LAYOUT( \
          PTT , KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, OSL(1), \
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,        OSL(2),\
        KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NUHS, KC_ENT,        OSL(3),\
        KC_LSPO,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSPC,  KC_UP,       KC_RSFT,\
        KC_LCTL,  MO(1),KC_LALT,               KC_SPC,       KC_RALT,KC_RGUI,_______,/*dead space*/     KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    /* Layer 1: Numpad Layer
       * ,---------------------------------------------------------------.
       * |Num| P/| P*| P-|   |   |   |   |   |   |   |   |   |   |   |   |
       * |---------------------------------------------------------------|
       * |     | P7| P8| P9| P+|   |   |   |   |   |   |   |   |  Del|   |
       * |---------------------------------------------------------------|
       * |      | P4| P5| P6| P+|   |   |   |   |   |   |   |        |   |
       * |---------------------------------------------------------------|
       * |  Fn1|  | P1| P2| P3| P.|   |   |   |   |   |   |      |   |   |
       * |---------------------------------------------------------------|
       * |LGui|    |  P0|         PEnter   |    |    |    |  |   |   |   |
       * `---------------------------------------------------------------'
       */
    [1] = LAYOUT( \
        KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
        _______,  KC_P7,  KC_P8,  KC_P9,KC_PPLS,_______,_______,_______,_______,_______,_______,_______,_______, KC_DEL,        _______,\
        _______,  KC_P4,  KC_P5,  KC_P6,KC_PPLS,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,\
          MO(2),_______,  KC_P1,  KC_P2,  KC_P3,KC_PDOT,_______,_______,_______,_______,_______,_______,_______,_______,        _______,\
        KC_LGUI,_______,  KC_P0,                KC_PENT,        _______,_______,_______,  /*dead space*/_______,_______,_______  \
    ),
    /* Layer 2: Function Layer
     * ,---------------------------------------------------------------.
     * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |   |   |
     * |---------------------------------------------------------------|
     * | Stop|Prv|PlP|Nxt|   |   |   |   |   |   |   |   |   |  Ins|   |
     * |---------------------------------------------------------------|
     * |      |Mut|VlD|VlU|   |   |   |   |   |   |   |   |        |   |
     * |---------------------------------------------------------------|
     * |    |   |   |   |   |   |   |   |   |   |   |   |      |PgU|   |
     * |---------------------------------------------------------------|
     * |    |    |    |                  |    |    |    |  |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
    [2] = LAYOUT( \
        _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,_______,_______,\
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, KC_INS,     _______,\
        _______,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,\
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PGUP,     _______,\
        _______,_______,_______,               _______,          _______,_______,_______, /*dead space*/KC_HOME,KC_PGDN,KC_END  \
    ),
};

const uint16_t fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_MOMENTARY(2),

};
