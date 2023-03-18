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
