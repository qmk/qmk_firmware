/* Copyright 2017 Wunder
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
#include "xd75.h"

// Layer shorthand
#define _QW 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BSPC   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | \      | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | UP     | DEL    | DOWN   | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | HOME   | PG UP  | END    | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | FN     | LGUI   | LALT   | SPACE  | SPACE  | FN     | PG DN  | FN     | BSPC   | BSPC   | RALT   | RGUI   | FN     | RCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = { /* QWERTY */
  { KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_MINS, KC_GRV , KC_EQL , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC  },
  { KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_LBRC, KC_RBRC, KC_BSLS, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_QUOT  },
  { KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_UP  , KC_DEL , KC_DOWN, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT   },
  { KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_HOME, KC_PGUP, KC_END , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT  },
  { KC_LCTL, TT(_FN), KC_LGUI, KC_LALT, KC_SPC , KC_SPC , TT(_FN), KC_PGDN, TT(_FN), KC_BSPC, KC_BSPC, KC_RALT, KC_RGUI, TT(_FN), KC_RCTL  },
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     |        |        |        | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | MS 2   | MS UP  | MS 1   | MS 3   | RGB HD |        | RGB HI | [      | ]      | UP     | =      |        | \      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | MS W U |        | MS L   | MS DN  | MS R   |        | RGB SD |        | RGB SI | -      | LEFT   | DOWN   | RIGHT  |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | MS W D |        |        |        |        |        | RGB VD |        | RGB VI |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RGB TG | FN     |        |        | MS W L | MS W R |        | RESET  |        | MS 1   | MS 2   | RGB RMD| RGB MD | FN     |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_FN] = { /* FUNCTION */
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10  , KC_F11 , KC_F12   },
  { _______, _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, RGB_HUD, _______, RGB_HUI, KC_LBRC, KC_RBRC, KC_UP  , KC_EQL  , _______, KC_BSLS  },
  { KC_WH_U, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, RGB_SAD, _______, RGB_SAI, KC_MINS, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______  },
  { KC_WH_D, _______, _______, _______, _______, _______, RGB_VAD, _______, RGB_VAI, _______, _______, _______, _______ , _______, _______  },
  { RGB_TOG, TT(_FN), _______, _______, KC_WH_L, KC_WH_R, _______, RESET  , _______, KC_BTN1, KC_BTN2, RGB_RMOD,RGB_MOD , TT(_FN), _______  },
 }
};

