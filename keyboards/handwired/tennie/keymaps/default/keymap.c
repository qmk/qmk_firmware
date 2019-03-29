/* Copyright 2018 Jack H.
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
#include QMK_KEYBOARD_H

#define TAPPING_TOGGLE 2

// Custom keycode definitions, and keycode renames
#define KC_LTST RGB_MODE_RGBTEST
#define KC_RTOG RGB_TOG
#define KC_RNXT RGB_MODE_FORWARD
#define KC_RPRV RGB_MODE_REVERSE
#define KC_oooo KC_TRNS
#define KC_XXXX KC_NO

// Layer names
#define base  0
#define shrek 1
#define ogre  2
#define tcp   3

// Layer Switches
#define KC_SHRK TT(shrek)
#define KC_OGRE TT(ogre)
#define KC_TCP TT(tcp)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [base] = LAYOUT(
  //         ┌────────┬────────┬────────┐

                KC_DEL,  KC_SPC,  KC_ENT,

  //    ├────────┼────────┼────────┼────────┼

          KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,

  //    ├────────┼────────┼────────┼────────┼

               KC_SHRK, KC_OGRE, KC_TCP

  //         └────────┴────────┴────────┘
  ),
  [shrek] = LAYOUT(
  //         ┌────────┬────────┬────────┐

               KC_MPRV, KC_MPLY, KC_MNXT,

  //    ├────────┼────────┼────────┼────────┼

          KC_BRID, KC_VOLD, KC_VOLU, KC_BRIU,

  //    ├────────┼────────┼────────┼────────┼

               KC_oooo, KC_oooo, KC_oooo

  //         └────────┴────────┴────────┘
  ),
  [ogre] = LAYOUT(
  //         ┌────────┬────────┬────────┐

               KC_RNXT, KC_RTOG, KC_RPRV,

  //    ├────────┼────────┼────────┼────────┼

           KC_F13,  KC_F14,  KC_F15,  KC_F16,

  //    ├────────┼────────┼────────┼────────┼

               KC_oooo, KC_oooo, KC_oooo

  //         └────────┴────────┴────────┘
  ),
  [tcp] = LAYOUT(
  //         ┌────────┬────────┬────────┐

               KC_WBAK, KC_WREF, KC_WFWD,

  //    ├────────┼────────┼────────┼────────┼

          KC_XXXX, KC_PGDN, KC_PGUP, KC_XXXX,

  //    ├────────┼────────┼────────┼────────┼

               KC_oooo, KC_oooo, KC_oooo

  //         └────────┴────────┴────────┘
  ),
};
