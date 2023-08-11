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
#include <stdio.h>

#ifdef OLED_CUSTOM_ENABLE

void oled_render_default_layer_state(void) {
  //oled_write_P(PSTR("Layout: "), false);
  uint16_t layer = get_highest_layer(default_layer_state);
  char layer_str[8];
  snprintf(layer_str, sizeof(layer_str), "%u ",layer);
  oled_write(layer_str , false);
  switch (layer) {
#ifdef DVORAK_LAYER_ENABLE
    WRITE_STR_LAYER(_DVORAK, "Dvorak")
#endif
#ifdef DVORAK_RLC_IU_LAYER_ENABLE
      WRITE_STR_LAYER(_DVORAK_RLC_IU_, "Dvorak-rlc")
#endif
#ifdef BOO_LAYER_ENABLE
      WRITE_STR_LAYER(_BOO, "Boo")
#endif
#ifdef CAPEWELL_DVORAK_LAYER_ENABLE
      WRITE_STR_LAYER(_CAPEWELL_DVORAK, "Capewell Dvorak")
#endif
#ifdef AHEI_LAYER_ENABLE
      WRITE_STR_LAYER(_AHEI, "Ahei")
#endif

#ifdef QWERTY_LAYER_ENABLE
      WRITE_STR_LAYER(_QWERTY, "Qwerty")
#endif
#ifdef WORKMAN_LAYER_ENABLE
      WRITE_STR_LAYER(_WORKMAN, "Workman")
#endif
#ifdef NORMAN_LAYER_ENABLE
      WRITE_STR_LAYER(_NORMAN, "Norman")
#endif

#ifdef COLEMAK_LAYER_ENABLE
      WRITE_STR_LAYER(_COLEMAK, "Colemak")
#endif
#ifdef COLEMAK_DH_LAYER_ENABLE
      WRITE_STR_LAYER(_COLEMAK_DH, "Colemak")
#endif
#ifdef HALMAK_LAYER_ENABLE
      WRITE_STR_LAYER(_HALMAK, "Halmak")
#endif
#ifdef MINIMAK_LAYER_ENABLE
      WRITE_STR_LAYER(_MINIMAK, "Minimak")
#endif
#ifdef MINIMAK_8_LAYER_ENABLE
      WRITE_STR_LAYER(_MINIMAK_8, "Minimak 8")
#endif
#ifdef MINIMAK_12_LAYER_ENABLE
      WRITE_STR_LAYER(_MINIMAK_12, "Minimak 12")
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

#ifdef CARPALX_QFMLWY_LAYER_ENABLE
      WRITE_STR_LAYER(_CARPALX_QFMLWY, "Carpalx qfmlwy")
#endif

#ifdef CARPALX_QGMLWB_LAYER_ENABLE
      WRITE_STR_LAYER(_CARPALX_QGMLWB, "Carpalx qgmlwb")
#endif

#ifdef CARPALX_QGMLWY_LAYER_ENABLE
      WRITE_STR_LAYER(_CARPALX_QGMLWY, "Carpalx qgmlwy")
#endif

#ifdef HD_NEU_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_NEU, "HD Neu")
#endif
#ifdef HD_NEU_NARROW_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_NEU_NARROW, "HD Neu N")
#endif
#ifdef HD_TITANIUM_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_TITANIUM, "HD Titanium")
#endif
#ifdef HD_GOLD_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_GOLD, "HD Gold")
#endif
#ifdef HD_SILVER_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_SILVER, "HD Silver")
#endif
#ifdef HD_PLATINUM_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_PLATINUM, "HD Platinum")
#endif
#ifdef HD_BRONZE_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_BRONZE, "HD Bronze")
#endif
#ifdef HD_ELAN_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_ELAN, "HD Elan")
#endif
#ifdef HD_DASH_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_DASH, "HD Dash")
#endif
#ifdef HD_REF_LAYER_ENABLE
      WRITE_STR_LAYER(_HD_REF, "HD Ref")
#endif

#ifdef MTGAP_LAYER_ENABLE
      WRITE_STR_LAYER(_MTGAP, "Mtgap")
#endif
#ifdef CTGAP_LAYER_ENABLE
      WRITE_STR_LAYER(_CTGAP, "Ctgap")
#endif
#ifdef APT_LAYER_ENABLE
      WRITE_STR_LAYER(_APT, "Apt")
#endif
#ifdef CANARY_LAYER_ENABLE
      WRITE_STR_LAYER(_CANARY, "Canary")
#endif

#ifdef MALTRON_LAYER_ENABLE
      WRITE_STR_LAYER(_MALTRON, "Maltron")
#endif
#ifdef EUCALYN_LAYER_ENABLE
      WRITE_STR_LAYER(_EUCALYN, "Eucalyn")
#endif
#ifdef RSTHD_LAYER_ENABLE
      WRITE_STR_LAYER(_RSTHD, "Rsthd")
#endif
#ifdef HAND_UP_LAYER_ENABLE
      WRITE_STR_LAYER(_HANDS_UP, "Hands up")
#endif
#ifdef WHITE_LAYER_ENABLE
      WRITE_STR_LAYER(_WHITE, "White")
#endif
#ifdef ISRT_LAYER_ENABLE
      WRITE_STR_LAYER(_ISRT, "Isrt")
#endif
#ifdef SOUL_LAYER_ENABLE
      WRITE_STR_LAYER(_SOUL, "Soul")
#endif
#ifdef NIRO_LAYER_ENABLE
      WRITE_STR_LAYER(_NIRO, "Niro")
#endif
#ifdef ASSET_LAYER_ENABLE
      WRITE_STR_LAYER(_ASSET, "Asset")
#endif
#ifdef WHORF_LAYER_ENABLE
      WRITE_STR_LAYER(_WHORF, "Whorf")
#endif
#ifdef WHORF6_LAYER_ENABLE
      WRITE_STR_LAYER(_WHORF6, "Whorf 6")
#endif

#ifdef OPTIMOT_LAYER_ENABLE
      WRITE_STR_LAYER(_OPTIMOT, "Optimot")
#endif
#ifdef OPTIMOT_COMPACT_LAYER_ENABLE
      WRITE_STR_LAYER(_OPTIMOT_COMPACT, "Optimot")
#endif
#ifdef BEAKL19bis_LAYER_ENABLE
      WRITE_STR_LAYER(_BEAKL19bis, "Beakl19bis")
#endif
#ifdef BEPO_LAYER_ENABLE  // Bepo only works on bepo.
      WRITE_STR_LAYER(_BEPO, "Bepo")
#endif
      }
}

void oled_render_layer_state(void) {
  uint16_t layer = get_highest_layer(layer_state);
  char layer_str[8];
  snprintf(layer_str, sizeof(layer_str), "%u ",layer);
  oled_write_P(PSTR(""), false);
  if (layer > 0)
    oled_write(layer_str , false);

  switch (layer) {
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
#ifdef ACCENTS_MORTE_LAYER_ENABLE
    WRITE_STR_LAYER(_ACCENTS_MORTE, "Accents Morte");
#endif
#ifdef ACCENTS_LAYER_ENABLE
    WRITE_STR_LAYER(_ACCENTS, "Accents");
#endif
#ifdef MORTE_LAYER_ENABLE
    WRITE_STR_LAYER(_MORTE, "Morte");
#endif


    // language agnostic layers.
#ifdef NAV_LAYER_ENABLE
    WRITE_STR_CASE(_NAV, "Navigation");
    WRITE_STR_CASE(_NAVm, "Mouse");
#endif
#ifdef MEDIA_LAYER_ENABLE
    WRITE_STR_CASE(_MEDIA, "Media");
#endif
#ifdef FUNC_LAYER_ENABLE
    WRITE_STR_CASE(_FUN, "Func");
#endif

    WRITE_STR_CASE(_LAYERS, "Layers");

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
#endif
