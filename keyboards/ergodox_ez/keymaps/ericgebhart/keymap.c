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
#include "layouts.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Qwerty Base layers
    [_DVORAK]  = Dox_base(___NUMS___, ___DVORAK___),
    [_QWERTY]  = Dox_base(___NUMS___, ___QWERTY___),
    [_COLEMAK] = Dox_base(___NUMS___, ___COLEMAK_DH___),
    [_BEAKL]   = Dox_base(___NUMS___, ___BEAKL15___),
    // Bepo Base layers
    [_DVORAK_BP] = Dox_bepo_base(___NUMS_BP___,    ___DVORAK_FR___),
    [_BEAKL_BP]  = Dox_bepo_base(___BKLNUMS_BP___, ___BEAKL15_FR___),
    [_BEPO]      = Dox_bepo_base6(___BEPO6___),


    // transient layers.
    // Switch to using a transient layer macro
    [_SYMB]    = Dox_transient(___12_FUNC___, ___SYMB_BEAKLA_3x12___),
    [_SYMB_BP] = Dox_transient(___12_FUNC___, ___SYMB_BEAKLA_BP_3x12___),

    [_TOPROWS]    = Dox_transient(___12___, ___TOPROWS_3x12___),
    [_TOPROWS_BP] = Dox_transient(___12___, ___TOPROWS_BP_3x12___),

    [_KEYPAD]    = Dox_transient(___KEYPAD_BKL_FUNC_4x12___),
    [_KEYPAD_BP] = Dox_transient(___KEYPAD_BKL_FUNC_BP_4x12___),

    [_NAV]    = Dox_transient(___12___, ___NAV_3x12___),
    [_LAYERS] = Dox_transient(___12___, ___LAYERS_3x12___),
    [_RGB]    = Dox_transient(___12___, ___RGB_3x12___),
};
