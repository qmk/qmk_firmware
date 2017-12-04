/* Copyright 2017 Valentin Brosseau
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
#include "keymap_bepo.h"

// Layer shorthand
#define _BP 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Native BepoDev for compatible computer
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | "      | <      | >      | (      | )      | %      | VOL-   | VOL+   | @      | +      | -      | /      | *      | =      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | B      | E_ACUT | P      | O      | $      | E_GRAV | DEL    | E_CIRC | V      | D      | L      | J      | Z      | C_CEDIL|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | RALT   | A      | U      | I      | E      | ,      | ENTER  | ENTER  | C      | T      | S      | R      | N      | M      | W      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | A_GRAV | Y      | X      | .      | K      | BACKSP | BACKSP | ’      | Q      | G      | H      | F      | UP     | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LALT   | LCTRL  | LGUI   | FN     | SPACE  | SPACE  | RALT   | RALT   | SPACE  | SPACE  | FN     | RGUI   | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_BP] = { /* BepoDev */
  { KC_ESC,  BP_DQOT,    BP_LGIL,    BP_RGIL, BP_LPRN, BP_RPRN,    BP_PERCENT, KC_VOLD, KC_VOLU, BP_AT,   BP_PLUS, BP_MINUS, BP_SLASH, BP_ASTR, BP_EQUAL },
  { KC_TAB,  BP_B,       BP_E_ACUTE, BP_P,    BP_O,    BP_DOLLAR,  BP_E_GRAVE, KC_DEL,  BP_DCRC, BP_V,    BP_D,    BP_L,     BP_J,     BP_Z,    BP_CCED  },
  { KC_RALT, BP_A,       BP_U,       BP_I,    BP_E,    BP_COMMA,   KC_ENT,     KC_ENT,  BP_C,    BP_T,    BP_S,    BP_R,     BP_N,     BP_M,    BP_W     },
  { KC_LSFT, BP_A_GRAVE, BP_Y,       BP_X,    BP_DOT,  BP_K,       KC_BSPC,    KC_BSPC, BP_APOS, BP_Q,    BP_G,    BP_H,     BP_F,     KC_UP,   KC_RSFT  },
  { KC_LALT, KC_LCTL,    KC_LGUI,    MO(_FN), KC_SPC,  KC_SPC,     KC_RALT,    KC_RALT, KC_SPC,  KC_SPC,  MO(_FN), KC_RGUI,  KC_LEFT,  KC_DOWN, KC_RGHT  },
 },

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     |        | P/     | P*     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | P7     | P8     | P9     | -      | RGB_TOG| RGB_MOD| RGB_HUI| RGB_HUD|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | PREV   | PLAY   | NEXT   | STOP   |        | P4     | P5     | P6     | +      | RGB_SAI| RGB_SAD| RGB_VAI| RGB_VAD|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | VOL-   | MUTE   | VOL+   |        |        | P1     | P2     | P3     | PENT   |        |        |        | Home   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RESET  |        |        | FN     |        |        | P0     | P0    | P.     | PENT   |        |        | FN     | End    |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_FN] = { /* FUNCTION */
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_TRNS, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
  { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_MINS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, KC_TRNS },
  { KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS },
  { KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_APP,  KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS },
  { RESET,   KC_TRNS, KC_TRNS, MO(_FN), KC_TRNS, KC_TRNS, KC_KP_0, KC_KP_0, KC_PDOT, KC_PENT, KC_TRNS, KC_TRNS, MO(_FN), KC_END,  KC_TRNS },
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
