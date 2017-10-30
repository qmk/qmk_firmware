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

#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include "quantum_keycodes.h"
#include "keycode.h"
#include "action.h"

#define KEYMAP_GRID( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, K212, \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K310, K311, K312  \
) \
{ \
  { K012, K011, K010, K09, K05, K06, K07, K08, K04, K03, K02, K01 }, \
  { K112, K111, K110, K19, K15, K16, K17, K18, K14, K13, K12, K11 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { K212, K211, K210, K29, K25, K26, K27, K28, K24, K23, K22, K21 }, \
  { K312, K311, K310, K39, K35, K36, K37, K38, K34, K33, K32, K31 }  \
}

#define KEYMAP_MIT( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, K212, \
    K31, K32, K33, K34, K35,    K3X,   K38, K39, K310, K311, K312  \
) \
{ \
  { K012, K011, K010, K09, K05, K06, K07,   K08, K04, K03, K02, K01 }, \
  { K112, K111, K110, K19, K15, K16, K17,   K18, K14, K13, K12, K11 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { K212, K211, K210, K29, K25, K26, K27,   K28, K24, K23, K22, K21 }, \
  { K312, K311, K310, K39, K35, K3X, KC_NO, K38, K34, K33, K32, K31 }  \
}

#define KEYMAP_OFFSET( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, K212, \
    K31, K32, K33, K34, K35, K36,    K3X,   K39, K310, K311, K312  \
) \
{ \
  { K012, K011, K010, K09, K05, K06, K07,   K08, K04, K03, K02, K01 }, \
  { K112, K111, K110, K19, K15, K16, K17,   K18, K14, K13, K12, K11 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { K212, K211, K210, K29, K25, K26, K27,   K28, K24, K23, K22, K21 }, \
  { K312, K311, K310, K39, K35, K36, K3X, KC_NO, K34, K33, K32, K31 }  \
}

#define KEYMAP KEYMAP_OFFSET

#endif
