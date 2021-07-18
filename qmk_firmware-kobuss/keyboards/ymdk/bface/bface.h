/*
Copyright 2019 Ethan Durrant (emdarcher)

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

#define LAYOUT_all(\
  K04, K14, K24, K34, K44, K54, K64, K74, K84, K94, KA4, KB4, KC4, KD4, KE4, \
  K03, K13, K23, K33, K43, K53, K63, K73, K83, K93, KA3, KB3,  KC3,  KD3, \
  K02, K12, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2,  KC2,    KD2, \
  K01, K11,   K21, K31, K41, K51, K61, K71, K81, K91, KA1, KB1,  KC1, KD1, KE1, \
  K00,    K10,     K20,  K30,         K70,          K80,   K90, KA0, KB0, KC0, KD0  \
){ \
  { K00,   K10,   K20,   K30,   KC_NO, KC_NO, KC_NO,K70,    K80,    K90,    KA0,   KB0,   KC0,   KD0,   KC_NO }, \
  { K01,   K11,   K21,   K31,   K41,   K51,   K61,  K71,    K81,    K91,    KA1,   KB1,   KC1,   KD1,   KE1 }, \
  { K02,   K12,   K22,   K32,   K42,   K52,   K62,  K72,    K82,    K92,    KA2,   KB2,   KC2,   KD2,   KC_NO }, \
  { K03,   K13,   K23,   K33,   K43,   K53,   K63,  K73,    K83,    K93,    KA3,   KB3,   KC3,   KD3,   KC_NO }, \
  { K04,   K14,   K24,   K34,   K44,   K54,   K64,  K74,    K84,    K94,    KA4,   KB4,   KC4,   KD4,   KE4   }, \
}
//   0      1      2      3      4      5       6      7      8     9       A      B      C      D     E
//   A0     A1     A2     A3     A4     A5     A6      A7     C7    C6      C5     C4     C3     C2    D7

#define LAYOUT_60_ansi(\
  K04, K14, K24, K34, K44, K54, K64, K74, K84, K94, KA4, KB4, KC4, KE4, \
  K03, K13, K23, K33, K43, K53, K63, K73, K83, K93, KA3, KB3, KC3,    KD3, \
  K02, K12, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2,     KD2, \
  K01,    K21, K31, K41, K51, K61, K71, K81, K91, KA1, KB1,  KD1,  \
  K00,    K10,     K20,           K70,                K90, KA0, KC0, KD0  \
){ \
  { K00,   K10,   K20,   KC_NO, KC_NO, KC_NO, KC_NO, K70, KC_NO,    K90,    KA0,   KC_NO, KC0,   KD0,   KC_NO }, \
  { K01,   KC_NO, K21,   K31,   K41,   K51,   K61,  K71,    K81,    K91,    KA1,   KB1,   KC_NO, KD1,   KC_NO }, \
  { K02,   K12,   K22,   K32,   K42,   K52,   K62,  K72,    K82,    K92,    KA2,   KB2,   KC_NO, KD2,   KC_NO }, \
  { K03,   K13,   K23,   K33,   K43,   K53,   K63,  K73,    K83,    K93,    KA3,   KB3,   KC3,   KD3,   KC_NO }, \
  { K04,   K14,   K24,   K34,   K44,   K54,   K64,  K74,    K84,    K94,    KA4,   KB4,   KC4,   KC_NO, KE4   }, \
}
//   0      1      2      3      4      5       6      7      8     9       A      B      C      D     E
//   A0     A1     A2     A3     A4     A5     A6      A7     C7    C6      C5     C4     C3     C2    D7

#define LAYOUT_60_ansi_split_rshift(\
  K04, K14, K24, K34, K44, K54, K64, K74, K84, K94, KA4, KB4, KC4, KE4, \
  K03, K13, K23, K33, K43, K53, K63, K73, K83, K93, KA3, KB3,  KC3,  KD3, \
  K02, K12, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2,      KD2, \
  K01,    K21, K31, K41, K51, K61, K71, K81, K91, KA1, KB1,  KD1,  KE1, \
  K00,    K10,     K20,           K70,                K90, KA0, KC0, KD0  \
){ \
  { K00,   K10,   K20,   KC_NO, KC_NO, KC_NO, KC_NO, K70, KC_NO,    K90,    KA0,   KC_NO, KC0,   KD0,   KC_NO }, \
  { K01,   KC_NO, K21,   K31,   K41,   K51,   K61,  K71,    K81,    K91,    KA1,   KB1,   KC_NO, KD1,   KE1 }, \
  { K02,   K12,   K22,   K32,   K42,   K52,   K62,  K72,    K82,    K92,    KA2,   KB2,   KC_NO, KD2,   KC_NO }, \
  { K03,   K13,   K23,   K33,   K43,   K53,   K63,  K73,    K83,    K93,    KA3,   KB3,   KC3,   KD3,   KC_NO }, \
  { K04,   K14,   K24,   K34,   K44,   K54,   K64,  K74,    K84,    K94,    KA4,   KB4,   KC4,   KC_NO, KE4   }, \
}
//   0      1      2      3      4      5       6      7      8     9       A      B      C      D     E
//   A0     A1     A2     A3     A4     A5     A6      A7     C7    C6      C5     C4     C3     C2    D7

