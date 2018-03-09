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
#include "action_layer.h"
#include "backlight.h"

enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | HOME   | DEL    | PG UP  | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALT   | RAISE  | SPACE  | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | SPACE  | LOWER  | RALT   | RGUI   | RCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QWERTY] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_MINS, KC_GRV,  KC_EQL,  KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_DEL },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_HOME, KC_DEL,  KC_PGUP, KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_END,  KC_UP,   KC_PGDN, KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT) },
  { KC_LCTL, KC_LGUI, KC_LALT, RAISE, KC_SPC, KC_SPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC, KC_SPC, LOWER, KC_RALT, KC_RGUI, KC_RCTL },
 },

/* RAISE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | NUM LK | P/     | P*     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | SELECT | CALC   | MYCOMP | MAIL   |        |        | P7     | P8     | P9     | -      |        |        | PR SCR | SCR LK | PR SCR |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | PREV   | PLAY   | NEXT   | STOP   |        |        | P4     | P5     | P6     | +      |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | VOL-   | MUTE   | VOL+   |        |        |        | P1     | P2     | P3     | PENT   |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RESET  |        |        | RAISE  |        |        | P0     |        | P.     | PENT   |        | LOWER  |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_RAISE] = { /* FUNCTION */
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
  { KC_MSEL, KC_CALC, _______, KC_MAIL, XXXXXXX, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_MINS, XXXXXXX,  XXXXXXX,  _______, _______, _______ },
  { KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, XXXXXXX, XXXXXXX, KC_P6,   KC_P5,   KC_P4,   KC_PLUS, XXXXXXX,  _______, XXXXXXX,  XXXXXXX,  XXXXXXX },
  { KC_VOLD, KC_MUTE, KC_VOLU, KC_APP,  XXXXXXX, XXXXXXX, KC_P3,   KC_P2,   KC_P1,   _______, XXXXXXX,  XXXXXXX,  XXXXXXX,  _______, _______ },
  { RESET,   _______, _______, _______, _______, _______, KC_KP_0, XXXXXXX, KC_PDOT, KC_PENT, _______, _______, _______, _______, _______ },
 },

 /* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | NUM LK | P/     | P*     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | SELECT | CALC   | MYCOMP | MAIL   |        |        | P7     | P8     | P9     | -      |        |        | PR SCR | SCR LK | PR SCR |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | PREV   | PLAY   | NEXT   | STOP   |        |        | P4     | P5     | P6     | +      |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | VOL-   | MUTE   | VOL+   |        |        |        | P1     | P2     | P3     | PENT   |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | RESET  |        |        | RAISE  |        |        | P0     |        | P.     | PENT   | PENT   | LOWER  |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_LOWER] = { /* FUNCTION */
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
  { KC_MSEL, KC_CALC, _______, KC_MAIL, KC_SPC, KC_SPC, KC_P7,   KC_P8,   KC_P9,   KC_MINS, KC_SPC,  KC_SPC,  _______, _______, _______ },
  { KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, KC_SPC, KC_SPC, KC_P6,   KC_P5,   KC_P4,   KC_PLUS, KC_SPC,  _______, KC_SPC,  KC_SPC,  KC_SPC },
  { KC_VOLD, KC_MUTE, KC_VOLU, KC_APP,  KC_SPC, KC_SPC, KC_P3,   KC_P2,   KC_P1,   _______, KC_SPC,  KC_SPC,  KC_SPC,  _______, _______ },
  { RESET,   _______, _______, _______, KC_SPC, KC_SPC, KC_KP_0, _______, KC_PDOT, KC_PENT, _______, LOWER, _______, _______, _______ },
 },
 /* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | F1     | F2     | F3     | F4     | F5     | F6     | NUM LK | P/     | P*     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |  RESET |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_ADJUST] = { /* FUNCTION */
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_NLCK, KC_SLSH, KC_ASTR, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_TOGG, BL_INC,  BL_DEC,  _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______ },
 }
};



/*

RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_TOGG, BL_INC,  BL_DEC,

*/


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            PORTE &= ~(1<<6);
          } else {
            unregister_code(KC_RSFT);
            PORTE |= (1<<6);
          }
          return false;
          break;
      }
    return true;
};
