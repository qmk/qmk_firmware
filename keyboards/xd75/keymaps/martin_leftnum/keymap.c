/* Copyright 2017 Benjamin Kesselring
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

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Layer shorthand
#define _QW 0
#define _LW 1
#define _RS 2
#define _FN 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY - MIT ENHANCED / GRID COMPATIBLE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | \      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BACKSP | 7      | 8      | 9      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ESC    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | 4      | 5      | 6      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | ENTER  | 1      | 2      | 3      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | HYPER  | LALT   | LGUI   | LOWER  | FN     | SPACE  | RAISE  | LEFT   | DOWN   | UP     | RIGHT  |        | 0      | .      |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = { /* QWERTY */
  { KC_PLUS, KC_MINS, KC_ASTR, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC  },
  { KC_7,    KC_8,    KC_9   , KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC  },
  { KC_4,    KC_5,    KC_6   , KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT  },
  { KC_1,    KC_2,    KC_3   , KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT   },
  { _______, KC_0,    KC_DOT , KC_LCTL, KC_HYPR, KC_LALT, KC_LGUI, MO(_LW), MO(_FN), KC_SPC,  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  },
 },

/* LOWERED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    |        | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ~      | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      | DEL    |        | VOLU   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | _      | +      | {      | }      | |      | PREV   | PLAY   | NEXT   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    | F12    | PAGEDW | PAGEUP | HOME   | END    | MUTE   |        | VOLD   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        | PLAY   |        | PREV   | VOLD   | VOLU   | NEXT   |        | MUTE   |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_LW] = { /* LOWERED */
  { _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL   },
  { _______, KC_VOLU, _______, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL    },
  { KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE   },
  { _______, KC_VOLD, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGDN, KC_PGUP, KC_HOME, KC_END , KC_MUTE   },
  { _______, KC_MUTE, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT   },
 },

/* RAISED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    |        | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |        | VOLU   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | -      | =      | [      | ]      | \      | PREV   | PLAY   | NEXT   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    | F12    | PAGEUP | PAGEDW | HOME   | END    | MUTE   |        | VOLD   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | PLAY   |        | PREV   | VOLD   | VOLU   | NEXT   |        | MUTE   |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_RS] = { /* RAISED */
  { _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL    },
  { _______, KC_VOLU, _______, KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL    },
  { KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS   },
  { _______, KC_VOLD, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGDN, KC_PGUP, KC_HOME, KC_END , KC_MUTE   },
  { _______, KC_MUTE, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT   },
 },

/* FUNCTION */

 [_FN] = { /* FUNCTION */
  { RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_TOGG, BL_INC,  BL_DEC,  _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP  , _______, KC_PSCR, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
