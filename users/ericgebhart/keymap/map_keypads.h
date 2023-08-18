/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
#ifdef KEYPAD_LAYER_ENABLE
#  undef THUMBS_ARE
#  define THUMBS_ARE KEYPAD_LAYER_THUMBS

#  ifdef KEYPAD_BEAKL
#    ifdef KEYPAD_BEAKL_WI
T_LAYER(LANG_N(_KEYPAD), ___KP_BKL_WI_3x10___),
#    else
#      ifdef KEYPAD_MODS
  T_LAYER(LANG_N(_KEYPAD), ___KP_BKL_MODS_3x10___),
#      else
  T_LAYER(LANG_N(_KEYPAD), ___KP_BKL_FUNC_3x10___),
#      endif
#    endif

#  else  //not beakl

#    ifdef KEYPAD_MIRYOKU
  T_LAYER(LANG_N(_KEYPAD), ___KP_MIRYOKU_3x10___),
#    else

#      ifdef KEYPAD_RIGHT
#        ifdef KEYPAD_MODS
  T_LAYER(LANG_N(_KEYPAD), ___MODS_KP_3x10___),
#        else
  T_LAYER(LANG_N(_KEYPAD), ___FP_KP_3x10___),
#        endif

#      else // kp Left
#        ifdef KEYPAD_MODS
  T_LAYER(LANG_N(_KEYPAD), ___KP_MODS_3x10___),
#        else
  T_LAYER(LANG_N(_KEYPAD), ___KP_FP_3x10___),
#        endif
#      endif
#    endif

#  endif // not beakl

#undef THUMBS_ARE
#define THUMBS_ARE DEFAULT_THUMBS
#endif

#ifdef FUNC_LAYER_ENABLE
#  ifdef FUNCPAD_MIRYOKU
  T_LAYER(_FUN, ___FP_MIRYOKU_3x10___),
#  else
  T_LAYER(_FUN, ___FUN_3x10___),
#  endif
#endif
