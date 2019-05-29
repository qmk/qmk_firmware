/* Copyright 2019 kimat
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
/* Sendstring definitions for the belgian layout */
#ifndef SENDSTRING_BELGIAN
#define SENDSTRING_BELGIAN

#include "keymap_belgian.h"

const bool ascii_to_shift_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 1, 0, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};
const bool ascii_to_altgr_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 0
};

// NOTE that you have to send the dead keys twice: tilda, circ
// SEND_STRING(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^^``_abcdefghijklmnopqrstuvwxyz{|}~~");
const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    KC_BSPC, KC_TAB, KC_ENT, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, KC_ESC, 0, 0, 0, 0,
 /* SPACE  !     "      #        $     %     &      '                 */
    KC_SPC, BE_EXLM, BE_QUOT, BE_QUOT, BE_DLR,BE_UGRV,BE_AMP, BE_APOS ,
  /*  (      )     *      +        ,        -        .       /        */
    BE_LPRN, BE_RPRN, BE_DLR,BE_EQL, BE_COMM, BE_MINS, BE_SCLN, BE_EQL,
  /*   0     1     2     3     4     5    6     7                     */
    KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
  /*   8     9      :       ;         <        =       >       ?      */
    KC_8, KC_9, BE_COLN, BE_SCLN, BE_LESS,    BE_EQL, BE_LESS, BE_COMM,
  /*   @     A     B     C     D     E     F     G                    */
    KC_2, BE_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
  /*   H     I     J     K     L     M     N     O                    */
    KC_H, KC_I, KC_J, KC_K, KC_L, BE_M, KC_N, KC_O,
  /*   P     Q     R     S     T     U     V     W                    */
    KC_P, BE_Q, KC_R, KC_S, KC_T, KC_U, KC_V, BE_W,
  /*   X     Y     Z      [         \       ]       ^      _          */
    KC_X, KC_Y, BE_Z, BE_CIRC, BE_LESS, BE_DLR, BE_CIRC, BE_MINS,
  /*   `       a     b     c     d     e     f     g                  */
    BE_MU, BE_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
  /*   h     i     j     k     l     m     n     o                    */
    KC_H, KC_I, KC_J, KC_K, KC_L, BE_M, KC_N, KC_O,
  /*    p    q     r     s     t     u     v     w                    */
    KC_P, BE_Q, KC_R, KC_S, KC_T, KC_U, KC_V, BE_W,
  /*    x    y     z      {        |        }        ~    DELETE      */
    KC_X, KC_Y, BE_Z, KC_9, KC_1, KC_0, BE_EQL, KC_DEL
};

#endif
