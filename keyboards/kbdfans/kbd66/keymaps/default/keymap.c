/* Copyright 2018 Alex Peters
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

enum layer_names {
    _L0,
    _L1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0
     * ,-----------------------------------------------------------. ,---.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  `| BS| |INS|
     * |-----------------------------------------------------------| |---|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |DEL|
     * |-----------------------------------------------------------| `---'
     * |Cap  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Enter  |
     * |-------------------------------------------------------------.
     * |Shft|  `|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shft| Fn| UP|
     * |-----------------------------------------------------------------.
     * |Ctl |OS  |Alt |         Space          | Alt| Fn| Ctl|LFT|DWN|RIG|
     * `-----------------------------------------------------------------'
     */
    [_L0] = LAYOUT_all(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSPC, KC_INS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_L1), KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,           KC_SPC,                    KC_RALT, MO(_L1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Layer 1
     * ,-----------------------------------------------------------. ,---.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |   | |HOM|
     * |-----------------------------------------------------------| |---|
     * |     |   |   |   |   |   |   |   |   |   |PSc|VDn|VUp| Mute| |END|
     * |-----------------------------------------------------------| `---'
     * |Reset |   |   |   |   |   |   |PRV|PLY|NXT|STP|   |        |
     * |-------------------------------------------------------------.
     * |    |   |   |   |   |   |   |   |   |BLB|BLC|Slp|    |   |PUp|
     * |-----------------------------------------------------------------.
     * |    |    |    |                        |    |   |    |   |PDn|SLk|
     * `-----------------------------------------------------------------'
     */
    [_L1] = LAYOUT_all(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_VOLD, KC_VOLU, KC_MUTE,          KC_END,
        QK_BOOT, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_BRTG, BL_STEP, KC_SLEP, _______, _______, KC_PGUP,
        _______, _______, _______,                   _______,          _______,                   _______, _______, _______, _______, KC_PGDN, KC_SCRL
    )

};
