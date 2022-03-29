#pragma once
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
// kind of brutish. - make sure they are in the same order.
// Find the first and last bepo layer so we know where it is
// in the layer stack. en/qwerty goes from 0 to first bepo minus 1.
// same order as above.
#ifdef SECOND_LOCALE
#undef LANG_IS
#define LANG_IS SECOND_LOCALE

#ifdef DVORAK_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_DVORAK)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_DVORAK)
#endif

#ifdef QWERTY_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_QWERTY)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_QWERTY)
#endif

#ifdef COLEMAK_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_COLEMAK)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_COLEMAK)
#endif

#ifdef COLEMAK_DH_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_COLEMAK_DH)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_COLEMAK_DH)
#endif

#ifdef BEAKL15_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_BEAKL15)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_BEAKL15)
#endif

#ifdef BEAKL19_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_BEAKL19)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_BEAKL19)
#endif

#ifdef BEAKL27_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_BEAKL27)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_BEAKL27)
#endif

#ifdef BEAKLWI_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_BEAKLWI)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_BEAKLWI)
#endif

#ifdef WORKMAN_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_WORKMAN)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_WORKMAN)
#endif

#ifdef NORMAN_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_NORMAN)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_NORMAN)
#endif

#ifdef MALTRON_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_MALTRON)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_MALTRON)
#endif

#ifdef EUCALYN_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_EUCALYN)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_EUCALYN)
#endif

#ifdef CARPLAX_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_CARPLAX)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_CARPLAX)
#endif

#ifdef APT_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_APT)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_APT)
#endif

#ifdef MTGAP_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_MTGAP)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_MTGAP)
#endif

#ifdef HD_NEU_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_NEU)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_NEU)
#endif

#ifdef HD_NEU_NARROW_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_NEU_NARROW)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_NEU_NARROW)
#endif

#ifdef HD_GOLD_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_GOLD)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_GOLD)
#endif

#ifdef HD_PLATINUM_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_PLATINUM)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_PLATINUM)
#endif

#ifdef HD_SILVER_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_SILVER)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_SILVER)
#endif

#ifdef HD_BRONZE_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_BRONZE)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_BRONZE)
#endif

#ifdef HD_ELAN_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_ELAN)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_ELAN)
#endif

#ifdef HD_DASH_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_DASH)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_DASH)
#endif

#ifdef HD_REF_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_HD_REF)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_HD_REF)
#endif

#ifdef BEPO_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_BEPO)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_BEPO)
#endif

#ifdef OPTIMOT_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_OPTIMOT)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_OPTIMOT)
#endif

#ifdef BEAKL19bis_LAYER_ENABLE
#ifndef FIRST_LOC_LAYER
#define FIRST_LOC_LAYER LANG_N(_BEAKL19bis)
#endif
#undef LAST_LOC_LAYER
#define LAST_LOC_LAYER LANG_N(_BEAKL19bis)
#endif

#undef LANG_IS
#define LANG_IS DEFAULT_LANG

#endif // second locale enabled.

// find the last en-qwerty base layer. --- Assumes the layers layer is on.
#ifdef SECOND_LOCALE
#define LAST_EN_LAYER (FIRST_LOC_LAYER - 1)
#else
#define LAST_EN_LAYER (_LAYERS - 1)
#endif

// assuming en-us will always be the first layers.
#define FIRST_EN_LAYER 0
#define LOCALE_NAME CAT(LOCALE_, SECOND_LOCALE)

enum locales {
  LOCALE_EN_US = 0,
#ifdef SECOND_LOCALE
  LOCALE_NAME,
#endif
  LOCALES_END,
};
