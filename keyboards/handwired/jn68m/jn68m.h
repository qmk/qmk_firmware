/* Copyright 2018 Jumail Mundekkat / MxBlue
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
#ifndef JN68M_H
#define JN68M_H

#include "quantum.h"

#define LAYOUT( \
  K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10, K11, K12, K13, K14,      K67, K68,\
  K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29,      K69, K70,\
  K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41, K42, \
  K43, K44, K45, K46, K47, K48, K49, K50, K51, K52,      K53, K54,           K55, \
  K56, K57, K58,           K59,                K60,      K61, K63,      K64, K65, K66 \
) { \
  { K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10, K11, K12, K13, K14, K67, K68 }, \
  { K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K69, K70 }, \
  { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41, K42,KC_NO,KC_NO,KC_NO}, \
  { K43, K44, K45, K46, K47, K48, K49, K50, K51, K52,KC_NO,K53, K54,KC_NO,K55,KC_NO}, \
  { K56, K57, K58,KC_NO,KC_NO,K59,KC_NO,KC_NO,KC_NO,K60,KC_NO,K61, K63, K64, K65, K66} \
}

#define LAYOUT_splitbs( \
  K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10, K11, K12, K13, K14, K15,      K67, K68,\
  K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29,           K69, K70,\
  K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41, K42, \
  K43, K44, K45, K46, K47, K48, K49, K50, K51, K52,      K53, K54,                K55, \
  K56, K57, K58,           K59,                K60,      K61, K63,           K64, K65, K66 \
) { \
  { K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10, K11, K12, K13, K14, K67, K68 }, \
  { K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K69, K70 }, \
  { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41, K42, K15,KC_NO,KC_NO}, \
  { K43, K44, K45, K46, K47, K48, K49, K50, K51, K52,KC_NO,K53, K54,KC_NO,K55,KC_NO}, \
  { K56, K57, K58,KC_NO,KC_NO,K59,KC_NO,KC_NO,KC_NO,K60,KC_NO,K61, K63, K64, K65, K66} \
}

#endif
