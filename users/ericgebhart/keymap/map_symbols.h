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
#ifdef SYMBOL_LAYER_ENABLE
#  undef THUMBS_ARE
#  define THUMBS_ARE SYMB_LAYER_THUMBS

#  ifdef SYMBOL_BEAKL_C
T_LAYER(LANG_N(_SYMB), ___SYMB_BEAKLC_3x10___),
#  else

#    ifdef SYMBOL_BEAKL_EXT_VI
      T_LAYER(LANG_N(_SYMB), ___SYMB_BEAKLB_3x10___),
#    else

#      ifdef SYMBOL_BEAKL_EXT
      T_LAYER(LANG_N(_SYMB ), ___SYMB_BEAKLA_3x10___),
#      else

#        ifdef SYMBOL_BEAKL_WI
  T_LAYER(LANG_N(_SYMB), ___SYMB_BEAKLWI_3x10___),
#        else

#          ifdef SYMBOL_MIRYOKU
  T_LAYER(LANG_N(_SYMB), ___SYMB_MIRYOKU_3x10___),
#          else

#            ifdef SYMBOL_NEO
  T_LAYER(LANG_N(_SYMB), ___SYMB_NEO_3x10___),
#            else

// basic beakl, the default if nothing chosen.
           T_LAYER(LANG_N(_SYMB), ___SYMB_BEAKL_3x10___),

#            endif //neo
#          endif //miryoku
#        endif //beakl wi
#      endif //beakl ext
#    endif //beakl ext vi
#  endif //beaklc
#  undef THUMBS_ARE
#  define THUMBS_ARE DEFAULT_THUMBS
#endif
