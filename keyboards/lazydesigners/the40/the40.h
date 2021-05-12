/*
 Copyright 2020 LAZYDESIGNERS

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

#define LAYOUT_all( \
    K000,    K001,   K002,   K003,   K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011,  \
    K100,    K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,          \
    K200,    K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,          \
    K300,    K301,   K302,           K304,           K306,           K308,   K309,   K310           \
) \
{ \
  { K000,   K001,   K002,   K003,   K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011  }, \
  { K100,   K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,   KC_NO }, \
  { K200,   K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,   KC_NO }, \
  { K300,   K301,   K302,   KC_NO,  K304,   KC_NO,  K306,   KC_NO,  K308,   K309,   K310,   KC_NO }, \
}

#define LAYOUT_ortho( \
    K000,    K001,   K002,   K003,   K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011,  \
    K100,    K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,   K111,  \
    K200,    K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,   K211,  \
    K300,    K301,   K302,   K303,   K304,   K305,   K306,   K307,   K308,   K309,   K310,   K311   \
) \
{ \
  { K000,   K001,   K002,   K003,   K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011  }, \
  { K100,   K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,   K111  }, \
  { K200,   K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,   K211  }, \
  { K300,   K301,   K302,   K303,   K304,   K305,   K306,   K307,   K308,   K309,   K310,   K311  }, \
}

#define LAYOUT_wkl( \
    K000,    K001,   K002,   K003,   K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011,  \
    K100,    K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,          \
    K200,    K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,          \
    K300,            K302,           K304,           K306,           K308,           K310           \
) \
{ \
  { K000,   K001,   K002,   K003,   K004,   K005,   K006,   K007,   K008,   K009,   K010,   K011  }, \
  { K100,   K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,   KC_NO }, \
  { K200,   K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,   KC_NO }, \
  { K300,   K301,   K302,   KC_NO,  K304,   KC_NO,  K306,   KC_NO,  K308,   K309,   K310,   KC_NO }, \
}
