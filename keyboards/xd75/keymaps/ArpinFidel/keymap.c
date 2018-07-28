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
 * | CAP LK | A      | S      | D      | F      | G      | PG UP  | DEL    | PG DN  | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | HOME   | UP     | END    | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | FN     | LGUI   | LALT   | SPACE  | SPACE  | LEFT   | DOWN   | RIGHT  | BSPC   | BSPC   | RALT   | RGUI   | FN     | RCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = { /* QWERTY */
  { KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_MINS, KC_GRV , KC_EQL , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC  },
  { KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_LBRC, KC_RBRC, KC_BSLS, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_QUOT  },
  { KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_PGUP, KC_DEL , KC_PGDN, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT   },
  { KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_HOME, KC_UP  , KC_END , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT  },
  { KC_LCTL, TT(_FN), KC_LGUI, KC_LALT, KC_SPC , KC_SPC , KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_BSPC, KC_RALT, KC_RGUI, TT(_FN), KC_RCTL  },
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | NUM LK | P/     | P*     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | MS 2   | MS UP  | MS 1   | MS 3   | P7     | P8     | P9     | -      |        | UP     |        | RGB HD | RGB HI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | MS W U |        | MS L   | MS DN  | MS R   |        | P4     | P5     | P6     | +      | LEFT   | DOWN   | RIGHT  | RGB SD | RGB SI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | MS W D |        |        |        |        |        | P1     | P2     | P3     |        |        |        |        | RGB VD | RGB VI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RGB TG | FN     |        |        | MS W L | MS W R | P0     | RESET  | P.     | MS 1   | MS 2   | RGB RMD| RGB MD | FN     |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_FN] = { /* FUNCTION */
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10  , KC_F11 , KC_F12   },
  { _______, _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, KC_P7,   KC_P8,   KC_P9,   KC_MINS, _______, KC_UP  , _______ , RGB_HUD, RGB_HUI  },
  { KC_WH_U, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_LEFT, KC_DOWN, KC_RIGHT, RGB_SAD, RGB_SAI  },
  { KC_WH_D, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______, _______ , RGB_VAD, RGB_VAI  },
  { RGB_TOG, TT(_FN), _______, _______, KC_WH_L, KC_WH_R, KC_P0,   RESET  , KC_PDOT, KC_BTN1, KC_BTN2 , RGB_RMOD,RGB_MOD , TT(_FN), _______  },
 }
};

