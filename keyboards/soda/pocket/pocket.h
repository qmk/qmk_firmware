/*
Copyright 2015 Álvaro "Gondolindrim" Volpato  <gondolindrim@acheronproject.com>

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

#define ___ KC_NO

#define LAYOUT( \
     K00, K01, K02, K03, K04, K05, K06, \
     K10, K11, K12, K13, K14, K15, K16, \
     K20, K21, K22, K23, K24, K25,      \
                    K33, K34, K35, K36, \
          K41,      K43, K44, K45,      \
     K50, K51, K52,      K54, K55, K56  \
) { \
     { K00,   K01,   K02,   K03,   K04,   K05,   K06 }, \
     { K10,   K11,   K12,   K13,   K14,   K15,   K16 }, \
     { K20,   K21,   K22,   K23,   K24,   K25,   KC_NO}, \
     { KC_NO, KC_NO, KC_NO, K33,   K34,   K35,   K36 }, \
     { KC_NO, K41,   KC_NO, K43,   K44,   K45,   KC_NO}, \
     { K50,   K51,   K52,   KC_NO, K54,   K55,   K56 }  \
}

