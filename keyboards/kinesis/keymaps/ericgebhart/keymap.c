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

#define LAYOUT_PVARG(...)     LAYOUT_pretty(__VA_ARGS__)

#define Kinesis_base(...)        Base_4x6_4_6(__VA_ARGS__)
#define Kinesis_bepo_base(...)   Base_bepo_4x6_4_6(__VA_ARGS__)
#define Kinesis_bepo_base6(...)  Base_bepo6_4x6_4_6(__VA_ARGS__)
#define Kinesis_transient(...)   Transient6_4x6_4_6(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Qwerty Base layers
  [_DVORAK]  = Kinesis_base(___NUMS___, ___DVORAK___),
  [_QWERTY]  = Kinesis_base(___NUMS___, ___QWERTY___),
  [_COLEMAK] = Kinesis_base(___NUMS___, ___COLEMAK_DH___),
  [_BEAKL]   = Kinesis_base(___BKLNUMS___, ___BEAKL15___),
  // Bepo Base layers
  [_DVORAK_BP] = Kinesis_bepo_base(___NUMS_BP___, ___DVORAK_FR___),
  [_BEAKL_BP]  = Kinesis_bepo_base(___BKLNUMS_BP___,   ___BEAKL15_FR___),

  [_BEPO]      = Kinesis_bepo_base6(___BEPO6___),

  // transient layers.
  // Switch to using a transient layer macro
  [_SYMB]    = Kinesis_transient(___12_FUNC___, ___SYMB_BEAKLA_3x12___),
  [_SYMB_BP] = Kinesis_transient(___12_FUNC___, ___SYMB_BEAKLA_BP_3x12___),

  [_TOPROWS]    = Kinesis_transient(___12___, ___TOPROWS_3x12___),
  [_TOPROWS_BP] = Kinesis_transient(___12___, ___TOPROWS_BP_3x12___),

  [_NAV]    = Kinesis_transient(___12___, ___NAV_3x12___),
  [_LAYERS] = Kinesis_transient(___12___, ___LAYERS_3x12___),
  [_ADJUST] = Kinesis_transient(___12___, ___ADJUST_3x12___),
  //[_RGB]    = Kinesis_transient(___12___, ___RGB_3x12___),
};
