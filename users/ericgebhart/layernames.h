#pragma once
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

enum userspace_layers {
#ifdef DVORAK_LAYER_ENABLE
  _DVORAK = 0,
#endif
#ifdef QWERTY_LAYER_ENABLE
  _QWERTY,
#endif
#ifdef COLEMAK_LAYER_ENABLE
  _COLEMAK,
#endif
#ifdef BEAKL_LAYER_ENABLE
  _BEAKL,
#endif
#ifdef WORKMAN_LAYER_ENABLE
  _WORKMAN,
#endif
#ifdef NORMAN_LAYER_ENABLE
  _NORMAN,
#endif
#ifdef MALTRON_LAYER_ENABLE
  _MALTRON,
#endif
#ifdef EUCALYN_LAYER_ENABLE
  _EUCALYN,
#endif
#ifdef CARPLAX_LAYER_ENABLE
  _CARPLAX,
#endif

#ifdef BEPO_ENABLE
#ifdef DVORAK_LAYER_ENABLE
  _DVORAK_BP,
#endif
#ifdef BEAKL_LAYER_ENABLE
  _BEAKL_BP,
#endif
#ifdef BEPO_LAYER_ENABLE  // Bepo only works on bepo.
  _BEPO,
#endif
#endif
  _LAYERS, // keep this here at the end of base layers.
  _NAV,   // transient layers
  _SYMB,
#ifdef BEPO_ENABLE
  _SYMB_BP,
#endif
  _KEYPAD,
#ifdef BEPO_ENABLE
  _KEYPAD_BP,
#endif
  _TOPROWS,
#ifdef BEPO_ENABLE
  _TOPROWS_BP,
#endif
  _RGB,
  _ADJUST,
};

// Find the first and last bepo layer so we know where it is
// in the layer stack. en/qwerty goes from 0 to first bepo minus 1.
// same order as above.
#ifdef BEPO_ENABLE
#ifdef DVORAK_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _DVORAK_BP
#endif
#define LAST_BEPO_LAYER _DVORAK_BP
#endif

#ifdef BEAKL_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _BEAKL_BP
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _BEAKL_BP
#endif

#ifdef BEPO_LAYER_ENABLE
#ifndef FIRST_BEPO_LAYER
#define FIRST_BEPO_LAYER _BEPO
#endif
#undef LAST_BEPO_LAYER
#define LAST_BEPO_LAYER _BEPO
#endif
#endif // End BEPO

// find the last en-qwerty layer.
#ifdef BEPO_ENABLE
#define LAST_EN_LAYER (FIRST_BEPO_LAYER - 1)
#else
#define LAST_EN_LAYER (_LAYERS - 1)
#endif

// assuming en-us will always be the first layers.
#define FIRST_EN_LAYER 0

// Our locales. so it's easy to switch between them.
enum locales {
  LOCALE_EN_US = 0,
#ifdef BEPO_ENABLE
  LOCALE_BEPO_FR,
#endif
  LOCALES_END,
};

const uint16_t locale_layers[][2] = {
  [LOCALE_EN_US] =      {FIRST_EN_LAYER, LAST_EN_LAYER},
#ifdef BEPO_ENABLE
  [LOCALE_BEPO_FR] =    {FIRST_BEPO_LAYER, LAST_BEPO_LAYER},
#endif
};

uint32_t current_locale = 0;
#define LOCALE_LAYER_RANGE locale_layers[current_locale]
