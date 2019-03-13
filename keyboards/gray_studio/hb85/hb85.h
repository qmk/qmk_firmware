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

#pragma once

#include "quantum.h"

#define LAYOUT( \
         K12,    K11, K10, K00, K01,  K02, K03, K04, K05,  K06, K07, K08, K09,  K13,            \
  K28, K27, K26, K25, K24, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K77, K76, K75,     \
  K43,   K42, K41, K40, K39, K29, K30, K31, K32, K33, K34, K35, K36,    K37, K38, K74, K73,     \
  K57,    K56, K55, K54, K53, K44, K45, K46, K47, K48, K49, K50,        K51, K52, K88, K87,     \
  K72, K71, K70, K69, K68, K58, K59, K60, K61, K62, K63, K66,      K64, K65, K67, K90, K89,     \
        K86, K85,                  K78,                 K79, K80,  K81, K82, K83, K84, K91      \
) \
{ \
  { K00  , K01  , K02  , K03  , K04  , K05  , K06  , K07  , K08  , K09  , K10  , K11  , K12  , KC_NO, K13   }, \
  { K14  , K15  , K16  , K17  , K18  , K19  , K20  , K21  , K22  , K23  , K24  , K25  , K26  , K27  , K28   }, \
  { K29  , K30  , K31  , K32  , K33  , K34  , K35  , K36  , K37  , K38  , K39  , K40  , K41  , K42  , K43   }, \
  { K44  , K45  , K46  , K47  , K48  , K49  , K50  , K51  , KC_NO, K52  , K53  , K54  , K55  , K56  , K57   }, \
  { K58  , K59  , K60  , K61  , K62  , K63  , K64  , K65  , K66  , K67  , K68  , K69  , K70  , K71  , K72   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K73  , K74  , K75  , K76  , K77  , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, K78  , KC_NO, KC_NO, K79  , K80  , K81  , K82  , K83  , K84  , KC_NO, KC_NO, K85  , K86  , KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K87  , K88  , K89  , K90  , K91  , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}


#define LAYOUT_stt( \
  K0C, K0B, K0A, K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0E,                \
  K1E, K1D, K1C, K1B, K1A, K10, K11, K12, K13, K14, K15, K16, K17, K18, K59, K58, K57, \
  K2E, K2D, K2C, K2B, K2A, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K56, K55, \
  K3E, K3D, K3C, K3B, K3A, K30, K31, K32, K33, K34, K35, K36, K37, K39, K76, K75,      \
  K4E, K4C, K4B, K4A, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K78, K77,      \
  K6D, K6C, K61, K64, K65, K67, K68, K69, K79                                          \
) \
{ \
  { K00,   K01,   K02,   K03,   K04,   K05, K06,   K07, K08,   K09,   K0A,   K0B,   K0C,   KC_NO, K0E   }, \
  { K10,   K11,   K12,   K13,   K14,   K15, K16,   K17, K18,   KC_NO, K1A,   K1B,   K1C,   K1D,   K1E   }, \
  { K20,   K21,   K22,   K23,   K24,   K25, K26,   K27, K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E   }, \
  { K30,   K31,   K32,   K33,   K34,   K35, K36,   K37, KC_NO, K39,   K3A,   K3B,   K3C,   K3D,   K3E   }, \
  { K40,   K41,   K42,   K43,   K44,   K45, K46,   K47, K48,   K49,   K4A,   K4B,   K4C,   KC_NO, K4E   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K55, K56,   K57, K58,   K59,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, K61,   KC_NO, KC_NO, K64,   K65, KC_NO, K67, K68,   K69,   KC_NO, KC_NO, K6C,   K6D,   KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K75, K76,   K77, K78,   K79,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
}
