/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "charybdis.h"

// clang-format off
#define LAYOUT(                                                   \
  k00, k01, k02, k03, k04, k05,     k45, k44, k43, k42, k41, k40, \
  k10, k11, k12, k13, k14, k15,     k55, k54, k53, k52, k51, k50, \
  k20, k21, k22, k23, k24, k25,     k65, k64, k63, k62, k61, k60, \
                 k33, k34, k31,     k71, k73                      \
)                                                                 \
{                                                                 \
  {   k00,   k01,   k02,   k03,   k04,   k05 },                   \
  {   k10,   k11,   k12,   k13,   k14,   k15 },                   \
  {   k20,   k21,   k22,   k23,   k24,   k25 },                   \
  { KC_NO,   k31, KC_NO,   k33,   k34, KC_NO },                   \
  {   k40,   k41,   k42,   k43,   k44,   k45 },                   \
  {   k50,   k51,   k52,   k53,   k54,   k55 },                   \
  {   k60,   k61,   k62,   k63,   k64,   k65 },                   \
  { KC_NO,   k71, KC_NO,   k73, KC_NO, KC_NO },                   \
}
// clang-format on
