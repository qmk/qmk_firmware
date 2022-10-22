/*
Copyright 2017 Lukmanul Hakim <lukmanulhakim14@gmail.com>

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

/* NOTE : This is compatible to TrueFox Layout only */

#include QMK_KEYBOARD_H

// Fillers to make layering more clear
#define ___T___ KC_TRNS

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,----------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|Pscr|
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|Del |
     * |----------------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgUp|
     * |----------------------------------------------------------------|
     * |Shif|   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgDn|
     * |----------------------------------------------------------------|
     * |Alt|Fn0 |Gui |         Space    |Gui |Alt |     |  |Lef|Dow|Rght|
     * `----------------------------------------------------------------'
     */
    [0] = LAYOUT( \
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, KC_PSCR,\
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,     KC_DEL, \
        KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,      KC_PGUP,\
        KC_LSFT,XXXXXXX,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,     KC_UP,  KC_PGDN,\
        KC_LALT,MO(1), KC_LGUI,               KC_SPC,           KC_RGUI,KC_RALT, XXXXXXX,     KC_LEFT,KC_DOWN,KC_RGHT \
    ),
    [1] = LAYOUT( \
        _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,_______,_______,\
        _______,KC_MPRV,KC_MNXT,KC_VOLU,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______ ,     BL_TOGG ,\
        _______,KC_MPLY,KC_MSTP,KC_VOLD,_______,_______,_______,_______,_______,_______,_______,_______,_______,QK_BOOT,   BL_INC,\
        _______,_______,_______,KC_MUTE,_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,BL_DEC,\
        _______,_______,_______,               _______,          _______,_______,_______,     KC_HOME,_______,KC_END  \
    ),
};
