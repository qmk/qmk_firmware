/*
Copyright 2021 id-b3
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
#include "id-b3.h"

#ifdef DICE_ROLLER_ENABLE
//enumerate macros
enum custom_keycodes {
  ROLL_D20 = SAFE_RANGE,
  ROLL_D100,
  ROLL_D10,
  ROLL_D8,
  ROLL_D12,
  ROLL_D6,
  ROLL_D4,
  ROLL_D3,
  PM_SCROLL,
};
#endif