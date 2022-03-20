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

void oled_render_default_layer_state(void) {
  //oled_write_P(PSTR("Layout: "), false);
  switch (get_highest_layer(default_layer_state)) {
#ifdef DVORAK_LAYER_ENABLE
    WRITE_STR_LAYER(_DVORAK, "Dvorak")
#endif
#ifdef QWERTY_LAYER_ENABLE
      WRITE_STR_LAYER(_QWERTY, "Qwerty")
#endif
#ifdef COLEMAK_LAYER_ENABLE
      WRITE_STR_LAYER(_COLEMAK, "Colemak")
#endif
#ifdef COLEMAK_DH_LAYER_ENABLE
      WRITE_STR_LAYER(_COLEMAK_DH, "Colemak")
#endif
#ifdef BEAKL15_LAYER_ENABLE
      WRITE_STR_LAYER(_BEAKL15, "Beakl")
#endif
#ifdef BEAKL19_LAYER_ENABLE
      WRITE_STR_LAYER(_BEAKL19, "Beakl19")
#endif
#ifdef BEAKL27_LAYER_ENABLE
      WRITE_STR_LAYER(_BEAKL27, "Beakl27")
#endif
#ifdef BEAKLWI_LAYER_ENABLE
      WRITE_STR_LAYER(_BEAKLWI, "BeaklWi")
#endif
#ifdef WORKMAN_LAYER_ENABLE
      WRITE_STR_LAYER(_WORKMAN, "Workman")
#endif
#ifdef NORMAN_LAYER_ENABLE
      WRITE_STR_LAYER(_NORMAN, "Norman")
#endif
#ifdef MALTRON_LAYER_ENABLE
      WRITE_STR_LAYER(_MALTRON, "Maltron")
#endif
#ifdef EUCALYN_LAYER_ENABLE
      WRITE_STR_LAYER(_EUCALYN, "Eucalyn")
#endif
#ifdef CARPLAX_LAYER_ENABLE
      WRITE_STR_LAYER(_CARPLAX, "Carplax")
#endif
#ifdef HD_NEU_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_NEU, "HD neu")
#endif
#ifdef HD_REF_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_REF, "HD ref")
#endif
#ifdef MTGAP_LAYER_ENABLE
      WRITE_STR_LAYER(_MTGAP, "Mtgap")
#endif
#ifdef APT_LAYER_ENABLE
      WRITE_STR_LAYER(_APT, "Apt")
#endif
      // these only exist as Non _bp, non _en.
#ifdef OPTIMOT_LAYER_ENABLE
      WRITE_STR_CASE(_OPTIMOT, "Optimot")
#endif
#ifdef BEAKL19bis_LAYER_ENABLE
      WRITE_STR_CASE(_BEAKL19bis, "Beakl19bis")
#endif
#ifdef BEPO_LAYER_ENABLE  // Bepo only works on bepo.
      WRITE_STR_CASE(_BEPO, "Bepo")
#endif
      }
}

void oled_render_layer_state(void) {
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(layer_state)) {

    // language variant layers.
#ifdef TOPROWS_LAYER_ENABLE
    WRITE_STR_LAYER(_TOPROWS, "TopRows");
#endif

#ifdef SYMBOL_LAYER_ENABLE
    WRITE_STR_LAYER(_SYMB, "Symbols");
#endif

#ifdef KEYPAD_LAYER_ENABLE
    WRITE_STR_LAYER(_KEYPAD, "Keypad");
#endif

// single case, BP or no suffix.
#ifdef ACCENTED_MORTE_LAYER_ENABLE
    WRITE_STR_CASE(_ACCENTED_MORTE_BP, "Accented Morte");
#endif
#ifdef ACCENTED_LAYER_ENABLE
    WRITE_STR_CASE(_ACCENTED_BP, "Accented");
#endif
#ifdef MORTE_LAYER_ENABLE
    WRITE_STR_CASE(_MORTE_BP, "Morte");
#endif


    // language agnostic layers.
#ifdef NAV_LAYER_ENABLE
    WRITE_STR_CASE(_NAV, "Navigation");
    WRITE_STR_CASE(_NAVm, "Mouse");
#endif
#ifdef LAYERS_LAYER_ENABLE
    WRITE_STR_CASE(_LAYERS, "Layers");
#endif
#ifdef RGB_LAYER_ENABLE
    WRITE_STR_CASE(_RGB, "RGB");
#endif
#ifdef ADJUST_LAYER_ENABLE
    WRITE_STR_CASE(_ADJUST, "Adjust");
#endif
#ifdef COMBO_REF_LAYER_ENABLE
    WRITE_STR_CASE(_COMBO_REF, "COMBO Ref");
#endif

  }
}
