/* Copyright 2020 @ethan605
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
  /* 0: Qwerty layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ ESC │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │ INS │ DEL │ FN  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │   BSPC    │HOME │
   * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
   * │  TAB   │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  BSLS  │END  │
   * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
   * │  LCTRL  │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │    ENTER    │PGUP │
   * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────┬─────┼─────┤
   * │   LSHFT    │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │  RSHFT   │ UP  │PGDN │
   * ├──────┬─────┴─┬───┴──┬──┴─────┴─────┴─────┴─────┴─────┴────┬┴────┬┴────┬┴────┬─────┼─────┼─────┤
   * │ CAPS │ LALT  │ LCMD │                 SPC                 │RCMD │RALT │RCTL │LEFT │DOWN │RIGHT│
   * └──────┴───────┴──────┴─────────────────────────────────────┴─────┴─────┴─────┴─────┴─────┴─────┘
   */
  [0] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_DEL,   MO(1),
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_DEL,   KC_BSPC,  KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_END,
    KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_PGUP,
    KC_LSFT,  MO(1),    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_PGDN,
    KC_CAPS,  KC_LALT,  KC_LCMD,                      KC_SPC,   KC_SPC,   KC_SPC,                       KC_RCMD,  KC_RALT,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  /* 1: Function layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │ FN  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
   * │     │     │     │     │     │     │     │     │     │     │     │     │     │   QK_BOOT   │     │
   * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
   * │        │ TOG │ MOD │ HU+ │ HU- │ SA+ │ SA- │ VA+ │ VA- │     │     │     │     │        │     │ // RGB controls
   * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
   * │         │     │     │     │     │     │     │     │     │     │     │     │             │     │
   * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴───────┬─────┼─────┤
   * │            │     │     │     │ DEC │ TOG │ INC │STEP │     │     │     │          │     │     │ // Backlight controls
   * ├──────┬─────┴─┬───┴──┬──┴─────┴─────┴─────┴─────┴─────┴────┬┴────┬┴────┬┴────┬─────┼─────┼─────┤
   * │      │       │      │                                     │     │     │     │     │     │     │
   * └──────┴───────┴──────┴─────────────────────────────────────┴─────┴─────┴─────┴─────┴─────┴─────┘
   */
  [1] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  QK_BOOT,  _______,
    _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  _______,  _______,  _______,  BL_DOWN,  BL_TOGG,  BL_UP,    BL_STEP,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______
  ),
};
