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
#include "ericgebhart.h"

void oled_render_layer_map(void) {
  uint8_t lyr = get_highest_layer(layer_state);
  if (lyr < _LAYERS) {
    switch (get_highest_layer(default_layer_state)) {

#ifdef QWERTY_LAYER_ENABLE
      SHOW_MAP(_QWERTY)
#endif

#ifdef COLEMAK_DH_LAYER_ENABLE
        SHOW_MAP(_COLEMAK_DH)
#endif

#ifdef COLEMAK_LAYER_ENABLE
        SHOW_MAP(_COLEMAK)
#endif

#ifdef APT_LAYER_ENABLE
        SHOW_MAP(_APT)
#endif

#ifdef DVORAK_LAYER_ENABLE
        SHOW_MAP(_DVORAK)
#endif

#ifdef BEAKL27_LAYER_ENABLE
        SHOW_MAP(_BEAKL27)
#endif

#ifdef BEAKL15_LAYER_ENABLE
        SHOW_MAP(_BEAKL15)
#endif

#ifdef BEAKL19_LAYER_ENABLE
        SHOW_MAP(_BEAKL19)
#endif

#ifdef BEAKLWI_LAYER_ENABLE
        SHOW_MAP(_BEAKLWI)
#endif

#ifdef MTGAP_LAYER_ENABLE
        SHOW_MAP(_MTGAP)
#endif

#ifdef HD_NEW_LAYER_ENABLE
        SHOW_MAP(_HD_NEU)
#endif

#ifdef HD_REF_LAYER_ENABLE
        SHOW_MAP(_HD_REF)
#endif

#ifdef BEPO_LAYER_ENABLE
        SHOW_MAP(_BEPO)
#endif

#ifdef OPTIMOT_LAYER_ENABLE
        SHOW_MAP(_OPTIMOT)
#endif

#ifdef BEAKL19bis_LAYER_ENABLE
        SHOW_MAP(_BEAKL19bis)
#endif

        }

  } else {

    switch (lyr) {
      LCASE(_TOPROWS)
#ifdef TOPROWS_BKL_NUMS
#ifdef TOPROWS_MOD
        CARTE_TOPROWS_MOD
#else
#ifdef TOPROWS_BKL_19_NUMS
        CARTE_TOPROWS_BKL19
#else
        CARTE_TOPROWS
#endif
#endif
#else // not beakl nums.
        CARTE_RAISE
#endif
        break;


    case _NAV:
#ifdef NAV_FULL_LOCK_MODS
      CARTE_NAVA
#endif
#ifdef NAV_FULL
        CARTE_NAV
#endif
#ifdef NAV_NO_MOUSE
        CARTE_NAVnm
#endif
    break;

#ifdef MOUSEKEY_ENABLE
      SHOW_MAP_S(_NAVm)
#endif

      SHOW_MAP_S(_LAYERS)

      LCASE(_SYMB)
      CARTE_SYMB_BEAKLB
      break;

#ifdef KEYAD_LAYER_ENABLE
      LCASE(_KEYPAD)
#ifdef KEYPAD_BEAKL
#ifdef KEYPAD_BEAKL_WI
      CARTE_KP_BKL_WI
#endif
#ifdef KEYPAD_MODS
        CARTE_KP_BKL_MODS
#endif
#if !defined(KEYPAD_MODS) && !defined(KEYPAD_BEAKL_WI)
        CARTE_KP_BKL_FUNC
#endif

#else // not beakl.
#ifdef KEYPAD_RIGHT
#ifdef KEYPAD_MODS
        CARTE_MODS_KP
#else
        CARTE_FP_KP
#endif

#else // not keypad right.
#ifdef KEYPAD_MODS
        CARTE_KP_MODS
#else
        CARTE_KP_FP  // the final default.
#endif
#endif // end not keypad right.
#endif // end not beakl
        break;
#endif // end keypad.

      // extra layers for bepo only
#ifdef MORTE_LAYER_ENABLE
    case _MORTE:
      CARTE_MORTE
      break;
#endif

#ifdef ACCENTED_MORTE_LAYER_ENABLE
    case _ACCENTED_MORTE:
      CARTE_ACCENTED_MORTE
        break;
#endif

#ifdef ACCENTED_LAYER_ENABLE
    case _ACCENTED:
      CARTE_ACCENTED
        break;
#endif

    }
  }
}
