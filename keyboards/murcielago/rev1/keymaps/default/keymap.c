/*
Copyright 2020 elagil

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

enum layers {
    BASE,
    _NAV,
    _SYM,
    _FN
};

#define PRE_WRD LCTL(KC_LEFT)  // jump to next word
#define NXT_WRD LCTL(KC_RGHT)  // jump to previous word

#define NXT_WDL LCTL(KC_DEL)   // delete next word
#define PRE_WDL LCTL(KC_BSPC)  // delete previous word

#define NAV MO(_NAV) // NAV layer access
#define SYM MO(_SYM) // SYM layer access
#define FN OSL(_FN) // FN layer access

/*
 * This default keymap is aimed at users of the US or US international layout
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* BASE
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |  =+  |  1!  |  2@  |  3#  |  4$  |  5%  |                        |  6^  |  7&  |  8*  |  9(  |  0)  |  -_  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       | Tab  |  Q   |  W   |  E   |  R   |  T   |                        |   Y  |   U  |   I  |   O  |   P  |  \|  |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       | Del  |  A   |  S   |  D   |  F   |  G   |                        |   H  |   J  |   K  |   L  |  ;:  |  '"  |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       | Sft  |  Z   |  X   |  C   |  V   |  B   | Esc  |          | Ent  |   N  |   M  |  ,<  |  .>  |  /?  |  Sft |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  | LAlt | LGUI |  SYM | Back | Ctrl |                | RAlt |Space | NAV  | PWR  | Play |
   *                  `----------------------------------'                `----------------------------------'
   */
  [BASE] = LAYOUT( /* qwerty */
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_DEL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    QK_GESC, KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
             KC_LALT, KC_LGUI, SYM,     KC_BSPC, KC_LCTL,                   KC_RALT, KC_SPC,  NAV,     FN,      KC_MPLY
  ),

  /* NAV - navigation layer
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                        |   F6 |   F7 |   F8 |   F9 |   F10|   F11|
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |      |      |      |      |      |                        |      |PRE W |  UP  |NXT W |      |      |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |      |      |      |      |      |                        | HOME | LEFT | DOWN |RIGHT | END  |      |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      |      |      |      |      |      |      |          |      |      |DEL PW| Ins  |DEL NW|      |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |      |      |      |                |      |      |      |      |      |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_NAV] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, PRE_WRD, KC_UP,   NXT_WRD, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PRE_WDL, KC_INS,  NXT_WDL, XXXXXXX, XXXXXXX,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, _______,                   XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
  ),

  /* SYM - symbols and numpad layer
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                        |   F6 |   F7 |   F8 |   F9 |   F10|   F11|
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |      |      |      |  (   |  )   |      |                        |      |   7  |   8  |   9  |      |      |
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       | CLck |      |  ~   |  {   |  }   |      |                        |   +  |   4  |   5  |   6  |   -  |      |
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      |      |  `   |  [   |  ]   |      |      |          | NEnt |   *  |   1  |   2  |   3  |   /  |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |      |      |      |                |      |   0  |      |      | NLck |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_SYM] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX,                   XXXXXXX, KC_P7,   KC_P8,   KC_P9,   XXXXXXX, XXXXXXX,
    KC_CAPS, XXXXXXX, KC_TILD, KC_LCBR, KC_RCBR, XXXXXXX,                   KC_PPLS, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_GRV,  KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, KC_PENT, KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PSLS, XXXXXXX,
             XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P0,   XXXXXXX, XXXXXXX, KC_NUM
  ),

  /* FN - one-shot access to F-keys with modifiers
   *       ,-----------------------------------------.                        ,-----------------------------------------.
   *       |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                        |   F6 |   F7 |   F8 |   F9 |   F10|   F11|
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |A F12 |A F1  |A F2  |A F3  |A F4  |A F5  |                        | A F6 | A F7 | A F8 | A F9 | A F10| A F11|
   *       |------+------+------+------+------+------|                        |------+------+------+------+------+------|
   *       |C F12 |C F1  |C F2  |C F3  |C F4  |C F5  |                        | C F6 | C F7 | C F8 | C F9 | C F10| C F11|
   *       |------+------+------+------+------+------+------.          ,------+------+------+------+------+------+------|
   *       |      |      |      |      |      |      |      |          |      |      |      |      |      |      |      |
   *       `------------------------------------------------'          `------------------------------------------------'
   *                  |      |      |      |      |      |                |      |      |      |      |      |
   *                  `----------------------------------'                `----------------------------------'
   */
  [_FN] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  C(KC_F12), C(KC_F1),C(KC_F2),C(KC_F3),C(KC_F4),C(KC_F5),                  C(KC_F6),C(KC_F7),C(KC_F8),C(KC_F9),C(KC_F10),C(KC_F11),
  A(KC_F12), A(KC_F1),A(KC_F2),A(KC_F3),A(KC_F4),A(KC_F5),                  A(KC_F6),A(KC_F7),A(KC_F8),A(KC_F9),A(KC_F10),A(KC_F11),
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _NAV ... _SYM:
            if (index == 0 || index == 1) { /* Left or right encoder */
                // Next/previous track
                clockwise ? tap_code(KC_MNXT) : tap_code(KC_MPRV);
            }
            break;

        default:
            if (index == 0 || index == 1) { /* Left or right encoder */
                // Volume up or down
                clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            }
            break;
    }
    return true;
}
