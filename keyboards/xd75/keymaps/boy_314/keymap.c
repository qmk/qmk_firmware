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
#define _FN1 1
#define _FN2 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | '      | .      | .      | P      | Y      | [      | \      | ]      | F      | G      | C      | R      | L      | /      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | O      | E      | U      | I      | HOME   | DEL    | PG UP  | D      | H      | T      | N      | S      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | ;      | Q      | J      | K      | X      | END    | UP     | PG DN  | M      | W      | W      | V      | Z      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | DEL    | LALT   | FN1    | FN1    | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | FN2    | FN2    | RALT   | RGUI   | RCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC  },
  { KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_LBRC, KC_BSLS, KC_RBRC, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH  },
  { KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_HOME, KC_DEL,  KC_PGUP, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT   },
  { KC_LSPO, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_END,  KC_UP,   KC_PGDN, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSPC  },
  { KC_LCTL, KC_DEL,  KC_LALT, MO(_FN1),MO(_FN1),KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  MO(_FN2),MO(_FN2),KC_RALT, KC_RGUI, KC_RCTL  },
 },

/* FUNCTION1
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |   `    |   !    |   @    |   #    |   $    |   %    |        |        |        |    ^   |   &    |   *    |   (    |   )    | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |   ~    |   !    |   @    |   #    |   $    |   %    | RESET  |RGB HUE-|RGB HUE+|    ^   |   &    |   *    |   (    |   )    | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | DEL    |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |RGB SAT-|RGB SAT+|        |   _    |   +    |   {    |   }    |   |    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |BRIGHT- |BRIGHT+ |        |        |        | HOME   | END    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |RGB MODE|RGB MODE|        |        | PREV   | VOL UP |VOL DOWN| NEXT   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_FN1] = { /* FUNCTION1 */
  { KC_GRV , KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC  },
  { KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,   RESET, RGB_HUD, RGB_HUI, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL   },
  { KC_DEL,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, RGB_SAD, RGB_SAI, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE  },
  { _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, RGB_VAD, RGB_VAI, _______, _______, _______, KC_HOME,  KC_END, _______  },
  { _______, _______, _______, _______, _______, _______, _______,RGB_RMOD, RGB_MOD, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  },
 },


/* FUNCTION2
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |   `    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |   `    |        |        |   UP   |        |        | RESET  |RGB HUE-|RGB HUE+|        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |  LEFT  |  DOWN  | RIGHT  |        |        |RGB SAT-|RGB SAT+|        |   -    |   =    |   [    |   ]    |   \    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |BRIGHT- |BRIGHT+ |        |        |        | PAGE UP| PAGE DN|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |RGB MODE|RGB MODE|        |        | PREV   | VOL UP |VOL DOWN| NEXT   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */^    
 
 [_FN2] = { /* FUNCTION2 */
  {  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______, _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC  },
  {  KC_GRV, _______, _______,   KC_UP, _______, _______,   RESET, RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, KC_DEL   },
  {  KC_DEL, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, RGB_SAD, RGB_SAI, _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS  },
  { _______, _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______, _______, _______, KC_PGDN, KC_PGUP, _______  },
  { _______, _______, _______, _______, _______, _______, _______,RGB_RMOD, RGB_MOD, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  },
 }
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
