/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2022 Kemal Akkoyun <kakkoyun@gmail.com> (@kakkoyun)
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
#define LAYOUT_charybdis_5x6(                                                            \
  k00, k01, k02, k03, k04, k05,                            k65, k64, k63, k62, k61, k60, \
  k10, k11, k12, k13, k14, k15,                            k75, k74, k73, k72, k71, k70, \
  k20, k21, k22, k23, k24, k25,                            k85, k84, k83, k82, k81, k80, \
  k30, k31, k32, k33, k34, k35,                            k95, k94, k93, k92, k91, k90, \
            k42, k43,                                                k103, k102,         \
                      k44, k45,                                                          \
                                k54, k55,            k113,                                     \
                                k52, k53,      k114, k115                                \
)                                                                 \
{                                                                 \
  {   k00,   k01,   k02,   k03,   k04,   k05 },                   \
  {   k10,   k11,   k12,   k13,   k14,   k15 },                   \
  {   k20,   k21,   k22,   k23,   k24,   k25 },                   \
  {   k30,   k31,   k32,   k33,   k34,   k35 },                   \
  { KC_NO, KC_NO,   k42,   k43,   k44,   k45 },                   \
  { KC_NO, KC_NO,   k52,   k53,   k54,   k55 },                   \
\
  {   k60,   k61,   k62,   k63,   k64,   k65 },                   \
  {   k70,   k71,   k72,   k73,   k74,   k75 },                   \
  {   k80,   k81,   k82,   k83,   k84,   k85 },                   \
  {   k90,   k91,   k92,   k93,   k94,   k95 },                   \
  { KC_NO, KC_NO,  k102,  k103, KC_NO, KC_NO },                   \
  { KC_NO, KC_NO, KC_NO,  k113,  k114,  k115 },                   \
}
// clang-format on
