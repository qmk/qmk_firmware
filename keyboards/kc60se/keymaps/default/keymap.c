/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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

/* Happy Hacker Keyboard */

enum layer_names { _BL, _FL };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// clang-format off
    [_BL] = LAYOUT_60_ansi_split_bs_rshift(
          KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
          KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FL),
          KC_NO,   KC_LALT, MO(_FL),                   KC_SPC,                                      KC_NO,   KC_RGUI, KC_RALT, KC_NO
    ),
    [_FL] = LAYOUT_60_ansi_split_bs_rshift(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_INS,
        KC_CAPS,  BL_ON,   BL_STEP, _______, _______, NK_TOGG, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   _______, KC_DEL,
        _______,  KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______,
        _______,  KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
        _______,  _______,  _______,                  _______,                                     _______, KC_MSTP, _______, _______
    )
// clang-format on
};

/* BL
 *,--------------------------------------------------------------------------.
 *| esc|  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |  \ |  ` |
 *|--------------------------------------------------------------------------+
 *| tab  |  q |  w |  e |  r |  t |  y |  u |  i |  o |  p |  [ |  ] | bksp  |
 *|--------------------------------------------------------------------------+
 *| ctrl  |  a |  s |  d |  f |  g |  h |  j |  k |  l |  ; |  ' |  enter    |
 *|--------------------------------------------------------------------------+
 *| shift   |  z |  x |  c |  v |  b |  n |  m |  , |  . |  / | rshift  | fn1|
 *|--------------------------------------------------------------------------+
 *        |lalt| fn1  |               space              | rgui  |ralt|
 *        `-----------------------------------------------------------'
 * FL
 *,--------------------------------------------------------------------------.
 *|    | f1 | f2 | f3 | f4 | f5 | f6 | f7 | f8 | f9 | f10| f11| f12|    | ins|
 *|--------------------------------------------------------------------------+
 *| caps |blon|blup|    |    |NKRO|    |    | psc|slck|paus| up |    |  del  |
 *|--------------------------------------------------------------------------+
 *|       |vol-|vol+|mute|    |    | *  | /  |home|pgup|left|rght|  penter   |
 *|--------------------------------------------------------------------------+
 *|         |prev|play|next|    |    | +  | -  |end |pgdn|down|         |    |
 *|--------------------------------------------------------------------------+
 *        |    |      |                                  | stop |    |
 *        `----------------------------------------------------------'
 */
