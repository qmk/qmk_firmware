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

#define ESCCTRL CTL_T(KC_ESC)
#define KC_SPFN LT(_SPCFN, KC_SPC) // press for space, hold for function layer (aka spacefn)
#define HYPER MT(MOD_HYPR, KC_ENT)
#define ENTSFT SFT_T(KC_ENT)
#define APPTOG LGUI(KC_TAB) // toggles last two apps used
#define APPWIN LGUI(KC_GRV) // toggles app windows (Mac/Linux)
#define SPCRGT LCTL(KC_RGHT) // Switch workspaces
#define SPCLFT LCTL(KC_LEFT)

#define _______ KC_TRANS
#define XXXXXXX KC_NO

// Layer shorthand
enum layers{
  _QWERTY = 0,
  _FUNC,
  _UPPER,
  _LOWER,
  _SPCFN
};

enum keycodes{
  QWERTY = 0,
  FUNC,
  UPPER,
  LOWER,
  SPCFN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------.
 * | F10  | F11  | F12  | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |------+------+------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | F7   | F8   | F9   | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | \      |
 * |------+------+------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | F4   | F5   | F6   | ESC/CTL| A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |
 * |------+------+------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | F1   | F2   | F3   | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | ENT/SFT|
 * |------+------+------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * | PGDN |PGUP  | HOME | FUNC   |HYPER   | LCTL   | LGUI   | LALT   | SPCFN  | SPCFN  | RALT   | RGUI   | RCTL   | HYPER  | FUNC   |
 * '--------------------------------------------------------------------------------------------------------------------------------'
 */

    [_QWERTY] = {
        /* QWERTY */
        {KC_F10,  KC_F11,  KC_F12,  KC_GRV,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
        {KC_F7,   KC_F8,   KC_F9,   KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS},
        {KC_F4,   KC_F5,   KC_F6,   ESCCTRL, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
        {KC_F1,   KC_F2,   KC_F3,   KC_LSFT, KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ENTSFT},
        {KC_PGDN, KC_PGUP, KC_HOME, FUNC,    HYPER, KC_LCTL, KC_LGUI, KC_LALT, SPCFN,  SPCFN,  KC_RALT, KC_RGUI, KC_RCTL, HYPER,   FUNC},
    },

/* SPCFN
 * .-----------------------------------------------------------------------------------------------------------------------------------------.
 * |      | /    | *    |         |         |         | PAGEUP |         |         |        |         |    UP   |   -    |    =    |   DEL   |
 * |------+------+------+---------+---------+---------+--------+---------+---------+--------+---------+---------+--------+---------+---------+
 * | P7   | P8   | P9   |         |         | SPCLEFT | PAGEDN |  SPCRGT |    [    |   ]    | LEFT    |  DOWN   | RIGHT  |         |         |
 * |------+------+------+---------+---------+---------+--------+---------+---------+--------+---------+---------+--------+---------+---------+
 * | P4   | P5   | P6   |         |         |         |        |         |    {    |   }    |         |         |        |         |         |
 * |------+------+------+---------+---------+---------+--------+---------+---------+--------+---------+---------+--------+---------+---------+
 * | P1   | P2   | P3   |         |         |         |        |         |    (    |   )    |         |         |        |         |         |
 * |------+------+------+---------+---------+---------+--------+---------+---------+--------+---------+---------+--------+---------+---------+
 * | VOLD | VOLUp| MUTE |         |         |         |        |         |         |        |         |         |        |         |         |
 * '-----------------------------------------------------------------------------------------------------------------------------------------.
 */

    [_SPCFN] = {
        /* SPCFN */
        {_______, KC_SLSH, KC_ASTR, _______, _______, _______, KC_PGUP, _______, _______, _______, _______, KC_UP,   KC_MINS,  KC_EQL, KC_DEL,
        {KC_P7,  KC_P8,   KC_P9,    _______, _______, SPCLFT,  KC_PGDN, SPCRGT,  KC_LBRC, KC_RBRC, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
        {KC_P4,   KC_P5,   KC_P6,   _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, _______,
        {KC_P1,   KC_P2,   KC_P3,   _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, _______, _______, _______, _______, _______,
        {KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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
