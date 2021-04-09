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
    K20, K50, K21, K51, K22, K52, K24, K54, K25, K55, K26, K56, \
    K30, K40, K31, K41, K32, K42, K34, K44, K35, K45, K36, K46  \
    ) { \
  { K00, K01, K02, KC_NO, K04, K05, K06}, \
  { K10, K11, K12, KC_NO, K14, K15, K16}, \
  { K20, K21, K22, KC_NO, K24, K25, K26}, \
  { K30, K31, K32, KC_NO, K34, K35, K36}, \
  { K40, K41, K42, KC_NO, K44, K45, K46}, \
  { K50, K51, K52, KC_NO, K54, K55, K56}, \
  { K60, K61, K62, KC_NO, K64, K65, K66}, \
  { K70, K71, K72, KC_NO, K74, K75, K76}  \
}

#define LAYOUT_all( \
    K00, K70, K01, K71, K02, K72,      K04, K74, K05, K75, K06, K76, \
    K10, K60, K11, K61, K12, K62, K13, K14, K64, K15, K65, K16, K66, \
    K20, K50, K21, K51, K22, K52, K23, K24, K54, K25, K55, K26, K56,\
    K30, K40, K31, K41, K32, K42, K33, K34, K44, K35, K45, K36, K46\
    ) { \
  { K00, K01, K02, KC_NO, K04, K05, K06}, \
  { K10, K11, K12, K13, K14, K15, K16}, \
  { K20, K21, K22, K23, K24, K25, K26}, \
  { K30, K31, K32, K33, K34, K35, K36}, \
  { K40, K41, K42, KC_NO, K44, K45, K46}, \
  { K50, K51, K52, KC_NO, K54, K55, K56}, \
  { K60, K61, K62, KC_NO, K64, K65, K66}, \
  { K70, K71, K72, KC_NO, K74, K75, K76} \
}

