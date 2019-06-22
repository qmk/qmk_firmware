/* Copyright 2016 Jack Humbert
 *
 * This program is KCee software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the KCee Software Foundation, either version 2 of the License, or
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
/* Sendstring definitions for the Colemak layout */
#ifndef SENDSTRING_FRENCH
#define SENDSTRING_FRENCH

#include "keymap_french_sendstring.h"

/* AZERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | &      | é      | "      | '      | (      | -      | è      | _      | ç      | à      | )      | =      | INSERT | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | a      | z      | e      | r      | t      | y      | u      | i      | o      | p      | ^      | $      | ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | q      | s      | d      | f      | g      | h      | j      | k      | l      | m      | ù      | *      | ENTER  | PG DN  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | w      | x      | c      | v      | b      | n      | ,      | ;      | :      | !      | <      | LSHIFT | UP     | DEL    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | CMD    | ALT    | FN     | SPACE  | SPACE  | SPACE  | SPACE  | ALGR   | MENU   | HOME   | END    | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 const bool ascii_to_shift_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 0, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 1, 1,
    0, 1, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
//    0,0,1,0,0,0,0,0

};

const bool ascii_to_alt_lut[0x80] PROGMEM = {
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,

 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 1, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 1, 1, 1, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 1, 1, 1, 1, 0,

};


//    modifié quantum.h et quantum.c avec 0x100 pour pouvoir aller au delà de 127. Plus d'erreur, mais il ne prend pas la suite en compte quand même ?
const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
//7
    0, 0, 0, 0, 0, 0, 0, 0,
//   15
    KC_BSPC, KC_TAB, KC_ENT, 0, 0, 0, 0, 0,
//    23
    0, 0, 0, 0, 0, 0, 0, 0,
//    31
    0, 0, 0, KC_ESC, 0, 0, 0, 0,

	/* SPACE       !     "      #        $          %     &      '                    39*/
    KC_SPC, FR_AMP, FR_QUOT, FR_AMP, FR_APOS, FR_LPRN, FR_AMP, FR_QUOT,
	/*  (           )       *      +        ,        -        .       /                    47*/
    FR_LPRN, FR_RPRN, FR_ASTR, FR_EQL, FR_COMM, FR_RPRN, FR_SCLN, FR_COLN,
	/*   0        1     2     3     4     5    6     7                    55 */
    KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_7,
	/*   8     9      :       ;         <        =       >       ?                     63 */
    KC_KP_8, KC_KP_9, FR_COLN, FR_M, FR_SCLN, FR_EQL, FR_COLN, FR_EXLM,
	/*   @     A     B     C     D     E     F     G                    71 */
    FR_AGRV, FR_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
	/*   H     I     J     K     L     M     N     O                    79*/
    KC_H, KC_I, KC_J, KC_K, KC_L, FR_M, KC_N, KC_O,
	/*   P     Q     R     S     T     U     V     W                    87 */
    KC_P, FR_Q, KC_R, KC_S, KC_T, KC_U, KC_V, FR_W,
	/*   X     Y     Z      [         \       ]       ^      _                    95*/
    KC_X, KC_Y, FR_Z, FR_LPRN, FR_UNDS, FR_RPRN, FR_CIRC, FR_UNDS,
	/*   `       a     b     c     d     e     f     g                    103*/
    FR_SUP2, FR_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
	/*   h     i     j     k     l     m     n     o                    111*/
    KC_H, KC_I, KC_J, KC_K, KC_L, FR_M, KC_N, KC_O,
	  /*    p    q     r     s     t     u     v     w                     119 */
    KC_P, FR_Q, KC_R, KC_S, KC_T, KC_U, KC_V, FR_W,
	  /*    x    y     z      {        |        }        ~    DELETE                    127*/
    KC_X, KC_Y, FR_Z, FR_APOS, FR_MINS, FR_EQL, FR_EACU, KC_DEL,



};


#endif
