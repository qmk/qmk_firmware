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

          KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT,

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

              _______, _______, _______

  //         └────────┴────────┴────────┘
  ),
  [ogre] = LAYOUT(
  //         ┌────────┬────────┬────────┐

               RGB_MOD, RGB_TOG, RGB_RMOD,

  //    ├────────┼────────┼────────┼────────┼

           KC_F13,  KC_F14,  KC_F15,  KC_F16,

  //    ├────────┼────────┼────────┼────────┼

               _______, _______, _______

  //         └────────┴────────┴────────┘
  ),
  [tcp] = LAYOUT(
  //         ┌────────┬────────┬────────┐

               KC_WBAK, KC_WREF, KC_WFWD,

  //    ├────────┼────────┼────────┼────────┼

          XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX,

  //    ├────────┼────────┼────────┼────────┼

              _______, _______, _______

  //         └────────┴────────┴────────┘
  ),
};
