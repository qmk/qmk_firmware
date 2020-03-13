/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#define LAYOUT_ortho_6x4( \
    K06,  K16,  K26,  K36,  \
    K05,  K15,  K25,  K35,  \
    K04,  K14,  K24,  K34,  \
    K03,  K13,  K23,  K33,  \
    K02,  K12,  K22,  K32,  \
    K01,  K11,  K21,  K31   \
) \
{ \
  { K06, K05, K04, K03, K02, K01 }, \
  { K16, K15, K14, K13, K12, K11 }, \
  { K26, K25, K24, K23, K22, K21 }, \
  { K36, K35, K34, K33, K32, K31 }  \
}

#define LAYOUT( \
    K01, K02, K03, K04, K05, K06, \
    K11, K12, K13, K14, K15, K16, \
    K21, K22, K23, K24, K25, K26, \
    K31, K32, K33, K34, K35, K36 \
) LAYOUT_ortho_6x4( \
    K06,  K16,  K26,  K36,  \
    K05,  K15,  K25,  K35,  \
    K04,  K14,  K24,  K34,  \
    K03,  K13,  K23,  K33,  \
    K02,  K12,  K22,  K32,  \
    K01,  K11,  K21,  K31   \
)
