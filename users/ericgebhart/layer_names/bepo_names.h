/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
#ifdef BEPO_ENABLE
#undef LANG_IS
#define LANG_IS BEPO

#include "base_names.h"

#undef LANG_IS
#define LANG_IS DEFAULT_LANG


// ignores lang...
#ifdef BEPO_LAYER_ENABLE  // Bepo only works on bepo.
_BEPO,
#endif
#ifdef OPTIMOT_LAYER_ENABLE  // only works on bepo.
  _OPTIMOT,
#endif
#ifdef BEAKL19bis_LAYER_ENABLE  // only works on bepo.
  _BEAKL19bis,
#endif
#endif
