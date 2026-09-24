/*
/ Copyright 2022 quarkeys
/ This program is free software: you can redistribute it and/or modify
/ it under the terms of the GNU General Public License as published by
/ the Free Software Foundation, either version 2 of the License, or
/ (at your option) any later version.
/ This program is distributed in the hope that it will be useful,
/ but WITHOUT ANY WARRANTY; without even the implied warranty of
/ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/ GNU General Public License for more details.
/ You should have received a copy of the GNU General Public License
/ along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* [0]
     * ,---------------------------------------------------------------------------------------------------------------.
     * | Esc  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  -   |  +   | Back |  ~   |  Del |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab     |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |  {   |  }   |   \      | PgUp |
     * |---------+------+------+------+------+------+------+------+------+------+------+------+------+----------+------|
     * | Capslock   |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |  "   |  ~   | Enter | PgDn |
     * |------------+------+------+------+------+------|------+------+------+------+------+------+------+-------+------|
     * | SHIFT  |  \   |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   |   Shift   |  Fn  |  Up  |
     * |--------+------+------+------+------+------+------+------+------+------+------+------+-----------+------+------|
     * | Ctrl   |  Win   |  ALT   |                  SPACE                   | ALT  | Win  | Ctrl | Left | Down | Rght |
     * `--------+--------+--------+------------------------------------------+------+------+------+------+------+------'
     */
    [0] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_TILD, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_GRV,  KC_ENT,           KC_PGDN,
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   MO(1),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    MO(2),   MO(3),   KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),

    /* [1]
     * ,---------------------------------------------------------------------------------------------------------------.
     * |Reset |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  | Back |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |         | PgUp | Home |  Up  | End  | Del  |  \   |  7   |  8   |  9   | RTOG | RMOD | RVAI |          |      |
     * |---------+------+------+------+------+------+------+------+------+------+------+------+------+----------+------|
     * |            | PgDn | Left | Down | Rght |  +   |  -   |  4   |  5   |  6   | RSAD | RVAD |      |       |      |
     * |------------+------+------+------+------+------|------+------+------+------+------+------+------+-------+------|
     * |        |      | Play | Mute | VolD | VolU |  *   |  /   |  1   |  2   |  3   |  .   |           |      |      |
     * |--------+------+------+------+------+------+------+------+------+------+------+------+-----------+------+------|
     * |        |        |        |                    0                     |      |      |      |      |      |      |
     * `--------+--------+--------+------------------------------------------+------+------+------+------+------+------'
     */
    [1] = LAYOUT_all(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  KC_BSLS, KC_7,    KC_8,    KC_9,    UG_TOGG, UG_NEXT, UG_VALU, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PLUS, KC_MINS, KC_4,    KC_5,    KC_6,    UG_SATD, UG_SATD, UG_VALD, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, KC_ASTR, KC_SLSH, KC_1,    KC_2,    KC_3,    KC_DOT,  KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_0,                      KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS)
};
