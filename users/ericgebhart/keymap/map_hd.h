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
#undef ALT_TARGET_IS
#define ALT_TARGET_IS HD
// NONE, DV = dvorak, BK=Beakl, BKW=Beaklwi, HD=Hands down.
// HD_ELAN,

#ifdef HD_NEU_LAYER_ENABLE
B_LAYERt6(LANG_N(_HD_NEU), ___12_NUMBERS___, ___HD_NEU___),
#endif

#ifdef HD_NEU_NARROW_LAYER_ENABLE
  B_LAYER(LANG_N(_HD_NEU), ___10_NUMBERS___, ___HD_NEU_NARROW___),
#endif

#ifdef HD_REF_LAYER_ENABLE
  B_LAYER(LANG_N(_HD_REF), ___10_NUMBERS___, ___HD_REF___),
#endif

#ifdef HD_GOLD_LAYER_ENABLE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_T)
  B_LAYER(LANG_N(_HD_GOLD), ___10_NUMBERS___, ___HD_GOLD___),
#endif

#ifdef HD_PLATINUM_LAYER_ENABLE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_L)
  B_LAYER(LANG_N(_HD_PLATINUM), ___10_NUMBERS___, ___HD_PLATINUM___),
#endif

#ifdef HD_SILVER_LAYER_ENABLE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_N)
  B_LAYER(LANG_N(_HD_SILVER), ___10_NUMBERS___, ___HD_SILVER___),
#endif

#ifdef HD_BRONZE_LAYER_ENABLE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_H)
  B_LAYER(LANG_N(_HD_BRONZE), ___10_NUMBERS___, ___HD_BRONZE___),
#endif

#ifdef HD_ELAN_LAYER_ENABLE
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(TL_DOT)
#undef ALT_TARGET_IS
#define ALT_TARGET_IS HD_ELAN
  B_LAYER(LANG_N(_HD_ELAN), ___10_NUMBERS___, ___HD_ELAN___),
#endif

#ifdef HD_DASH_LAYER_ENABLE
#undef ALT_TARGET_IS
#define ALT_TARGET_IS HD_DASH
#undef THUMB_LETTER
#define THUMB_LETTER LANG_KC(_E)
  B_LAYER(LANG_N(_HD_DASH), ___10_NUMBERS___, ___HD_DASH___),
#endif
