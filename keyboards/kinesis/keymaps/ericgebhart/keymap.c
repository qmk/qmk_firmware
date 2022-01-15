/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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
#include "keymap_bepo.h"
#include "ericgebhart.h"

#define LAYOUT_PVARG(...)     LAYOUT_pretty(__VA_ARGS__)

// Base layers 4x10, so numbers are enabled, and a 3x10 for the keymap.
// Transient function layers are all 3x10.

#define BASE Base_4x6_4_6
#define BEPO Base_bepo_4x6_4_6
#define TRANS Transient_4x6_4_6

// tell the keymap we want to specify number rows.
// 4x10 input instead 3x10.
#define BASE_NUMBER_ROW    // turn on 4 row base templates.


#include "map.h"
