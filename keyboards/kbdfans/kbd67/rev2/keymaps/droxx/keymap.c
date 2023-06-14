// KBD67 Rev 2 ANSI Layout

/* Copyright 2022 Alex K
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
// #include "droxx.h"

// make keycodes easier to change for the future
#define DRXX        KC_TRNS

// enumerate custom layer names for the keymap
enum keymap_layers {
    _DRXXMAIN = 0,
    _DRXXFN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap Base Layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │Esc│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BackSp│Hom│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ BkSl│PgU│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │Caps  │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│   Enter│PgD│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │Shift   │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│ Shift│ ↑ │End│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │Ctrl│ Win│ Alt│          Space         │Alt│Fn │Ctl│ ← │ ↓ │ → │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */
[_DRXXMAIN] = LAYOUT_65_ansi(
  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                     KC_SPC,                        KC_RALT,     MO(_DRXXFN),     KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

  /* Keymap Fn Layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │~ `│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│    Del│Ins│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │     │RM-│RB+│RM+│   │RTg│   │   │   │   │   │   │   │     │Pau│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │      │RS-│RB-│RS+│   │   │   │   │   │   │   │   │        │SLk│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │        │   │DGu│EGu│   │   │   │   │   │   │   │      │   │PSr│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │    │    │    │                        │   │   │   │   │   │   │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */
[_DRXXFN] = LAYOUT_65_ansi(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_INS,
  DRXX  ,   RGB_RMOD, RGB_VAI,  RGB_MOD,  DRXX,     RGB_TOG,  DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     KC_PAUS,
  DRXX,     RGB_SPD,  RGB_VAD,  RGB_SPI,  DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,               DRXX,     KC_SCRL,
  DRXX,     DRXX,     GUI_OFF,  GUI_ON,   DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,     DRXX,               DRXX,     KC_PSCR,
  DRXX,     DRXX,     DRXX,                         DRXX,                         DRXX,          DRXX,          DRXX,     DRXX,     DRXX,     DRXX),
};
