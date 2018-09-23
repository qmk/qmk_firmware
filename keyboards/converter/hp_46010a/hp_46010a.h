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

/* ,---------.  ,---------------------------------------------------------.  ,---------.    ,-------------------.
 * | res|stop|  |   f1|   f2|   f3|   f4|menu|user|   f5|   f6|   f7|   f8|  |clrl|clrd|    |    |    |    |    |
 * `---------'  `---------------------------------------------------------'  `---------'    `-------------------'
 * ,------------------------------------------------------------------------..---------.    ,-------------------.
 * |     `|   1|   2|   3|   4|   5|   6|   7|   8|   9|   0|   -|   +| back||insl|dell|    |   *|   /|   +|   -|
 * |------------------------------------------------------------------------||---------|    |-------------------|
 * |     tab|   q|   w|   e|   r|   t|   y|   u|   i|   o|   p|   [|  ]|   \||insc|delc|    |   7|   8|   9|pade|
 * |------------------------------------------------------------------------||---------|    |-------------------|
 * |caps|ctrl|   a|   s|   d|   f|   g|   h|   j|   k|   l|   ;|   '|   retr|| cur|prev|    |   4|   5|   6|   ,|
 * |------------------------------------------------------------------------------------    |-------------------|
 * |dele|lshf  |   z|   x|   c|   v|   b|   n|   m|   ,|   .|   /|rshf  |sel |  up|next|    |   1|   2|   3| tab|
 * |-------------------------------------------------------------------------|---------|    |---------------    |
 * |prnt|      |lalt|              space                    |ralt|      |left|down|rght|    |        0|   .|    |
 * `-----------------------------------------------------------------------------------'    `-------------------'
 */

#define LAYOUT_HP_46010A( \
    KEY_RES, KEY_STOP, KEY_F1, KEY_F2, KEY_F3, KEY_F4,KEY_MENU,KEY_USER, KEY_F5, KEY_F6, KEY_F7, KEY_F8,                     KEY_CLRL, KEY_CLRD,   KEY_B1,   KEY_B2,  KEY_B3,  KEY_B4,   \
    KEY_GRAV,      KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINU, KEY_PLUS, KEY_BACK,       KEY_INSL, KEY_DELL,   KEY_MULT, KEY_DIV, KEY_ADD, KEY_SUBT, \
    KEY_TAB,          KEY_Q,KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LBRA, KEY_RBRA, KEY_PIPE,     KEY_INSC, KEY_DELC,   KEY_P7,   KEY_P8,  KEY_P9,  KEY_PADE, \
    KEY_CAPS, KEY_CTRL,  KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMI, KEY_QUOT,        KEY_RETR, KEY_CUR,  KEY_PREV,   KEY_P4,   KEY_P5,  KEY_P6,  KEY_PCOM, \
    KEY_DELE, KEY_LSHF,     KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMA, KEY_DOT, KEY_SLAS,KEY_RSHF, KEY_SEL,  KEY_UP,   KEY_NEXT,   KEY_P1,   KEY_P2,  KEY_P3,  KEY_PTAB, \
    KEY_PRNT,               KEY_LALT,              KEY_SPACE                    ,               KEY_RALT,          KEY_LEFT, KEY_DOWN, KEY_RGHT,        KEY_P0,       KEY_PDOT           \
) { \
    {KEY_USER,  KEY_F5,   KEY_F6,   KEY_F7,   KEY_F8,   KEY_CLRL, KEY_CLRD, KEY_MENU }, \
    {KEY_9,     KEY_0,    KEY_MINU, KEY_PLUS, KEY_BACK, KEY_INSL, KEY_DELL, KEY_8    }, \
    {KEY_O,     KEY_P,    KEY_LBRA, KEY_RBRA, KEY_PIPE, KEY_INSC, KEY_DELC, KEY_I    }, \
    {KEY_K,     KEY_L,    KEY_SEMI, KEY_QUOT, KEY_RETR, KEY_CUR,  KEY_PREV, KEY_J    }, \
    {KEY_COMA,  KEY_DOT,  KEY_SLAS, KEY_1,    KEY_SEL,  KEY_UP,   KEY_NEXT, KEY_M    }, \
    {KEY_SPACE, KEY_LALT, KEY_RALT, KC_NO,    KEY_LEFT, KEY_DOWN, KEY_RGHT, KC_NO    }, \
    {KEY_F3,    KEY_F2,   KEY_F1,   KEY_GRAV, KEY_CTRL, KEY_STOP, KEY_G,    KEY_F4   }, \
    {KEY_6,     KEY_5,    KEY_4,    KEY_3,    KEY_CAPS, KEY_RSHF, KEY_LSHF, KEY_7    }, \
    {KEY_Y,     KEY_T,    KEY_R,    KEY_E,    KEY_W,    KEY_Q,    KEY_TAB,  KEY_U    }, \
    {KEY_RES,   KEY_F,    KEY_D,    KEY_S,    KEY_A,    KC_NO,    KEY_2,    KEY_H    }, \
    {KEY_P7,    KEY_P4,   KEY_P8,   KEY_P5,   KEY_P9,   KEY_P6,   KEY_PADE, KEY_PCOM }, \
    {KEY_MULT,  KEY_P1,   KEY_DIV,  KEY_P2,   KEY_PLUS, KEY_P3,   KEY_MINU, KEY_PTAB }, \
    {KEY_B1,    KEY_P0,   KEY_B2,   KC_NO,    KEY_B3,   KEY_PDOT, KEY_B4,   KC_NO    }, \
    {KEY_B,     KEY_V,    KEY_C,    KEY_X,    KEY_Z,    KEY_PRNT, KEY_DELE, KEY_N    }, \
}

#define LAYOUT LAYOUT_HP_46010A
