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

#ifndef ericgebhart
#define ericgebhart

#include QMK_KEYBOARD_H
#include "core_keysets.h"
#include "layouts.h"
#include "layers.h"
#if defined(OLED_ENABLE)
#    include "oled_stuff.h"
#endif

// Get the enums for the layers.
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
#ifdef LAYERS_LAYER_ENABLE
  _LAYERS, // keep this here at the end of base layers.
#endif
#ifdef NAV_LAYER_ENABLE
  _NAV,   // transient layers
#endif
#ifdef SYMBOL_LAYER_ENABLE
  _SYMB,
#ifdef BEPO_ENABLE
  _SYMB_BP,
#endif
#endif
#ifdef KEYPAD_LAYER_ENABLE
  _KEYPAD,
#ifdef BEPO_ENABLE
  _KEYPAD_BP,
#endif
#endif
#ifdef TOPROWS_LAYER_ENABLE
  _TOPROWS,
#ifdef BEPO_ENABLE
  _TOPROWS_BP,
#endif
#endif
#ifdef RGB_LAYER_ENABLE
  _RGB,
#endif
#ifdef ADJUST_LAYER_ENABLE
  _ADJUST,
#endif
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
#endif

enum locales {
  LOCALE_EN_US = 0,
#ifdef BEPO_ENABLE
  LOCALE_BEPO_FR,
#endif
  LOCALES_END,
};
