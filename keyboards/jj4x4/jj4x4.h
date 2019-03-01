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

void matrix_init_user(void);  // TODO port this to other PS2AVRGB boards
	
#define LAYOUT_ortho_4x4( \
	K01, K02, K03, K04, \
	K11, K12, K13, K14, \
	K21, K22, K23, K24, \
	K31, K32, K33, K34 \
) \
{ \
  { K01, K02, K03, K04 }, \
  { K11, K12, K13, K14 }, \
  { K21, K22, K23, K24 }, \
  { K31, K32, K33, K34 } \
}	
