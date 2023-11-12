/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
     Copyright 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified Copyright 2018 Elvis Pfutzenreuter <elvis.pfutzenreuter@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public LicensezZZ
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _x_ KC_TRNS
#define _DEFLT 0
#define _AR 1
#define _RAISE 2

#define LAYOUT LAYOUT_default

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Layer 0, default layer
   *  | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | || > |  <<  |  >>  | vol+ | vol- | Bkspc |
   *  |  ~`  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |    0 |    - |    = |    BkSpc    |NumLck|   /  |   *  |   -   |
   *  |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |    P |    { |    } |     \    |  7   |   8  |   9  |       |
   *  |   Ctrl    |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |    ; |   '  |     Return     |  4   |   5  |   6  |   +   |
   *  |    LShft     |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |       RShft       |  1   |   2  |   3  |       | 
   *  | Ctrl  |  Alt  |  Win  |                  Space                      |  Win  |  Fn   |  Alt  |   Ctrl   |      0      |   .  | Enter |
   * 
   * Layout is inspired on Model F.
   * Extra keys on top right, as well as some seldom-used keys, are media keys in default layer.
   * Num Lock toogles layer, so the numeric block works as a Model F navigation block in a Mac.
   * (Fn-Num Lock operates as conventional Num Lock in case the keyboard needs to be used with Windows or Linux.)
   * Caps Lock operates normally but it takes FN to work, the key is Ctrl by default, like in Model F.
   */
  [_DEFLT] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_BSPC,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,          TO(_AR), KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,          KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,                    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                            KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL, KC_LALT,KC_LGUI,                     KC_SPC,                   KC_RGUI, KC_NO, MO(_RAISE), KC_RALT,  KC_RCTL,                  KC_P0,   KC_P0,   KC_PDOT
  ),

  /* Layer 1, Num Lock activated 
   *  ...
   *  ... 
   *  ... | Home |  Up  | Pg Up |       |
   *  ... | Left | (no) | Right |   +   |
   *  ... | End  | Down | Pg Dn |       |
   *  ... |     Ins     |  Del  | Enter |
   */
  [_AR] = LAYOUT(
    _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_,       TO(_DEFLT), _x_, _x_, _x_,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_,          KC_HOME, KC_UP,   KC_PGUP, _x_,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_,               KC_LEFT, KC_NO,   KC_RGHT, _x_,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_,                    KC_END,  KC_DOWN, KC_PGDN, _x_,
    _x_, _x_,_x_, _x_, _x_, _x_, _x_, _x_, _x_,                                    KC_INS,  KC_INS,  KC_DEL
  ),

  /* Layer 2, raise layer
   *  |      |      |      |      |      |      |      |      |      |      |      |      |      | PrtSc |Pause|ScrLck| stop | mute |  Del  |
   *  |          | RGB Toggle | RGB Hue - | RGB Hue + |   |   |   |   |   |   |    |      |      |     Del     |NumLck|      |      |       |
   *  |          | RGB Mode + | RGB Satu- | RGB Satu+  |   |   |   |   |   |   |      |      |      |          |      |      |      |       |
   *  | Caps Lck | RGB Mode - | RGB Brgt- | RGB Brgt+   |   |   |   |   |   |   |   |   |     |                |      |      |      |       |
   *  |              |      |      |      |      |      |      |      |      |      |      |                   |      |      |      |       |
   *  |       |       |       |                                             | Win Menu  |      |        |      |             |      |       |
   */ 
  [_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_PAUS,  KC_SCRL, KC_MUTE, KC_MSTP, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,            KC_NUM,  _______, _______, _______,
    _______, RGB_TOG, RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,
    KC_CAPS, RGB_MOD, RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, _______, _______,  _______, _______,                   _______, _______, _______, _______,
    _______, RGB_RMOD,RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______,
    _______, _______,_______,                     _______,                  KC_APP,  _______,    _______,  _______,  _______,               _______, _______, _______
  ),

};
