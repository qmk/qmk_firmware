/*
Copyright 2021 Salicylic_Acid
Copyright 2022 jun10000

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define LAYOUT( \
    L01, L05, L10, L15, L20, L25, L30, L35, L40, R45, R50, R55, R60, R65, \
         L06, L11, L16, L21, L26, L31, L36, R41, R46, R51, R56, R61, R66, \
    L02, L07, L12, L17, L22, L27, L32, L37, R42, R47, R52, R57, R62, R67, \
    L03, L08, L13, L18, L23, L28, L33, L38, R43, R48, R53, R58, R63, R68, \
    L04, L09, L14, L19, L24, L29, L34, L39, R44, R49, R54, R59, R64, R69  \
  ) \
  { \
    {   L01,   L06,   L11,   L16,   L21,   L26,   L31,   L36 }, \
    {   L02,   L07,   L12,   L17,   L22,   L27,   L32,   L37 }, \
    {   L03,   L08,   L13,   L18,   L23,   L28,   L33,   L38 }, \
    {   L04,   L09,   L14,   L19,   L24,   L29,   L34,   L39 }, \
    {   L05,   L10,   L15,   L20,   L25,   L30,   L35,   L40 }, \
    {   R41,   R46,   R51,   R56,   R61,   R66, KC_NO, KC_NO }, \
    {   R42,   R47,   R52,   R57,   R62,   R67, KC_NO, KC_NO }, \
    {   R43,   R48,   R53,   R58,   R63,   R68, KC_NO, KC_NO }, \
    {   R44,   R49,   R54,   R59,   R64,   R69, KC_NO, KC_NO }, \
    {   R45,   R50,   R55,   R60,   R65, KC_NO, KC_NO, KC_NO }  \
  }
