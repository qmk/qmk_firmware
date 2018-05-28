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

#define KNO KC_NO

#include "quantum.h"

#define LAYOUT( \
  KD0, KC0, KB0, KA0, K90, K80, K70, K60, K50, K40, K30, K20, K10, K00, KE0, \
  KD1, KC1, KB1, KA1, K91, K81, K71, K61, K51, K41, K31, K21, K11, K01, KE1, \
  KD2, KC2, KB2, KA2, K92, K82, K72, K62, K52, K42, K32, K22, K12,      KE2, \
  KD3, KC3, KB3, KA3, K93, K83, K73, K63, K53, K43, K33, K23,      K03, KE3, \
  KD4, KC4, KB4,           K84,                     K44, K34, K24, K04, KE4  \
){ \
  { K00, K10, K20, K30, K40, K50, K60, K70, K80, K90, KA0, KB0, KC0, KD0, KE0 }, \
  { K01, K11, K21, K31, K41, K51, K61, K71, K81, K91, KA1, KB1, KC1, KD1, KE1 }, \
  { KNO, K12, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2, KC2, KD2, KE2 }, \
  { K03, KNO, K23, K33, K43, K53, K63, K73, K83, K93, KA3, KB3, KC3, KD3, KE3 }, \
  { K04, KNO, K24, K34, K44, KNO, KNO, KNO, K84, KNO, KNO, KB4, KC4, KD4, KE4 } \
}

#endif
