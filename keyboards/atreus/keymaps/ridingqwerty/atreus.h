/* Copyright 2018 Jack Humbert
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

// 6 cols, 8 rows
// see ./keyboards/40percentclub/gherkin/gherkin.h
// top:    topological layout
// bottom: wiring matrix

#define LAYOUT( \
    K00,   K01,   K02,   K03,   K04,                 K40,   K41,   K42,   K43,   K44, \
    K10,   K11,   K12,   K13,   K14,                 K50,   K51,   K52,   K53,   K54, \
    K20,   K21,   K22,   K23,   K24,                 K60,   K61,   K62,   K63,   K64, \
    K30,   K31,   K32,   K33,   K34,   K35,   K70,   K71,   K72,   K73,   K74,   K75  \
) { \
  { K00, K01, K02, K03, K04, KC_NO }, \
  { K10, K11, K12, K13, K14, KC_NO }, \
  { K20, K21, K22, K23, K24, KC_NO }, \
  { K30, K31, K32, K33, K34, K35   }, \
  { K44, K43, K42, K41, K40, KC_NO }, \
  { K54, K53, K52, K51, K50, KC_NO }, \
  { K64, K63, K62, K61, K60, KC_NO }, \
  { K75, K74, K73, K72, K71, K70   }  \
}
