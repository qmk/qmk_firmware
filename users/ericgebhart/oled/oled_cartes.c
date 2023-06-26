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
#ifdef OLED_CUSTOM_ENABLE

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
#ifdef HALMAK_LAYER_ENABLE
        SHOW_MAP(_HALMAK)
#endif
#ifdef MINIMAK_LAYER_ENABLE
        SHOW_MAP(_MINIMAK)
#endif
#ifdef MINIMAK_8_LAYER_ENABLE
        SHOW_MAP(_MINIMAK_8)
#endif
#ifdef MINIMAK_12_LAYER_ENABLE
        SHOW_MAP(_MINIMAK_12)
#endif
#ifdef SEMIMAK_JQ_LAYER_ENABLE
        SHOW_MAP(_SEMIMAK_JQ)
#endif
#ifdef SEMIMAK_LAYER_ENABLE
        SHOW_MAP(_SEMIMAK)
#endif
#ifdef APTMAK_LAYER_ENABLE
        SHOW_MAP(_APTMAK)
#endif
#ifdef APTMAK_30_LAYER_ENABLE
        SHOW_MAP(_APTMAK_30)
#endif
#ifdef APTMAK_ALT_LAYER_ENABLE
        SHOW_MAP(_APTMAK_ALT)
#endif

#ifdef DVORAK_LAYER_ENABLE
        SHOW_MAP(_DVORAK)
#endif
#ifdef DVORAK_RLC_IU_LAYER_ENABLE
        SHOW_MAP(_DVORAK_RLC_IU)
#endif
#ifdef BOO_LAYER_ENABLE
        SHOW_MAP(_BOO)
#endif
#ifdef CAPEWELL_DVORAK_LAYER_ENABLE
        SHOW_MAP(_CAPEWELL_DVORAK)
#endif
#ifdef AHEI_LAYER_ENABLE
        SHOW_MAP(_AHEI)
#endif

#ifdef BEAKL27_LAYER_ENABLE
        SHOW_MAP(_BEAKL27)
#endif

#ifdef BEAKL27a_LAYER_ENABLE
        SHOW_MAP(_BEAKL27a)
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

#ifdef BEAKLWIa_LAYER_ENABLE
        SHOW_MAP(_BEAKLWIa)
#endif

#ifdef BEAKLWIb_LAYER_ENABLE
        SHOW_MAP(_BEAKLWIb)
#endif

#ifdef CARPALX_QFMLWY_LAYER_ENABLE
        SHOW_MAP(_CARPALX_QFMLWY)
#endif

#ifdef CARPALX_QGMLWB_LAYER_ENABLE
        SHOW_MAP(_CARPALX_QGMLWB)
#endif

#ifdef CARPALX_QGMLWY_LAYER_ENABLE
        SHOW_MAP(_CARPALX_QGMLWY)
#endif

#ifdef MTGAP_LAYER_ENABLE
        SHOW_MAP(_MTGAP)
#endif

#ifdef CTGAP_LAYER_ENABLE
        SHOW_MAP(_CTGAP)
#endif

#ifdef APT_LAYER_ENABLE
        SHOW_MAP(_APT)
#endif

#ifdef CANARY_LAYER_ENABLE
        SHOW_MAP(_CANARY)
#endif


#ifdef HD_NEU_LAYER_ENABLE
        SHOW_MAP(_HD_NEU)
#endif

#ifdef HD_NEU_NARROW_LAYER_ENABLE
        SHOW_MAP(_HD_NEU_NARROW)
#endif

#ifdef HD_NEU_NARROW_M_LAYER_ENABLE
        SHOW_MAP(_HD_NEU_NARROW_M)
#endif

#ifdef HD_TITANIUM_LAYER_ENABLE
        SHOW_MAP(_HD_TITANIUM)
#endif

#ifdef HD_VIBRANIUM_LAYER_ENABLE
        SHOW_MAP(_HD_VIBRANIUM)
#endif

#ifdef HD_VIBRANIUM_NT_LAYER_ENABLE
        SHOW_MAP(_HD_VIBRANIUM_NT)
#endif
#ifdef HD_VIBRANIUM_NTP_LAYER_ENABLE
        SHOW_MAP(_HD_VIBRANIUM_NTP)
#endif
#ifdef HD_VIBRANIUM_VF_LAYER_ENABLE
        SHOW_MAP(_HD_VIBRANIUM_VF)
#endif
#ifdef HD_VIBRANIUM_VP_LAYER_ENABLE
        SHOW_MAP(_HD_VIBRANIUM_VP)
#endif
#ifdef HD_VIBRANIUM_B_LAYER_ENABLE
        SHOW_MAP(_HD_VIBRANIUM_B)
#endif

#ifdef HD_MITHRIL_LAYER_ENABLE
        SHOW_MAP(_HD_MITHRIL)
#endif

#ifdef HD_VROOMY_LAYER_ENABLE
        SHOW_MAP(_HD_VROOMY)
#endif

#ifdef HD_RHODIUM_LAYER_ENABLE
        SHOW_MAP(_HD_RHODIUM)
#endif

#ifdef HD_RHODIUMB_LAYER_ENABLE
        SHOW_MAP(_HD_RHODIUMB)
#endif

#ifdef HD_GOLD_LAYER_ENABLE
        SHOW_MAP(_HD_GOLD)
#endif

#ifdef HD_PLATINUM_LAYER_ENABLE
        SHOW_MAP(_HD_PLATINUM)
#endif

#ifdef HD_SILVER_LAYER_ENABLE
        SHOW_MAP(_HD_SILVER)
#endif

#ifdef HD_BRONZE_LAYER_ENABLE
        SHOW_MAP(_HD_BRONZE)
#endif

#ifdef HD_ELAN_LAYER_ENABLE
        SHOW_MAP(_HD_ELAN)
#endif

#ifdef HD_DASH_LAYER_ENABLE
        SHOW_MAP(_HD_DASH)
#endif

#ifdef HD_REF_LAYER_ENABLE
        SHOW_MAP(_HD_REF)
#endif

#ifdef RSTHD_LAYER_ENABLE
        SHOW_MAP(_RSTHD)
#endif

#ifdef HANDS_UP_LAYER_ENABLE
        SHOW_MAP(_HANDS_UP)
#endif
#ifdef WHITE_LAYER_ENABLE
        SHOW_MAP(_WHITE)
#endif
#ifdef ISRT_LAYER_ENABLE
        SHOW_MAP(_ISRT)
#endif
#ifdef SOUL_LAYER_ENABLE
        SHOW_MAP(_SOUL)
#endif
#ifdef NIRO_LAYER_ENABLE
        SHOW_MAP(_NIRO)
#endif
#ifdef ASSET_LAYER_ENABLE
        SHOW_MAP(_ASSET)
#endif
#ifdef WHORF_LAYER_ENABLE
        SHOW_MAP(_WHORF)
#endif
#ifdef WHORF6_LAYER_ENABLE
        SHOW_MAP(_WHORF6)
#endif
#ifdef PINE_LAYER_ENABLE
        SHOW_MAP(_PINE)
#endif
#ifdef GRAPHITE_LAYER_ENABLE
        SHOW_MAP(_GRAPHITE)
#endif

#ifdef BEPO_LAYER_ENABLE
        SHOW_MAP(_BEPO)
#endif

#ifdef OPTIMOT_LAYER_ENABLE
        SHOW_MAP(_OPTIMOT)
#endif

#ifdef OPTIMOT_COMPACT_LAYER_ENABLE
        SHOW_MAP(_OPTIMOT_COMPACT)
#endif

#ifdef BEAKL19bis_LAYER_ENABLE
        SHOW_MAP(_BEAKL19bis)
#endif

        }

  } else {

    switch (lyr) {
#ifdef TOPROWS_LAYER_ENABLE
      LCASE(_TOPROWS)
#    ifdef TOPROWS_MOD
        CARTE_TOPROWS_MOD
#    else
#      ifdef TOPROWS_BKL_15
        CARTE_TOPROWS_BKL15
#      else
#        ifdef TOPROWS_BKL_19
        CARTE_TOPROWS_BKL19
#        else
#          ifdef TOPROWS
        CARTE_TOPROWS
#          else
#            ifdef TOPROWS_JOHNM_MOD
        CARTE_TOPROWS_JOHNM_MOD
#            else
#              ifdef TOPROWS_JOHNM2_MOD
        CARTE_TOPROWS_JOHNM2_MOD
#              else
        CARTE_RAISE
#              endif
#            endif
#          endif
#        endif
#      endif
#    endif
        break;
#endif


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
#ifdef NAV_MIRYOKU
        CARTE_NAV_miryoku
#endif
    break;

#ifdef MOUSE_LAYER_ENABLE
    case _NAVm:
#  ifdef NAV_MOUSE_MIRYOKU
        CARTE_NAVm_miryoku
#  else
      CARTE_NAVm
#  endif
      break;
#endif

#ifdef MEDIA_LAYER_ENABLE
          SHOW_MAP_S(_MEDIA)
#endif
          SHOW_MAP_S(_LAYERS)

#ifdef SYMBOL_LAYER_ENABLE
            LCASE(_SYMB)
#  ifdef SYMBOL_BEAKL
            CARTE_SYMB_BEAKL
#  endif
#  ifdef SYMBOL_BEAKL_EXT
            CARTE_SYMB_BEAKLA
#  endif
#  ifdef SYMBOL_BEAKL_EXT_VI
            CARTE_SYMB_BEAKLB
#  endif
#  ifdef SYMBOL_BEAKL_C
            CARTE_SYMB_BEAKLC
#  endif
#  ifdef SYMBOL_D
            CARTE_SYMB_D
#  endif
#  ifdef SYMBOL_MIRYOKU
            CARTE_SYMB_MIRYOKU
#  endif
#  ifdef SYMBOL_BEAKL_WI
            CARTE_SYMB_BEAKL_WI
#  endif
#  ifdef SYMBOL_BEAKL_WI
            CARTE_SYMB_NEO
#  endif
            break;
#endif

#ifdef KEYPAD_LAYER_ENABLE
          LCASE(_KEYPAD)

#  ifdef KEYPAD_BEAKL
#    ifdef KEYPAD_BEAKL_WI
          CARTE_KP_BKL_WI
#    else
#      ifdef KEYPAD_MODS
                   CARTE_KP_BKL_MODS
#      else
           CARTE_KP_BKL_FUNC
#      endif
#    endif

#  else  //not beakl

#    ifdef KEYPAD_MIRYOKU
        CARTE_KP_MIRYOKU
#    else

#      ifdef KEYPAD_RIGHT
#        ifdef KEYPAD_MODS
            CARTE_MODS_KP
#        else
            CARTE_FP_KP
#        endif

#      else // kp Left
#        ifdef KEYPAD_MODS
            CARTE_KP_MODS
#        else
            CARTE_KP_FP
#        endif
#      endif
#    endif

#  endif // not beakl
            break;
#endif // end keypad.

#ifdef MORTE_LAYER_ENABLE
         SHOW_MAP(_MORTE)
#endif

#ifdef ACCENTS_MORTE_LAYER_ENABLE
         SHOW_MAP(_ACCENTS_MORTE)
#endif

#ifdef ACCENTS_LAYER_ENABLE
         SHOW_MAP(_CARTE_ACCENTS)
#endif
          }
  }
}
#endif
