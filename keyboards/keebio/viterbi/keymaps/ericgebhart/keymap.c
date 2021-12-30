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

#include "keymap_bepo.h"
#include "ericgebhart.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // 4x10
  [_DVORAK]  = _5x14_base(___NUMS___, ___DVORAK___),
  [_QWERTY]  = _5x14_base(___NUMS___, ___QWERTY___),
  [_COLEMAK] = _5x14_base(___NUMS___, ___COLEMAK_DH___),
  [_BEAKL]   = _5x14_base(___BKLNUMS___, ___BEAKL15___),

  //[_DVORAK_BP] = _5x14_base_bepo(___DVORAK_FR___),
  //[_BEAKL_BP]  = _5x14_base_bepo(___BEAKL15_FR___),

  // 4x12
  //[_BEPO]      = _5x14_base_bepo6(___BEPO6_FR___),

    // transient macro takes a 3x12 for args
  [_SYMB]    = _5x14_transient(___12___, ___SYMB_BEAKLA_3x12___),
  //[_SYMB_BP] = _5x14_transient(___SYMB_BEAKLA_BP_3x12___),

  [_TOPROWS]    = _5x14_transient(___12___, ___TOPROWS_3x12___),
  //[_TOPROWS_BP] = _5x14_transient(___TOPROWS_BP_3x12___),

  [_KEYPAD]    = _5x14_transient(___12___, ___KP_C_3x12___),
  //[_KEYPAD_BP] = _5x14_transient(___KP_C_BP_3x12___),

  // Navigation and control
  [_NAV]    = _5x14_transient(___12___, ___NAV_3x12___),
  [_LAYERS] = _5x14_transient(___12___, ___LAYERS_3x12___),
  //[_RGB]  = _5x14_transient(___12___, ___RGB_3x12___),
};
