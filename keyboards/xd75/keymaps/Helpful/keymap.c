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
#define _BL 0
#define _FL 1

enum custom_keycodes {
  TERMINAL = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case TERMINAL:
                SEND_STRING(SS_LGUI("x")"i");
                return false; break;
            // case EXIT:
            //     SEND_STRING("exit()");
            //     return false; break;
        }
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | BKSPC  | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | {      | }      | \      | HOME   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAPS   | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |        | ENTER  | END    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | `      | RSHIFT | UP     | TERM   |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALT   | SPACE  | SPACE  | SPACE  | SPACE  | SPACE  | SPACE  | RALT  | FN      | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_BL] = { /* BASE */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,   KC_DEL },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC,  KC_RBRC, KC_BSLASH, KC_HOME },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOTE, KC_ENT,  KC_ENT,    KC_END },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_GRV,  KC_RSFT,  KC_UP,     TERMINAL  },
  { KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC, KC_SPC, KC_SPC, KC_SPC,   KC_SPC,  KC_RALT,TO(_FL), KC_RCTL, KC_LEFT,  KC_DOWN,   KC_RIGHT },
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    |        | BKSPC  | RESET  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | 7      | 8      | 9      | HOME   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | CAPS   | A      | S      | D      | F      | G      | H      | J      | K      | L      |        | 4      | 5      | 6      | END    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      |        |        |        | 1      | 2      | 3      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | VOL-   | MUTE   | VOL+   | SPACE  | SPACE  | SPACE  | SPACE  | SPACE  | SPACE  |        | FN     | 0      | PREV   | PLAY   | NEXT   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FL] = { /* FUNCTION */
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_BSPC, RESET   },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_7,    KC_8,    KC_9,    KC_HOME },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_NO,   KC_4,    KC_5,    KC_6,    KC_END  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,    KC_M,    KC_NO,   KC_NO,   KC_NO,   KC_1,    KC_2,    KC_3,    KC_ENT  },
  { KC_VOLD, KC_MUTE, KC_VOLU, KC_SPC,  KC_SPC, KC_SPC,  KC_SPC, KC_SPC,  KC_SPC,  KC_NO,  TO(_BL),  KC_0,    KC_MPRV, KC_MPLY, KC_MNXT },
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
