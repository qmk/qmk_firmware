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


//#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
/* Define layer names */
enum userspace_layers {
    _DVORAK = 0,
    _QWERTY,
    _COLEMAK,
    _BEAKL,
    //_WORKMAN,
    //_NORMAN,
    //_MALTRON,
    //_EUCALYN,
    //_CARPLAX,
    _DVORAK_BP, // beginning of Bepo
    _BEAKL_BP,
    _BEPO,
    _LAYERS,
    _NAV,   // transient layers
    _SYMB,
    _SYMB_BP,
    _KEYPAD,
    _KEYPAD_BP,
    _TOPROWS,
    _TOPROWS_BP,
    _RGB,
    _ADJUST,
};

// clang-format off
typedef union {
  uint32_t raw;
  struct {
    bool    rgb_layer_change     :1;
    bool    is_overwatch         :1;
    bool    nuke_switch          :1;
    bool    swapped_numbers      :1;
    bool    rgb_matrix_idle_anim :1;
  };
} userspace_config_t;
// clang-format on
extern userspace_config_t userspace_config;

#endif
