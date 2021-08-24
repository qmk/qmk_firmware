/*
Copyright 2018 listofoptions <listofoptions@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

/*
 * ,-------.  ,--------------------------------------------------------------------------.
 * | F1| F2|  |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  BS  |NumLck |ScrLck |
 * |-------|  |--------------------------------------------------------------------------|
 * | F3| F4|  | Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ] |   |  7|  8|  9|  -|
 * |-------|  |------------------------------------------------------|Ent|---------------|
 * | F5| F6|  | Ctrl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|   |  4|  5|  6|   |
 * |-------|  |----------------------------------------------------------------------|   |
 * | F7| F8|  |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift|PrS|  1|  2|  3|  +|
 * |-------|  |----------------------------------------------------------------------|   |
 * | F9|F10|  |  Alt  |               Space                  |CapsLck|   0   |   .   |   |
 * `-------'  `--------------------------------------------------------------------------'
*/

#define LAYOUT_5291( \
    KEY_F1,KEY_F2,  KEY_ESC, KEY_1,   KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,   KEY_0,   KEY_MIN, KEY_EQU,  KEY_BACK,         KEY_NLOCK,         KEY_SLOCK, \
    KEY_F3,KEY_F4,  KEY_TAB, KEY_Q,   KEY_W,KEY_E,KEY_R,KEY_T,KEY_Y,KEY_U,KEY_I,KEY_O,   KEY_P,   KEY_LBRC,KEY_RBRC,          KEY_PAD7,KEY_PAD8, KEY_PAD9,KEY_PMIN,  \
    KEY_F5,KEY_F6,  KEY_LCTR,KEY_A,   KEY_S,KEY_D,KEY_F,KEY_G,KEY_H,KEY_J,KEY_K,KEY_L,   KEY_SEMI,KEY_QUOT,KEY_TICK, KEY_ENTR,KEY_PAD4,KEY_PAD5, KEY_PAD6,           \
    KEY_F7,KEY_F8,  KEY_LSFS,KEY_BSLS,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KEY_N,KEY_M,KEY_COMM,KEY_DOT, KEY_SLS,KEY_RSFS, KEY_PAST,KEY_PAD1,KEY_PAD2, KEY_PAD3,KEY_PPLS,  \
    KEY_F9,KEY_F10, KEY_LALT,                              KEY_SPACE,                                     KEY_CLOCK,         KEY_PAD0,          KEY_PDOT            \
) \
{ {KEY_Z,     KEY_S,   KEY_W,   KEY_3     }\
, {KEY_X,     KEY_D,   KEY_E,   KEY_4     }\
, {KEY_C,     KEY_F,   KEY_R,   KEY_5     }\
, {KEY_V,     KEY_G,   KEY_T,   KEY_6     }\
, {KEY_B,     KEY_H,   KEY_Y,   KEY_7     }\
, {KEY_N,     KEY_J,   KEY_U,   KEY_8     }\
, {KEY_PAD2,  KEY_PAD5,KEY_PAD8,KEY_NLOCK }\
, {KEY_M,     KEY_K,   KEY_I,   KEY_9     }\
, {KEY_COMM,  KEY_L,   KEY_O,   KEY_0     }\
, {KEY_DOT,   KEY_SEMI,KEY_P,   KEY_MIN   }\
, {KEY_SLS,   KEY_QUOT,KEY_LBRC,KEY_EQU   }\
, {KEY_SPACE, KEY_RSFS,KEY_TICK,KEY_RBRC  }\
, {KEY_CLOCK, KEY_PAST,KEY_ENTR,KEY_BACK  }\
, {KEY_PAD0,  KEY_PAD1,KEY_PAD4,KEY_PAD7  }\
, {KEY_PPLS,  KC_NO,   KEY_PMIN,KEY_SLOCK }\
, {KEY_PDOT,  KEY_PAD3,KEY_PAD6,KEY_PAD9  }\
, {KEY_BSLS,  KEY_A,   KEY_Q,   KEY_2     }\
, {KEY_LALT,  KC_NO,   KC_NO,   KEY_1     }\
, {KEY_F7,    KEY_F5,  KEY_F3,  KEY_F1    }\
, {KEY_F8,    KEY_F6,  KEY_F4,  KEY_F2    }\
, {KC_F10,    KC_NO,   KC_NO,   KC_NO     }\
, {KC_F9,     KC_NO,   KC_NO,   KC_NO     }\
, {KEY_LSFS,  KEY_LCTR,KEY_TAB, KEY_ESC   }\
, {KC_NO,     KC_NO,   KC_NO,   KC_NO     }\
}

#define LAYOUT LAYOUT_5291