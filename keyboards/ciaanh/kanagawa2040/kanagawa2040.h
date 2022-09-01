/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#define ___ KC_NO

// clang-format off
 #define LAYOUT(  \
             K02, \
   K10, K11, K12, \
   K20, K21, K22, \
   K30, K31, K32, \
   K40, K41, K42  \
 ) \
 { \
   { ___, ___, K02 }, \
   { K10, K11, K12 }, \
   { K20, K21, K22 }, \
   { K30, K31, K32 }, \
   { K40, K41, K42 }  \
 }
// clang-format on
