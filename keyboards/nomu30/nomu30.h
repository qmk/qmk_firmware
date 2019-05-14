/* Copyright 2019 Naoto Takai
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
        K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
  K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110,       \
  K200, K201, K202, K203, K204, K205, K206, K207, K208                    \
) \
{ \
  { KC_NO, K001, K002, K003, K004, K005, K006, K007, K008, K009,  K010,  K011  }, \
  { K100,  K101, K102, K103, K104, K105, K106, K107, K108, K109,  K110,  KC_NO }, \
  { K200,  K201, K202, K203, K204, K205, K206, K207, K208, KC_NO, KC_NO, KC_NO }, \
}

#define LAYOUT_kc( \
        K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
  K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110,       \
  K200, K201, K202, K203, K204, K205, K206, K207, K208                    \
) \
LAYOUT( \
             KC_##K001, KC_##K002, KC_##K003, KC_##K004, KC_##K005, KC_##K006, KC_##K007, KC_##K008, KC_##K009, KC_##K010, KC_##K011, \
  KC_##K100, KC_##K101, KC_##K102, KC_##K103, KC_##K104, KC_##K105, KC_##K106, KC_##K107, KC_##K108, KC_##K109, KC_##K110,            \
  KC_##K200, KC_##K201, KC_##K202, KC_##K203, KC_##K204, KC_##K205, KC_##K206, KC_##K207, KC_##K208                                   \
)
