/*
Copyright 2018 Jumail Mundekkat / MxBlue

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

#define LAYOUT( \
  K11,      K31, K41, K51, K61,      K81, K91, KA1, KB1,      KC1, K01, KD1, K21,      K20, K30, K00, \
                                                                                                      \
  K12, K22, K32, K42, K52, K62,  K72,  K82,  K92,  KA2,  KB2, KC2, K02,   KD2   ,      K70, K60, K50, \
   K13  , K23, K33, K43, K53, K63,  K73,  K83,  K93,  KA3,  KB3, KC3, K03,  KD3 ,      KD0, K90, K80, \
     K15  , K25, K35, K45, K55, K65,  K75,  K85,  K95,  KA5,  KB5, KC5,   K05   ,                     \
      K16  , K26, K36, K46, K56, K66,  K76,  K86,  K96,  KA6,  KB6,   KC6  , K06,           KD6,      \
  K17 , K27 , K37 ,                K57                  , K97 , KA7 , KB7 , KC7 ,      K07, KD7, K87  \
){ \
  { K00,   KC_NO, K20,   K30,   KC_NO, K50,   K60,   K70,   K80,   K90,   KC_NO, KC_NO, KC_NO, KD0   }, \
  { K01,   K11,   K21,   K31,   K41,   K51,   K61,   KC_NO, K81,   K91,   KA1,   KB1,   KC1,   KD1   }, \
  { K02,   K12,   K22,   K32,   K42,   K52,   K62,   K72,   K82,   K92,   KA2,   KB2,   KC2,   KD2   }, \
  { K03,   K13,   K23,   K33,   K43,   K53,   K63,   K73,   K83,   K93,   KA3,   KB3,   KC3,   KD3   }, \
  { K05,   K15,   K25,   K35,   K45,   K55,   K65,   K75,   K85,   K95,   KA5,   KB5,   KC5,   KC_NO }, \
  { K06,   K16,   K26,   K36,   K46,   K56,   K66,   K76,   K86,   K96,   KA6,   KB6,   KC6,   KD6   }, \
  { K07,   K17,   K27,   K37,   KC_NO, K57,   KC_NO, KC_NO, K87,   K97,   KA7,   KB7,   KC7,   KD7   }  \
}
