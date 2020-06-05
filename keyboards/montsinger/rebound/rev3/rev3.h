/* Copyright 2020 Ross Montsinger
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

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 * The first section contains all of the arguments representing the
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT_ortho_4x12( \
    K00, K70, K01, K71, K02, K72, K04, K74, K05, K75, K06, K76, \
    K10, K60, K11, K61, K12, K62, K14, K64, K15, K65, K16, K66, \
    K20, K50, K21, K51, K22, K52, K24, K54, K25, K55, K26, K56,\
    K30, K40, K31, K41, K32, K42, K34, K44, K35, K45, K36, K46\
    ) { \
  { K00, K01, K02, K04, KA6, KA7}, \
  { K10, K11, K12, K14, KB5, KB6, KB7 }, \
  { K20, K21, K22, K24, KC5, KC6, KC7 }, \
  { K30, K31, K32, K34, KD5, KD6, KD7 }, \
  { K40, K41, K42, K44, KE5, KE6, KE7 }, \
  { K50, K51, K52, K54, KF5, KF6, KF7 }, \
  { K60, K61, K62, K67, KG5, KG6, KG7 }, \
  { K70, K71, K72, K74, KH5, KH6, KH7 } \}

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05,      K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K42, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K43, K26, K27, K28, K29, K2A, K2B,\
    K30, K31, K32, K33, K34, K35, K44, K36, K37, K38, K39, K3A, K3B\
    ) { \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B }, \
  { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B }, \
  { KC_NO, KC_NO, K42, K43, K44, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}
