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

// transient layers.

#ifdef LAYERS_LAYER_ENABLE
_LAYERS, // keep this here at the end of base layers.
#define MO_LAYERS MO(_LAYERS)
#else
#define MO_LAYERS ___
#endif

#ifdef NAV_LAYER_ENABLE
  _NAV,   // transient layers
#ifdef MOUSEKEY_ENABLE
  _NAVm,
#endif
#endif

#ifdef SYMBOL_LAYER_ENABLE
  _SYMB,
  _SYMB_EN = _SYMB,
#ifdef BEPO_ENABLE
  _SYMB_BP,
#endif
#endif

#ifdef KEYPAD_LAYER_ENABLE
  _KEYPAD,
  _KEYPAD_EN = _KEYPAD,   // the en's will be the norm at some point.
#ifdef BEPO_ENABLE
  _KEYPAD_BP,
#endif
#endif

#ifdef TOPROWS_LAYER_ENABLE
  _TOPROWS,
  _TOPROWS_EN = _TOPROWS,
#ifdef BEPO_ENABLE
  _TOPROWS_BP,
#endif
#endif

#ifdef RGB_LAYER_ENABLE
  _RGB,
#define TO_RGB MO(_RGB)
#else
#define TO_RGB ___
#endif

#ifdef ADJUST_LAYER_ENABLE
  _ADJUST,
#define MO_ADJUST MO(_ADJUST)
#else
#define MO_ADJUST ___
#endif

#ifdef BEPO_ENABLE
#ifdef ACCENTED_LAYER_ENABLE
  _ACCENTED_BP,
#endif
#ifdef MORTE_LAYER_ENABLE
  _MORTE_BP,
#endif
#ifdef ACCENTED_MORTE_LAYER_ENABLE
  _ACCENTED_MORTE_BP,
#endif
#endif

#ifdef COMBO_REF_LAYER_ENABLE
  _COMBO_REF,
#endif
#ifdef COMBO_REF_LAYER_TWO_ENABLE
  _COMBO_REF2,
#endif
