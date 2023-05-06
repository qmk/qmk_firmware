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
// choose your beakl,
#undef ALT_TARGET_IS
#define ALT_TARGET_IS BK // NONE, DV = dvorak, BK=Beakl, BKW=Beaklwi.

#ifdef BEAKL15_LAYER_ENABLE
B_LAYER(LANG_N(_BEAKL15), ___10_NUMBERS_BEAKL15___, ___BEAKL15___),
#endif

#ifdef BEAKL19_LAYER_ENABLE
  B_LAYER(LANG_N(_BEAKL19), ___10_NUMBERS_BEAKL19___, ___BEAKL19___),
#endif

#ifdef BEAKL27_LAYER_ENABLE
#undef ALT_TARGET_IS
#define ALT_TARGET_IS BK2 // NONE, DV = dvorak, BK=Beakl, BKW=Beaklwi.

  B_LAYER(LANG_N(_BEAKL27), ___10_NUMBERS_BEAKL19___, ___BEAKL27___),
#endif

#ifdef BEAKLWI_LAYER_ENABLE
#undef ALT_TARGET_IS
#define ALT_TARGET_IS BKW // NONE, DV = dvorak, BK=Beakl, BKW=Beaklwi.

#undef THUMBS_ARE   // change the default thumbs to WI.
#define THUMBS_ARE WIa
  B_LAYER(LANG_N(_BEAKLWI), ___10_NUMBERS_BEAKL19___, ___BEAKLWI___),
#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#endif

#undef ALT_TARGET_IS
#define ALT_TARGET_IS NONE // NONE, DV = dvorak, BK=Beakl, BKW=Beaklwi.
