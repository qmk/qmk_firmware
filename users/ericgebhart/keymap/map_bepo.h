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
// beginning of 3x12 base layers.

#undef BASE_COLS_IN_OUT
#define BASE_COLS_IN_OUT 6 // 5, 5_6, 6

#ifdef BEPO_LAYER_ENABLE
    B_LAYERt6(LANG_N(_BEPO), ___12_SYMBOLS_BEPO___, ___BEPO_3x12___),
#endif

#ifdef OPTIMOT_LAYER_ENABLE
    B_LAYERt6(LANG_N(_OPTIMOT), ___12_SYMBOLS_BEPO___, ___OPTIMOT_3x12___),
#endif

#ifdef OPTIMOT_COMPACT_LAYER_ENABLE
      B_LAYER(LANG_N(_OPTIMOT), ___10_SYMBOLS_BEPO___, ___OPTIMOT_3x10___),
#endif

#ifdef BEAKL19bis_LAYER_ENABLE
    B_LAYERt6(LANG_N(_BEAKL19bis), ___12_SYMBOLS_BEPO___, ___BEAKL19bis_3x12___),
#endif

// end of 3x12 base layers.
#undef BASE_COLS_IN_OUT
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6
