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

#ifndef FACEW_H
#define FACEW_H

#include "quantum.h"

#define LAYOUT_all( \
  K61, K71, K72, K73, K74, K64, K65, K75, K76, K77, K78, K68, K66, K10, K60,\
   K11, K01, K02, K03, K04, K14, K15, K05, K06, K07, K08, K18, K16,  K20,   \
    K12, K21, K22, K23, K24, K34, K35, K25, K26, K27, K28, K38, K48,  K40,  \
  K19, K13, K41, K42, K43, K44, K54, K55, K45, K46, K47, K58,   K49,    K50,\
  K09,   K00,   K39,           K30,                 K59,   K69,   K57,   K29\
){ \
  { KC_NO, K01,   K02,   K03,   K04, K05, K06,   K07,   K08,   K09,   K00},   \
  { KC_NO, K11,   K12,   K13,   K14, K15, K16,   KC_NO, K18,   K19,   K10},   \
  { KC_NO, K21,   K22,   K23,   K24, K25, K26,   K27,   K28,   K29,   K20},   \
  { KC_NO, KC_NO, KC_NO, KC_NO, K34, K35, KC_NO, KC_NO, K38,   K39,   K30},   \
  { KC_NO, K41,   K42,   K43,   K44, K45, K46,   K47,   K48,   K49,   K40},   \
  { KC_NO, KC_NO, KC_NO, KC_NO, K54, K55, KC_NO, K57,   K58,   K59,   K50},   \
  { KC_NO, K61,   KC_NO, KC_NO, K64, K65, K66,   KC_NO, K68,   K69,   K60},   \
  { KC_NO, K71,   K72,   K73,   K74, K75, K76,   K77,   K78,   KC_NO, KC_NO}, \
}

#define LAYOUT_60_ansi( \
  K61, K71, K72, K73, K74, K64, K65, K75, K76, K77, K78, K68, K66,      K60,\
   K11, K01, K02, K03, K04, K14, K15, K05, K06, K07, K08, K18, K16,  K20,   \
    K12, K21, K22, K23, K24, K34, K35, K25, K26, K27, K28, K38,   K40,      \
  K19,      K41, K42, K43, K44, K54, K55, K45, K46, K47, K58,   K49,        \
  K09,   K00,   K39,           K30,                 K59,   K69,   K57,   K29\
){ \
  { KC_NO, K01,   K02,   K03,   K04, K05, K06,   K07,   K08,   K09,   K00},   \
  { KC_NO, K11,   K12,   KC_NO, K14, K15, K16,   KC_NO, K18,   K19,   KC_NO}, \
  { KC_NO, K21,   K22,   K23,   K24, K25, K26,   K27,   K28,   K29,   K20},   \
  { KC_NO, KC_NO, KC_NO, KC_NO, K34, K35, KC_NO, KC_NO, K38,   K39,   K30},   \
  { KC_NO, K41,   K42,   K43,   K44, K45, K46,   K47,   KC_NO, K49,   K40},   \
  { KC_NO, KC_NO, KC_NO, KC_NO, K54, K55, KC_NO, K57,   K58,   K59,   KC_NO}, \
  { KC_NO, K61,   KC_NO, KC_NO, K64, K65, K66,   KC_NO, K68,   K69,   K60},   \
  { KC_NO, K71,   K72,   K73,   K74, K75, K76,   K77,   K78,   KC_NO, KC_NO}, \
}

#endif
