/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#ifndef CANOE_H
#define CANOE_H

#include "quantum.h"

#define LAYOUT_iso( \
  K0D, K0C, K0B, K0A, K09, K08, K07, K06, K05, K04, K03, K02, K01, K00, K0E, \
  K1D, K1C, K1B, K1A, K19, K18, K17, K16, K15, K14, K13, K12, K11, K1E, \
  K2D, K2C, K2B, K2A, K29, K28, K27, K26, K25, K24, K23, K22, K10, K21, K2E, \
  K3D, K4A, K3C, K3B, K3A, K39, K38, K37, K36, K35, K34, K33, K32, K30, K3E, \
  K4D, K4C, K4B, K48, K44, K43, K42, K40, K4E \
){ \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
  { KC_NO, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
  { K30, KC_NO, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E }, \
  { K40, KC_NO, K42, K43, K44, KC_NO, KC_NO, KC_NO, K48, KC_NO, K4A, K4B, K4C, K4D, K4E }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
}

#define LAYOUT( \
  KD0, KC0, KB0, KA0, K90, K80, K70, K60, K50, K40, K30, K20, K10, K00, KE0, \
  KD1, KC1, KB1, KA1, K91, K81, K71, K61, K51, K41, K31, K21, K11, K01, KE1, \
  KD2, KC2, KB2, KA2, K92, K82, K72, K62, K52, K42, K32, K22, K12,      KE2, \
  KD3, KC3, KB3, KA3, K93, K83, K73, K63, K53, K43, K33, K23,      K03, KE3, \
  KD4, KC4, KB4,           K84,                     K44, K34, K24, K04, KE4  \
){ \
  { K00, K10, K20, K30, K40, K50, K60, K70, K80, K90, KA0, KB0, KC0, KD0, KE0 }, \
  { K01, K11, K21, K31, K41, K51, K61, K71, K81, K91, KA1, KB1, KC1, KD1, KE1 }, \
  { KC_NO, K12, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2, KC2, KD2, KE2 }, \
  { K03, KC_NO, K23, K33, K43, K53, K63, K73, K83, K93, KA3, KB3, KC3, KD3, KE3 }, \
  { K04, KC_NO, K24, K34, K44, KC_NO, KC_NO, KC_NO, K84, KC_NO, KC_NO, KB4, KC4, KD4, KE4 } \
}

#endif
