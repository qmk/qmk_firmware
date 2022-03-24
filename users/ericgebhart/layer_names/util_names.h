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

// transient layers which are language agnostic.

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


#ifdef COMBO_REF_LAYER_ENABLE
  _COMBO_REF,
// set the combo reference layer if we have one.
#undef COMBO_REF_DEFAULT
#define COMBO_REF_DEFAULT _COMBO_REF
#endif
#ifdef COMBO_REF_LAYER_TWO_ENABLE
  _COMBO_REF2,
#endif
