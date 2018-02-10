
/* Copyright 2016 Jonathan Nifenecker
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
/* Sendstring definitions for the bépo layout */
#ifndef SENDSTRING_BEPO
#define SENDSTRING_BEPO

#include "keymap_bepo.h"

const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
  0,        0,        0,         0,            0,          0,            0,           0,
  KC_BSPC,  KC_TAB,   KC_ENT,    0,            0,          0,            0,           0,
  0,        0,        0,         0,            0,          0,            0,           0,
  0,        0,        0,         KC_ESC,       0,          0,            0,           0,
  KC_SPC,   BP_EXLM,  BP_DQOT,   BP_HASH,      BP_DOLLAR,  BP_PERCENT,   BP_AMPR,     BP_APOS,
  BP_LPRN,  BP_RPRN,  BP_ASTR,   BP_PLUS,      BP_COMM,    BP_MINUS,     BP_DOT,      BP_SLSH,
  BP_0,     BP_1,     BP_2,      BP_3,         BP_4,       BP_5,         BP_6,        BP_7,
  BP_8,     BP_9,     BP_COLON,  BP_SCOLON,    BP_LESS,    BP_EQUAL,     BP_GREATER,  BP_QUESTION,
  BP_AT,    BP_A,     BP_B,      BP_C,         BP_D,       BP_E,         BP_F,        BP_G,
  BP_H,     BP_I,     BP_J,      BP_K,         BP_L,       BP_M,         BP_N,        BP_O,
  BP_P,     BP_Q,     BP_R,      BP_S,         BP_T,       BP_U,         BP_V,        BP_W,
  BP_X,     BP_Y,     BP_Z,      BP_LBRACKET,  BP_BSLS,    BP_RBRACKET,  BP_DCIRC,    KC_UNDS,
  BP_SLS,   BP_A,     BP_B,      BP_C,         BP_D,       BP_E,         BP_F,        BP_G,
  BP_H,     BP_I,     BP_J,      BP_K,         BP_L,       BP_M,         BP_N,        BP_O,
  BP_P,     BP_Q,     BP_R,      BP_S,         BP_T,       BP_U,         BP_V,        BP_W,
  BP_X,     BP_Y,     BP_Z,      BP_LCBR,      BP_PIPE,    BP_RCBR,      BP_TILD,     KC_DEL,
};

#endif
