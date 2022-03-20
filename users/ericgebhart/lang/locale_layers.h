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
#ifdef BEPO_ENABLE

#ifdef DVORAK_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _DVORAK_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _DVORAK_BP
#endif

#ifdef QWERTY_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _QWERTY_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _QWERTY_BP
#endif

#ifdef COLEMAK_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _COLEMAK_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _COLEMAK_BP
#endif

#ifdef BEAKL15_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _BEAKL15_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _BEAKL15_BP
#endif

#ifdef BEAKL19_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _BEAKL19_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _BEAKL19_BP
#endif

#ifdef BEAKL27_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _BEAKL27_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _BEAKL27_BP
#endif

#ifdef BEAKLWI_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _BEAKLWI_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _BEAKLWI_BP
#endif

#ifdef WORKMAN_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _WORKMAN_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _WORKMAN_BP
#endif

#ifdef NORMAN_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _NORMAN_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _NORMAN_BP
#endif

#ifdef MALTRON_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _MALTRON_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _MALTRON_BP
#endif

#ifdef EUCALYN_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _EUCALYN_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _EUCALYN_BP
#endif

#ifdef CARPLAX_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _CARPLAX_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _CARPLAX_BP
#endif

#ifdef MTGAP_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _MTGAP_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _MTGAP_BP
#endif

#ifdef HD_NEU_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _HD_NEU_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _HD_NEU_BP
#endif

#ifdef HD_REF_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _HD_REF_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _HD_REF_BP
#endif

#ifdef APT_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _APT_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _APT_BP
#endif

#ifdef BEPO_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _BEPO
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _BEPO
#endif

#ifdef OPTIMOT_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _OPTIMOT
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _OPTIMOT
#endif

#ifdef BEAKL19bis_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _BEAKL19bis
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _BEAKL19bis
#endif

#endif // bepo enabled.

// find the last en-qwerty layer. --- Assumes the layers layer is on.
#ifdef BEPO_ENABLE
#define LAST_EN_LAYER (FIRST_BEPO_LAYER - 1)
#else
#define LAST_EN_LAYER (_LAYERS - 1)
#endif

// assuming en-us will always be the first layers.
#define FIRST_EN_LAYER 0

enum locales {
  LOCALE_EN_US = 0,
#ifdef BEPO_ENABLE
  LOCALE_BEPO_FR,
#endif
  LOCALES_END,
};
