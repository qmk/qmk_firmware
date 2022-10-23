/*
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

#define LAYOUT_all( \
  k11,  k12, k117, k13, k14, k15, k16, k17,           k18, k19, k110, k111, k112, k113, k114, k115, k116, \
  k21,      k22,   k23, k24, k25, k26, k27,           k28, k29, k210, k211, k212, k213, k214,   k215,  \
           k32,    k33, k34, k35, k36, k37,           k38, k39, k310, k311, k312, k313, k314, k315,      \
         k41, k42, k43, k44, k45, k46, k47, k57, k58, k48, k49, k410, k411, k412,      k413,    k415, \
           k52,                   k55,    k56,        k59,                   k512,        k514, k515, k516 \
) \
{ \
  { k11,   k12, k13,   k14,   k15, k16, k17, k18, k19, k110,  k111,  k112, k113,  k114,  k115, k116,  k117 }, \
  { k21,   k22, k23,   k24,   k25, k26, k27, k28, k29, k210,  k211,  k212, k213,  k214,  k215, KC_NO, KC_NO }, \
  { KC_NO, k32, k33,   k34,   k35, k36, k37, k38, k39, k310,  k311,  k312, k313,  k314,  k315, KC_NO, KC_NO }, \
  { k41,   k42, k43,   k44,   k45, k46, k47, k48, k49, k410,  k411,  k412, k413,  KC_NO, k415, KC_NO, KC_NO }, \
  { KC_NO, k52, KC_NO, KC_NO, k55, k56, k57, k58, k59, KC_NO, KC_NO, k512, KC_NO, k514,  k515, k516,  KC_NO } \
}

#define LAYOUT_ansi( \
  k11,  k12, k117, k13, k14, k15, k16, k17,           k18, k19, k110, k111, k112, k113, k114, k115,   \
  k21,      k22,   k23, k24, k25, k26, k27,           k28, k29, k210, k211, k212, k213, k214,   k215,  \
           k32,    k33, k34, k35, k36, k37,           k38, k39, k310, k311, k312, k313,     k315,      \
         k41,      k43, k44, k45, k46, k47, k57, k58, k48, k49, k410, k411, k412,     k413,     k415, \
           k52,                   k55,    k56,        k59,                   k512,        k514, k515, k516 \
) \
{ \
  { k11,   k12,   k13,   k14,   k15, k16, k17, k18, k19, k110,  k111,  k112, k113,  k114,  k115, KC_NO,  k117 }, \
  { k21,   k22,   k23,   k24,   k25, k26, k27, k28, k29, k210,  k211,  k212, k213,  k214,  k215, KC_NO, KC_NO }, \
  { KC_NO, k32,   k33,   k34,   k35, k36, k37, k38, k39, k310,  k311,  k312, k313,  KC_NO, k315, KC_NO, KC_NO }, \
  { k41,   KC_NO, k43,   k44,   k45, k46, k47, k48, k49, k410,  k411,  k412, k413,  KC_NO, k415, KC_NO, KC_NO }, \
  { KC_NO, k52,   KC_NO, KC_NO, k55, k56, k57, k58, k59, KC_NO, KC_NO, k512, KC_NO, k514,  k515, k516, KC_NO } \
}

#define LAYOUT_split_bs( \
  k11,  k12, k117, k13, k14, k15, k16, k17,           k18, k19, k110, k111, k112, k113, k114, k115, k116,   \
  k21,      k22,   k23, k24, k25, k26, k27,           k28, k29, k210, k211, k212, k213, k214,   k215,  \
           k32,    k33, k34, k35, k36, k37,           k38, k39, k310, k311, k312, k313,     k315,      \
         k41,      k43, k44, k45, k46, k47, k57, k58, k48, k49, k410, k411, k412,     k413,     k415, \
           k52,                   k55,    k56,        k59,                   k512,        k514, k515, k516 \
) \
{ \
  { k11,   k12,   k13,   k14,   k15, k16, k17, k18, k19, k110,  k111,  k112, k113,  k114,  k115, k116,  k117 }, \
  { k21,   k22,   k23,   k24,   k25, k26, k27, k28, k29, k210,  k211,  k212, k213,  k214,  k215, KC_NO, KC_NO }, \
  { KC_NO, k32,   k33,   k34,   k35, k36, k37, k38, k39, k310,  k311,  k312, k313,  KC_NO, k315, KC_NO, KC_NO }, \
  { k41,   KC_NO, k43,   k44,   k45, k46, k47, k48, k49, k410,  k411,  k412, k413,  KC_NO, k415, KC_NO, KC_NO }, \
  { KC_NO, k52,   KC_NO, KC_NO, k55, k56, k57, k58, k59, KC_NO, KC_NO, k512, KC_NO, k514,  k515, k516, KC_NO } \
}

#define LAYOUT_iso( \
  k11,  k12, k117, k13, k14, k15, k16, k17,           k18, k19, k110, k111, k112, k113, k114,   k115,    \
  k21,      k22,   k23, k24, k25, k26, k27,           k28, k29, k210, k211, k212, k213, k214,          \
           k32,    k33, k34, k35, k36, k37,           k38, k39, k310, k311, k312, k313, k314, k315,    \
         k41, k42, k43, k44, k45, k46, k47, k57, k58, k48, k49, k410, k411, k412,     k413,     k415, \
           k52,                   k55,    k56,        k59,                   k512,        k514, k515, k516 \
) \
{ \
  { k11,   k12, k13,   k14,   k15, k16, k17, k18, k19, k110,  k111,  k112, k113,  k114,  k115,  KC_NO,  k117 }, \
  { k21,   k22, k23,   k24,   k25, k26, k27, k28, k29, k210,  k211,  k212, k213,  k214,  KC_NO, KC_NO, KC_NO }, \
  { KC_NO, k32, k33,   k34,   k35, k36, k37, k38, k39, k310,  k311,  k312, k313,  k314,  k315,  KC_NO, KC_NO }, \
  { k41,   k42, k43,   k44,   k45, k46, k47, k48, k49, k410,  k411,  k412, k413,  KC_NO, k415,  KC_NO, KC_NO }, \
  { KC_NO, k52, KC_NO, KC_NO, k55, k56, k57, k58, k59, KC_NO, KC_NO, k512, KC_NO, k514,  k515,  k516,  KC_NO } \
}
