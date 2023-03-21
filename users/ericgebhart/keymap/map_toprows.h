/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
// Top Rows  commonly called Raise
#ifdef TOPROWS_LAYER_ENABLE

#  undef THUMBS_ARE
#  define THUMBS_ARE TOPROWS_LAYER_THUMBS

#  ifdef TOPROWS_BKL_15_NUMS
T_LAYER(LANG_N(_TOPROWS), ___TOPROWS_3x10___),
#  endif

#  ifdef TOPROWS_BKL_19_NUMS
  T_LAYER(LANG_N(_TOPROWS), ___TOPROWS_BKL19_3x10___),
#  endif

#  ifdef TOPROWS_MOD
  T_LAYER(LANG_N(_TOPROWS), ___TOPROWS_MOD_3x10___),
#  endif

// Not beakl numbers. Give a basic en-qwerty toprows layer.
#if !defined(TOPROWS_BKL_15_NUMS) &&            \
  !defined(TOPROWS_BKL_19_NUMS) &&              \
  !defined(TOPROWS_MOD)

  T_LAYER(LANG_N(_TOPROWS), ___RAISE_3x10___),
#endif

#  undef THUMBS_ARE
#  define THUMBS_ARE DEFAULT_THUMBS
#endif // toprows.
