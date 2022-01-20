 /* Copyright 2020 Andrew Kannan
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

#define LAYOUT_default( \
    k11, k12, k13, k14, k15, k16, k17, k18, k69, k610, k611, k612, k613, k614, k615, k616, \
    k21, k22, k23, k24, k25, k26, k27, k78, k79, k710, k711, k712, k713, k714, k715, \
    k31, k32, k33, k34, k35, k36, k37, k88, k89, k810, k811, k812, k813, k814, k815, k816, \
    k41, k42, k43, k44, k45, k46, k47, k48, k99, k910, k911, k912, k913, k914, k915, k916, \
    k51, k52, k57, k58, k109, k1010, k1014, k1015, k1016 \
) { \
	{ k11, k12, k13, k14, k15, k16, k17, k18, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ k21, k22, k23, k24, k25, k26, k27, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ k31, k32, k33, k34, k35, k36, k37, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ k41, k42, k43, k44, k45, k46, k47, k48, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ k51, k52, KC_NO, KC_NO, KC_NO, KC_NO, k57, k58, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },  \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k69, k610, k611, k612, k613, k614, k615, k616 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k78, k79, k710, k711, k712, k713, k714, k715, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k88, k89, k810, k811, k812, k813, k814, k815, k816 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k99, k910, k911, k912, k913, k914, k915, k916 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k109, k1010, KC_NO, KC_NO, KC_NO, k1014, k1015, k1016 }\
}
